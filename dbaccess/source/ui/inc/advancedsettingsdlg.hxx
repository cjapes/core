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

#ifndef INCLUDED_DBACCESS_SOURCE_UI_INC_ADVANCEDSETTINGSDLG_HXX
#define INCLUDED_DBACCESS_SOURCE_UI_INC_ADVANCEDSETTINGSDLG_HXX

#include "IItemSetHelper.hxx"
#include "moduledbu.hxx"

#include <sfx2/tabdlg.hxx>

#include <memory>

namespace dbaui
{

    // AdvancedSettingsDialog
    class ODbDataSourceAdministrationHelper;
    /** implements the advanced page dlg of the data source properties.
    */
    class AdvancedSettingsDialog    :public SfxTabDialog
                                    ,public IItemSetHelper
                                    ,public IDatabaseSettingsDialog
    {
        OModuleClient                                       m_aModuleClient;
        ::std::auto_ptr<ODbDataSourceAdministrationHelper>  m_pImpl;

    protected:
        virtual void PageCreated(sal_uInt16 _nId, SfxTabPage& _rPage) SAL_OVERRIDE;

    public:
        AdvancedSettingsDialog( Window* _pParent
                            ,SfxItemSet* _pItems
                            ,const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XComponentContext >& _rxORB
                            ,const ::com::sun::star::uno::Any& _aDataSourceName);

        virtual ~AdvancedSettingsDialog();

        /// determines whether or not the given data source type has any advanced setting
        static  bool    doesHaveAnyAdvancedSettings( const OUString& _sURL );

        virtual const SfxItemSet* getOutputSet() const SAL_OVERRIDE;
        virtual SfxItemSet* getWriteOutputSet() SAL_OVERRIDE;

        virtual short   Execute() SAL_OVERRIDE;

        // forwards to ODbDataSourceAdministrationHelper
        virtual ::com::sun::star::uno::Reference< ::com::sun::star::uno::XComponentContext > getORB() const SAL_OVERRIDE;
        virtual ::std::pair< ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection >,sal_Bool> createConnection() SAL_OVERRIDE;
        virtual ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XDriver > getDriver() SAL_OVERRIDE;
        virtual OUString getDatasourceType(const SfxItemSet& _rSet) const SAL_OVERRIDE;
        virtual void clearPassword() SAL_OVERRIDE;
        virtual sal_Bool saveDatasource() SAL_OVERRIDE;
        virtual void setTitle(const OUString& _sTitle) SAL_OVERRIDE;
        virtual void enableConfirmSettings( bool _bEnable ) SAL_OVERRIDE;
    };

} // namespace dbaui

#endif // INCLUDED_DBACCESS_SOURCE_UI_INC_ADVANCEDSETTINGSDLG_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
