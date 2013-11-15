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
class OpSumIfs: public CheckVariables
{
public:
    virtual void GenSlidingWindowFunction(std::stringstream &ss,
            const std::string sSymName, SubArguments &vSubArguments);
    virtual std::string BinFuncName(void) const { return "SumIfs"; }
};
class OpCosh: public Normal
{
public:
    virtual void GenSlidingWindowFunction(std::stringstream &ss,
            const std::string sSymName, SubArguments &vSubArguments);

    virtual std::string BinFuncName(void) const { return "Cosh"; }
};
class OpSinh: public Normal
{
public:
    virtual void GenSlidingWindowFunction(std::stringstream &ss,
            const std::string sSymName, SubArguments &vSubArguments);
    virtual std::string BinFuncName(void) const { return "Sinh"; }
};
class OpSin: public Normal
{
public:
    virtual void GenSlidingWindowFunction(std::stringstream &ss,
            const std::string sSymName, SubArguments &vSubArguments);
    virtual std::string BinFuncName(void) const { return "Sin"; }
};
class OpAbs:public Normal{
public:
    virtual void GenSlidingWindowFunction(std::stringstream &ss,
            const std::string sSymName, SubArguments &vSubArguments);
    virtual std::string GetBottom(void) { return "0.0"; }
    virtual std::string BinFuncName(void) const { return "ScAbs"; }
};
class OpArcCos:public Normal{
public:
    virtual void GenSlidingWindowFunction(std::stringstream &ss,
        const std::string sSymName, SubArguments &vSubArguments);
    virtual std::string GetBottom(void) { return "0.0"; }
    virtual std::string BinFuncName(void) const { return "ScACos"; }
};
class OpArcCosHyp:public Normal{
public:
    virtual void GenSlidingWindowFunction(std::stringstream &ss,
        const std::string sSymName, SubArguments &vSubArguments);
    virtual std::string GetBottom(void) { return "1.0"; }
    virtual std::string BinFuncName(void) const { return "ScACosH"; }
};
class OpTan: public Normal
{
public:
    virtual void GenSlidingWindowFunction(std::stringstream &ss,
            const std::string sSymName, SubArguments &vSubArguments);

    virtual std::string BinFuncName(void) const { return "Tan"; }
};
class OpTanH: public Normal
{
public:
    virtual void GenSlidingWindowFunction(std::stringstream &ss,
            const std::string sSymName, SubArguments &vSubArguments);

    virtual std::string BinFuncName(void) const { return "TanH"; }
};
class OpSqrt: public Normal
{
public:
    virtual void GenSlidingWindowFunction(std::stringstream &ss,
            const std::string sSymName, SubArguments &vSubArguments);

    virtual std::string BinFuncName(void) const { return "Sqrt"; }
};
class OpArcCot:public Normal{
public:
    virtual void GenSlidingWindowFunction(std::stringstream &ss,
        const std::string sSymName, SubArguments &vSubArguments);
    virtual std::string GetBottom(void) { return "0.0"; }
    virtual std::string BinFuncName(void) const { return "ScACot"; }
};
class OpArcCotHyp:public Normal{
public:
    virtual void GenSlidingWindowFunction(std::stringstream &ss,
        const std::string sSymName, SubArguments &vSubArguments);
    virtual std::string GetBottom(void) { return "2.0"; }
    virtual std::string BinFuncName(void) const { return "ScACotH"; }
};
class OpArcSin:public Normal{
public:
    virtual void GenSlidingWindowFunction(std::stringstream &ss,
        const std::string sSymName, SubArguments &vSubArguments);
    virtual std::string GetBottom(void) { return "0.0"; }
    virtual std::string BinFuncName(void) const { return "ScASin"; }
};
class OpArcSinHyp:public Normal{
public:
    virtual void GenSlidingWindowFunction(std::stringstream &ss,
        const std::string sSymName, SubArguments &vSubArguments);
    virtual std::string GetBottom(void) { return "0.0"; }
    virtual std::string BinFuncName(void) const { return "ScASinH"; }
};
class OpTrunc: public Normal
{
public:
    virtual void GenSlidingWindowFunction(std::stringstream &ss,
            const std::string sSymName, SubArguments &vSubArguments);

