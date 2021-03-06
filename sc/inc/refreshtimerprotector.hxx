/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef SC_REFRESHTIMERPROTECTOR_HXX
#define SC_REFRESHTIMERPROTECTOR_HXX

#include <sal/config.h>
#include "scdllapi.h"

class ScRefreshTimerControl;

class SC_DLLPUBLIC ScRefreshTimerProtector
{
    ScRefreshTimerControl * const * ppControl;

public:
    ScRefreshTimerProtector( ScRefreshTimerControl * const * pp );
    ~ScRefreshTimerProtector();
};

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
