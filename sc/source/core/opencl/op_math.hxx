/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef SC_OPENCL_OP_MATH_HXX
#define SC_OPENCL_OP_MATH_HXX

#include "opbase.hxx"

namespace sc { namespace opencl {

class OpCos: public Normal
{
public:
    virtual void GenSlidingWindowFunction(std::stringstream &ss,
            const std::string sSymName, SubArguments &vSubArguments);

    virtual std::string BinFuncName(void) const { return "Cos"; }
};

class OpCsc: public Normal
{
public:
    virtual void GenSlidingWindowFunction(std::stringstream &ss,
            const std::string sSymName, SubArguments &vSubArguments);
    virtual std::string BinFuncName(void) const { return "Csc"; }
};

class OpSinh: public Normal
{
public:
    virtual void GenSlidingWindowFunction(std::stringstream &ss,
            const std::string sSymName, SubArguments &vSubArguments);
    virtual std::string BinFuncName(void) const { return "Sinh"; }
};
}}

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
