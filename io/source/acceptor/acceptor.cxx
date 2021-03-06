/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */

#include <osl/mutex.hxx>

#include <uno/mapping.hxx>

#include <cppuhelper/factory.hxx>
#include <cppuhelper/implbase2.hxx>
#include <cppuhelper/implementationentry.hxx>
#include <cppuhelper/supportsservice.hxx>
#include "cppuhelper/unourl.hxx"
#include "rtl/malformeduriexception.hxx"

#include <com/sun/star/connection/XAcceptor.hpp>
#include <com/sun/star/lang/XServiceInfo.hpp>

#include "services.hxx"
#include "acceptor.hxx"

#define IMPLEMENTATION_NAME "com.sun.star.comp.io.Acceptor"
#define SERVICE_NAME "com.sun.star.connection.Acceptor"

using namespace ::osl;
using namespace ::rtl;
using namespace ::cppu;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::registry;
using namespace ::com::sun::star::connection;

namespace io_acceptor
{
    class OAcceptor : public WeakImplHelper2< XAcceptor, XServiceInfo >
    {
    public:
        OAcceptor(const Reference< XComponentContext > & xCtx);
        virtual ~OAcceptor();
    public:
        // Methods
        virtual Reference< XConnection > SAL_CALL accept( const OUString& sConnectionDescription )
            throw( AlreadyAcceptingException,
                   ConnectionSetupException,
                   IllegalArgumentException,
                   RuntimeException, std::exception) SAL_OVERRIDE;
        virtual void SAL_CALL stopAccepting(  ) throw( RuntimeException, std::exception) SAL_OVERRIDE;

    public: // XServiceInfo
                virtual OUString              SAL_CALL getImplementationName() throw(std::exception) SAL_OVERRIDE;
                virtual Sequence< OUString >  SAL_CALL getSupportedServiceNames(void) throw(std::exception) SAL_OVERRIDE;
                virtual sal_Bool              SAL_CALL supportsService(const OUString& ServiceName) throw(std::exception) SAL_OVERRIDE;

    private:
        PipeAcceptor *m_pPipe;
        SocketAcceptor *m_pSocket;
        Mutex m_mutex;
        OUString m_sLastDescription;
        sal_Bool m_bInAccept;

        Reference< XMultiComponentFactory > _xSMgr;
        Reference< XComponentContext > _xCtx;
        Reference<XAcceptor>         _xAcceptor;
    };


    OAcceptor::OAcceptor( const Reference< XComponentContext > & xCtx )
        : m_pPipe( 0 )
        , m_pSocket( 0 )
        , m_bInAccept( sal_False )
        , _xSMgr( xCtx->getServiceManager() )
        , _xCtx( xCtx )
    {}

    OAcceptor::~OAcceptor()
    {
        if( m_pPipe )
        {
            delete m_pPipe;
        }
        if( m_pSocket )
        {
            delete m_pSocket;
        }
    }

    struct BeingInAccept
    {
        BeingInAccept( sal_Bool *pFlag,const OUString & sConnectionDescription  ) throw( AlreadyAcceptingException)
            : m_pFlag( pFlag )
            {
                  if( *m_pFlag )
                  {
                      OUString sMessage( "AlreadyAcceptingException :" );
                      sMessage += sConnectionDescription;
                      throw AlreadyAcceptingException( sMessage , Reference< XInterface > () );
                  }
                  *m_pFlag = sal_True;
            }
        ~BeingInAccept()
            {
                *m_pFlag = sal_False;
            }
        sal_Bool *m_pFlag;
    };