    virtual std::string BinFuncName(void) const { return "Trunc"; }
};
class OpArcTan2:public Normal{
public:
    virtual void GenSlidingWindowFunction(std::stringstream &ss,
        const std::string sSymName, SubArguments &vSubArguments);
    virtual std::string GetBottom(void) { return "0.0"; }
    virtual std::string BinFuncName(void) const { return "ScATan2"; }
};
class OpArcTan:public Normal{
public:
    virtual void GenSlidingWindowFunction(std::stringstream &ss,
        const std::string sSymName, SubArguments &vSubArguments);
    virtual std::string GetBottom(void) { return "0.0"; }
    virtual std::string BinFuncName(void) const { return "ScATan"; }
};
class OpArcTanH:public Normal{
public:
    virtual void GenSlidingWindowFunction(std::stringstream &ss,
        const std::string sSymName, SubArguments &vSubArguments);
    virtual std::string GetBottom(void) { return "0.0"; }
    virtual std::string BinFuncName(void) const { return "ScATanH"; }
};
class OpBitAnd:public Normal{
public:
    virtual void GenSlidingWindowFunction(std::stringstream &ss,
        const std::string sSymName, SubArguments &vSubArguments);
        virtual std::string GetBottom(void) { return "0.0"; }
    virtual std::string BinFuncName(void) const { return "ScBitAnd"; }
};
class OpLn: public CheckVariables
{
public:
    virtual void GenSlidingWindowFunction(std::stringstream &ss,
            const std::string sSymName, SubArguments &vSubArguments);
    virtual std::string BinFuncName(void) const { return "Ln"; }
};
class OpRound: public CheckVariables
{
public:
    virtual void GenSlidingWindowFunction(std::stringstream &ss,
            const std::string sSymName, SubArguments &vSubArguments);
    virtual std::string BinFuncName(void) const { return "Round"; }
};
class OpCot: public Normal
{
public:
    virtual void GenSlidingWindowFunction(std::stringstream &ss,
            const std::string sSymName, SubArguments &vSubArguments);

    virtual std::string BinFuncName(void) const { return "Cot"; }
};
class OpCoth: public Normal
{
public:
    virtual void GenSlidingWindowFunction(std::stringstream &ss,
            const std::string sSymName, SubArguments &vSubArguments);

    virtual std::string BinFuncName(void) const { return "Coth"; }
};
class OpPower: public Normal
{
public:
    virtual void GenSlidingWindowFunction(std::stringstream &ss,
        const std::string sSymName, SubArguments &vSubArguments);
    virtual std::string BinFuncName(void) const { return "Power"; }
};
class OpOdd: public Normal
{
public:
    virtual void GenSlidingWindowFunction(std::stringstream &ss,
        const std::string sSymName, SubArguments &vSubArguments);
    virtual std::string BinFuncName(void) const { return "Odd"; }
};
class OpFloor: public Normal
{
public:
    virtual void GenSlidingWindowFunction(std::stringstream &ss,
        const std::string sSymName, SubArguments &vSubArguments);
    virtual std::string BinFuncName(void) const { return "Floor"; }
};
class OpCscH: public Normal
{
public:
    virtual void GenSlidingWindowFunction(std::stringstream &ss,
            const std::string sSymName, SubArguments &vSubArguments);
    virtual std::string BinFuncName(void) const { return "CscH"; }
};
class OpExp: public Normal
{
public:
    virtual void GenSlidingWindowFunction(std::stringstream &ss,
            const std::string sSymName, SubArguments &vSubArguments);
    virtual std::string BinFuncName(void) const { return "Exp"; }
};
class OpLog10: public Normal
{
public:
    virtual void GenSlidingWindowFunction(std::stringstream &ss,
            const std::string sSymName, SubArguments &vSubArguments);
    virtual std::string BinFuncName(void) const { return "Log10"; }
};
class OpEven: public Normal
{
public:
    virtual void GenSlidingWindowFunction(std::stringstream &ss,
            const std::string sSymName, SubArguments &vSubArguments);

    virtual std::string BinFuncName(void) const { return "Even"; }
};
class OpAverageIfs: public CheckVariables
{
public:
    virtual void GenSlidingWindowFunction(std::stringstream &ss,
            const std::string sSymName, SubArguments &vSubArguments);
    virtual std::string BinFuncName(void) const { return "AverageIfs"; }
};
class OpCountIfs: public CheckVariables
{
public:
    virtual void GenSlidingWindowFunction(std::stringstream &ss,
            const std::string sSymName, SubArguments &vSubArguments);
    virtual std::string BinFuncName(void) const { return "CountIfs"; }
};
class OpMod: public Normal
{
public:
    virtual void GenSlidingWindowFunction(std::stringstream &ss,
            const std::string sSymName, SubArguments &vSubArguments);

    virtual std::string BinFuncName(void) const { return "Mod"; }
};

class OpCombina: public Normal
{
public:
    virtual void GenSlidingWindowFunction(std::stringstream &ss,
            const std::string sSymName, SubArguments &vSubArguments);

    virtual std::string BinFuncName(void) const { return "Combina"; }
    virtual void BinInlineFun(std::set<std::string>& ,std::set<std::string>& );
};
class OpLog: public Normal
{
public:
    virtual void GenSlidingWindowFunction(std::stringstream &ss,
            const std::string sSymName, SubArguments &vSubArguments);

    virtual std::string BinFuncName(void) const { return "Log"; }
};
}}

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
