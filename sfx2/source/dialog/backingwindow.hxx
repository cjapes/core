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

#ifndef INCLUDED_SFX2_SOURCE_DIALOG_BACKINGWINDOW_HXX
#define INCLUDED_SFX2_SOURCE_DIALOG_BACKINGWINDOW_HXX

#include <rtl/ustring.hxx>

#include <vcl/builder.hxx>
#include <vcl/button.hxx>
#include <vcl/tabctrl.hxx>
#include <vcl/layout.hxx>

#include <sfx2/recentdocsview.hxx>
#include <sfx2/templatelocalview.hxx>
#include <sfx2/templateviewitem.hxx>

#include <svtools/acceleratorexecute.hxx>
#include <unotools/moduleoptions.hxx>

#include <com/sun/star/datatransfer/dnd/XDropTarget.hpp>
#include <com/sun/star/uno/XComponentContext.hpp>
#include <com/sun/star/frame/XDispatchProvider.hpp>
#include <com/sun/star/frame/XDesktop.hpp>
#include <com/sun/star/frame/XFrame.hpp>
#include <com/sun/star/frame/XDesktop2.hpp>

#include <set>

class BackingWindow
    : public Window
    , public VclBuilderContainer
{
    com::sun::star::uno::Reference< com::sun::star::uno::XComponentContext >         mxContext;
    com::sun::star::uno::Reference<com::sun::star::frame::XDispatchProvider >        mxDesktopDispatchProvider;
    com::sun::star::uno::Reference<com::sun::star::frame::XFrame>                    mxFrame;
    com::sun::star::uno::Reference< com::sun::star::frame::XDesktop2 >               mxDesktop;
    /** helper for drag&drop. */
    com::sun::star::uno::Reference< com::sun::star::datatransfer::dnd::XDropTargetListener > mxDropTargetListener;

    PushButton*                     mpOpenButton;
    PushButton*                     mpTemplateButton;

    FixedText*                      mpCreateLabel;

    PushButton*                     mpWriterAllButton;
    PushButton*                     mpCalcAllButton;
    PushButton*                     mpImpressAllButton;
    PushButton*                     mpDrawAllButton;
    PushButton*                     mpDBAllButton;
    PushButton*                     mpMathAllButton;

    PushButton*                     mpHelpButton;
    PushButton*                     mpExtensionsButton;

    VclBox*                         mpAllButtonsBox;
    VclBox*                         mpButtonsBox;
    VclBox*                         mpSmallButtonsBox;
    VclBox*                         mpThinBox1;
    VclBox*                         mpThinBox2;
    VclBox*                         mpHelpBox;
    VclBox*                         mpExtensionsBox;

    RecentDocsView*                 mpAllRecentThumbnails;

    std::vector<Window*>            maDndWindows;

    Rectangle                       maStartCentButtons;

    bool                            mbInitControls;
    sal_Int32                       mnHideExternalLinks;
    svt::AcceleratorExecute*        mpAccExec;

    void setupButton( PushButton* pButton );

    void dispatchURL( const OUString& i_rURL,
                      const OUString& i_rTarget = OUString( "_default" ),
                      const com::sun::star::uno::Reference< com::sun::star::frame::XDispatchProvider >& i_xProv = com::sun::star::uno::Reference< com::sun::star::frame::XDispatchProvider >(),
                      const com::sun::star::uno::Sequence< com::sun::star::beans::PropertyValue >& = com::sun::star::uno::Sequence< com::sun::star::beans::PropertyValue >()
                      );

    DECL_LINK(ClickHdl, Button*);
    DECL_LINK(ExtLinkClickHdl, Button*);

    void initControls();

public:
    BackingWindow( Window* pParent );
    ~BackingWindow();

    virtual void        Paint( const Rectangle& rRect ) SAL_OVERRIDE;
    virtual void        Resize() SAL_OVERRIDE;
    virtual bool        PreNotify( NotifyEvent& rNEvt ) SAL_OVERRIDE;
    virtual bool        Notify( NotifyEvent& rNEvt ) SAL_OVERRIDE;
    virtual void        GetFocus() SAL_OVERRIDE;

    virtual Size GetOptimalSize() const SAL_OVERRIDE;

    void setOwningFrame( const com::sun::star::uno::Reference< com::sun::star::frame::XFrame >& xFrame );

    void clearRecentFileList();
};

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