    Reference< XConnection > OAcceptor::accept( const OUString &sConnectionDescription )
        throw( AlreadyAcceptingException,
               ConnectionSetupException,
               IllegalArgumentException,
               RuntimeException, std::exception)
    {
        OSL_TRACE(
            "acceptor %s\n",
            OUStringToOString(
                sConnectionDescription, RTL_TEXTENCODING_ASCII_US).getStr());
        // if there is a thread alread accepting in this object, throw an exception.
        struct BeingInAccept guard( &m_bInAccept, sConnectionDescription );

        Reference< XConnection > r;
        if( !m_sLastDescription.isEmpty() &&
            m_sLastDescription != sConnectionDescription )
        {
            // instantiate another acceptor for different ports
            OUString sMessage = "acceptor::accept called multiple times with different conncetion strings\n";
            throw ConnectionSetupException( sMessage, Reference< XInterface > () );
        }

        if( m_sLastDescription.isEmpty() )
        {
            // setup the acceptor
            try
            {
                cppu::UnoUrlDescriptor aDesc(sConnectionDescription);
                if ( aDesc.getName() == "pipe" )
                {
                    OUString aName(
                        aDesc.getParameter(
                            OUString("name")));

                    m_pPipe = new PipeAcceptor(aName, sConnectionDescription);

                    try
                    {
                        m_pPipe->init();
                    }
                    catch( ... )
                    {
                        {
                            MutexGuard g( m_mutex );
                            delete m_pPipe;
                            m_pPipe = 0;
                        }
                        throw;
                    }
                }
                else if ( aDesc.getName() == "socket" )
                {
                    OUString aHost;
                    if (aDesc.hasParameter(
                            OUString("host")))
                        aHost = aDesc.getParameter(
                            OUString("host"));
                    else
                        aHost = "localhost";
                    sal_uInt16 nPort = static_cast< sal_uInt16 >(
                        aDesc.getParameter(
                            OUString("port")).
                        toInt32());
                    bool bTcpNoDelay
                        = aDesc.getParameter(
                            OUString("tcpnodelay")).toInt32() != 0;

                    m_pSocket = new SocketAcceptor(
                        aHost, nPort, bTcpNoDelay, sConnectionDescription);

                    try
                    {
                        m_pSocket->init();
                    }
                    catch( ... )
                    {
                        {
                            MutexGuard g( m_mutex );
                            delete m_pSocket;
                            m_pSocket = 0;
                        }
                        throw;
                    }
                }
                else
                {
                    OUString delegatee = "com.sun.star.connection.Acceptor." + aDesc.getName();

                    OSL_TRACE(
                        "trying to get service %s\n",
                        OUStringToOString(
                            delegatee, RTL_TEXTENCODING_ASCII_US).getStr());
                    _xAcceptor = Reference<XAcceptor>(
                        _xSMgr->createInstanceWithContext(delegatee, _xCtx), UNO_QUERY);

                    if(!_xAcceptor.is())
                    {
                        OUString message("Acceptor: unknown delegatee ");
                        message += delegatee;

                        throw ConnectionSetupException(message, Reference<XInterface>());
                    }
                }
            }
            catch (const rtl::MalformedUriException & rEx)
            {
                throw IllegalArgumentException(
                    rEx.getMessage(),
                    Reference< XInterface > (),
                    0 );
            }
            m_sLastDescription = sConnectionDescription;
        }

        if( m_pPipe )
        {
            r = m_pPipe->accept();
        }
        else if( m_pSocket )
        {
            r = m_pSocket->accept();
        }
        else
        {
            r = _xAcceptor->accept(sConnectionDescription);
        }

        return r;
    }

    void SAL_CALL OAcceptor::stopAccepting(  ) throw( RuntimeException, std::exception)
    {
        MutexGuard guard( m_mutex );

        if( m_pPipe )
        {
            m_pPipe->stopAccepting();
        }
        else if ( m_pSocket )
        {
            m_pSocket->stopAccepting();
        }
        else if( _xAcceptor.is() )
        {
            _xAcceptor->stopAccepting();
        }

    }

    OUString acceptor_getImplementationName()
    {
        return OUString( IMPLEMENTATION_NAME );
    }

    Reference< XInterface > SAL_CALL acceptor_CreateInstance( const Reference< XComponentContext > & xCtx)
    {
        return Reference < XInterface >( ( OWeakObject * ) new OAcceptor(xCtx) );
    }

    Sequence< OUString > acceptor_getSupportedServiceNames()
    {
        Sequence< OUString > seqNames(1);
        seqNames.getArray()[0] = SERVICE_NAME;
        return seqNames;
    }

        OUString OAcceptor::getImplementationName() throw(std::exception)
    {
        return acceptor_getImplementationName();
    }

        sal_Bool OAcceptor::supportsService(const OUString& ServiceName) throw(std::exception)
    {
        return cppu::supportsService(this, ServiceName);
    }

        Sequence< OUString > OAcceptor::getSupportedServiceNames(void) throw(std::exception)
    {
        return acceptor_getSupportedServiceNames();
    }


}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
