/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "op_math.hxx"

#include "formulagroup.hxx"
#include "document.hxx"
#include "formulacell.hxx"
#include "tokenarray.hxx"
#include "compiler.hxx"
#include "interpre.hxx"
#include "formula/vectortoken.hxx"
#include "opinlinefun_math.hxx"
#include <sstream>

using namespace formula;

namespace sc { namespace opencl {

void OpCos::GenSlidingWindowFunction(std::stringstream &ss,
            const std::string sSymName, SubArguments &vSubArguments)
{
    FormulaToken *tmpCur = vSubArguments[0]->GetFormulaToken();
    const formula::SingleVectorRefToken*tmpCurDVR= dynamic_cast<const
          formula::SingleVectorRefToken *>(tmpCur);
    ss << "\ndouble " << sSymName;
    ss << "_"<< BinFuncName() <<"(";
    for (unsigned i = 0; i < vSubArguments.size(); i++)
    {
        if (i)
            ss << ",";
        vSubArguments[i]->GenSlidingWindowDecl(ss);
    }
    ss << ")\n{\n\t";
    ss <<"int gid0=get_global_id(0);\n\t";
    ss << "double arg0 = " << vSubArguments[0]->GenSlidingWindowDeclRef();
    ss << ";\n\t";
#ifdef ISNAN
    ss<< "if(isNan(arg0)||(gid0>=";
    ss<<tmpCurDVR->GetArrayLength();
    ss<<"))\n\t\t";
    ss<<"arg0 = 0;\n\t";
#endif
    ss << "double tmp=cos(arg0);\n\t";
    ss << "return tmp;\n";
    ss << "}";
}

void OpCosh::GenSlidingWindowFunction(std::stringstream &ss,
            const std::string sSymName, SubArguments &vSubArguments)
{
    FormulaToken *tmpCur = vSubArguments[0]->GetFormulaToken();
    const formula::SingleVectorRefToken*tmpCurDVR= dynamic_cast<const
          formula::SingleVectorRefToken *>(tmpCur);
    ss << "\ndouble " << sSymName;
    ss << "_"<< BinFuncName() <<"(";
    for (unsigned i = 0; i < vSubArguments.size(); i++)
    {
        if (i)
            ss << ",";
        vSubArguments[i]->GenSlidingWindowDecl(ss);
    }
    ss << ")\n{\n";
    ss <<"    int gid0=get_global_id(0);\n";
    ss << "    double arg0 = " << vSubArguments[0]->GenSlidingWindowDeclRef();
    ss << ";\n";
#ifdef ISNAN
    ss<< "    if(isNan(arg0)||(gid0>=";
    ss<<tmpCurDVR->GetArrayLength();
    ss<<"))\n";
    ss<<"        arg0 = 0;\n";
#endif
    ss << "    double tmp=cosh(arg0);\n";
    ss << "    return tmp;\n";
    ss << "}";
}

void OpCot::GenSlidingWindowFunction(std::stringstream &ss,
            const std::string sSymName, SubArguments &vSubArguments)
{
    FormulaToken *tmpCur = vSubArguments[0]->GetFormulaToken();
    const formula::SingleVectorRefToken*tmpCurDVR= dynamic_cast<const
          formula::SingleVectorRefToken *>(tmpCur);
    ss << "\ndouble " << sSymName;
    ss << "_"<< BinFuncName() <<"(";
    for (unsigned i = 0; i < vSubArguments.size(); i++)
    {
        if (i)
            ss << ",";
        vSubArguments[i]->GenSlidingWindowDecl(ss);
    }
    ss << ")\n{\n";
    ss <<"    int gid0=get_global_id(0);\n";
    ss << "    double arg0 = " << vSubArguments[0]->GenSlidingWindowDeclRef();
    ss << ";\n";
#ifdef ISNAN
    ss<< "    if(isNan(arg0)||(gid0>=";
    ss<<tmpCurDVR->GetArrayLength();
    ss<<"))\n";
    ss<<"        arg0 = 0;\n";
#endif
    ss << "    double tmp=1/tan(arg0);\n";
    ss << "    return tmp;\n";
    ss << "}";
}

void OpCoth::GenSlidingWindowFunction(std::stringstream &ss,
            const std::string sSymName, SubArguments &vSubArguments)
{
    FormulaToken *tmpCur = vSubArguments[0]->GetFormulaToken();
    const formula::SingleVectorRefToken*tmpCurDVR= dynamic_cast<const
          formula::SingleVectorRefToken *>(tmpCur);
    ss << "\ndouble " << sSymName;
    ss << "_"<< BinFuncName() <<"(";
    for (unsigned i = 0; i < vSubArguments.size(); i++)
    {
        if (i)
            ss << ",";
        vSubArguments[i]->GenSlidingWindowDecl(ss);
    }
    ss << ")\n{\n";
    ss <<"    int gid0=get_global_id(0);\n";
    ss << "    double arg0 = " << vSubArguments[0]->GenSlidingWindowDeclRef();
    ss << ";\n";
#ifdef ISNAN
    ss<< "    if(isNan(arg0)||(gid0>=";
    ss<<tmpCurDVR->GetArrayLength();
    ss<<"))\n";
    ss<<"        arg0 = 0;\n";
#endif
    ss << "    double tmp=1/tanh(arg0);\n";
    ss << "    return tmp;\n";
    ss << "}";
}

void OpCombina::BinInlineFun(std::set<std::string>& decls,
    std::set<std::string>& funs)
{
    decls.insert(bikDecl);
    funs.insert(bik);
}

void OpCombina::GenSlidingWindowFunction(std::stringstream &ss,
            const std::string sSymName, SubArguments &vSubArguments)
{
    ss << "\ndouble " << sSymName;
    ss << "_"<< BinFuncName() <<"(";
    for (unsigned i = 0; i < vSubArguments.size(); i++)
    {
        if (i)
            ss << ",";
        vSubArguments[i]->GenSlidingWindowDecl(ss);
    }
    ss << ")\n{\n";
    ss << "    int gid0 = get_global_id(0);\n";
    ss << "    double tem;\n";
    ss << "    double arg0,arg1;\n";
    for (unsigned int i = 0; i < vSubArguments.size(); i++)
    {
        FormulaToken *pCur = vSubArguments[i]->GetFormulaToken();
        assert(pCur);
        ss << "    arg"<<i<<" = "<<vSubArguments[i]->GenSlidingWindowDeclRef();
        ss << ";\n";
        if(pCur->GetType() == formula::svSingleVectorRef)
        {
#ifdef ISNAN
            const formula::SingleVectorRefToken* pSVR =
            dynamic_cast< const formula::SingleVectorRefToken* >(pCur);
            ss << "    if(isNan(arg" << i <<")||(gid0 >= ";
            ss << pSVR->GetArrayLength();
            ss << "))\n";
            ss << "        arg" << i << " = 0;\n";
        }
        else if (pCur->GetType() == formula::svDouble)
        {
            ss << "    if(isNan(arg" << i <<"))\n";
            ss << "        arg" << i << " = 0;\n";
        }
#endif
    }
    ss << "    arg0 = trunc(arg0);\n";
    ss << "    arg1 = trunc(arg1);\n";
    ss << "    if(arg0 < arg1 || arg0 < 0 || arg1 < 0)\n";
    ss << "        tem = -1;\n";
    ss << "    else if(arg0 == 0 && arg1 == 0)\n";
    ss << "        tem = 0;\n";
    ss << "    else if(arg0 > 0 && arg1 == 0)\n";
    ss << "        tem = 1;\n";
    ss << "    else\n";
    ss << "        tem = bik(arg0+arg1-1,arg1);\n";
    ss << "    double k = tem - trunc(tem);\n";
    ss << "    if(k < 0.5)\n";
    ss << "        tem = trunc(tem);\n";
    ss << "    else\n";
    ss << "        tem = trunc(tem) + 1;";
    ss << "    return tem;\n";
    ss << "}";
}
void OpEven::GenSlidingWindowFunction(std::stringstream &ss,
            const std::string sSymName, SubArguments &vSubArguments)
{
    FormulaToken *tmpCur = vSubArguments[0]->GetFormulaToken();
    const formula::SingleVectorRefToken*tmpCurDVR= dynamic_cast<const
          formula::SingleVectorRefToken *>(tmpCur);
    ss << "\ndouble " << sSymName;
    ss << "_"<< BinFuncName() <<"(";
    for (unsigned i = 0; i < vSubArguments.size(); i++)
    {
        if (i)
            ss << ",";
        vSubArguments[i]->GenSlidingWindowDecl(ss);
    }
    ss << ")\n{\n";
    ss <<"    int gid0=get_global_id(0);\n";
    ss << "    double arg0 = " << vSubArguments[0]->GenSlidingWindowDeclRef();
    ss << ";\n";
#ifdef ISNAN
    ss<< "    if(isNan(arg0)||(gid0>=";
    ss<<tmpCurDVR->GetArrayLength();
    ss<<"))\n";
    ss<<"        arg0 = 0;\n";
#endif
    ss << "    double tmp;\n";
    ss << "    arg0 = arg0 / 2;\n";
    ss << "    if (arg0 < 0)\n";
    ss << "        if (trunc(arg0) == arg0)\n";
    ss << "            tmp = arg0 * 2;\n";
    ss << "        else\n";
    ss << "            tmp = (trunc(arg0) - 1) * 2;\n";
    ss << "    else if (arg0 > 0)\n";
    ss << "         if (trunc(arg0) == arg0)\n";
    ss << "             tmp = arg0 * 2;\n";
    ss << "         else\n";
    ss << "             tmp = (trunc(arg0) + 1) * 2;\n";
    ss << "    else\n";
    ss << "        tmp = 0;\n";
    ss << "    return tmp;\n";
    ss << "}";
}
void OpMod::GenSlidingWindowFunction(std::stringstream &ss,
            const std::string sSymName, SubArguments &vSubArguments)
{
#ifdef ISNAN
    FormulaToken *tmpCur0 = vSubArguments[0]->GetFormulaToken();
    const formula::SingleVectorRefToken*tmpCurDVR0= dynamic_cast<const
          formula::SingleVectorRefToken *>(tmpCur0);
    FormulaToken *tmpCur1 = vSubArguments[0]->GetFormulaToken();
    const formula::SingleVectorRefToken*tmpCurDVR1= dynamic_cast<const
          formula::SingleVectorRefToken *>(tmpCur1);
#endif
    ss << "\ndouble " << sSymName;
    ss << "_"<< BinFuncName() <<"(";
    for (unsigned i = 0; i < vSubArguments.size(); i++)
    {
        if (i)
            ss << ",";
        vSubArguments[i]->GenSlidingWindowDecl(ss);
    }
    ss << ")\n{\n";
    ss <<"    int gid0=get_global_id(0);\n";
    ss << "    double arg0 = " << vSubArguments[0]->GenSlidingWindowDeclRef();
    ss << ";\n";
    ss <<"    double arg1 =" << vSubArguments[1]->GenSlidingWindowDeclRef();
    ss << ";\n";
#ifdef ISNAN
    ss<< "    if(isNan(arg0)||(gid0>=";
    ss<<tmpCurDVR0->GetArrayLength();
    ss<<"))\n";
    ss<<"        arg0 = 0;\n";
#endif
#ifdef ISNAN
    ss<< "    if(isNan(arg1)||(gid0>=";
    ss<<tmpCurDVR1->GetArrayLength();
    ss<<"))\n";
    ss<<"        arg1 = 0;\n";
#endif
    ss << "    double tem;\n";
    ss << "    if(arg1 != 0) {\n";
    ss << "        if(arg0 < 0 && arg1 > 0)\n";
    ss << "            while(arg0 < 0)\n";
    ss << "                arg0 += arg1;\n";
    ss << "        else if (arg0 > 0 && arg1 < 0)\n";
    ss << "            while(arg0 > 0)\n";
    ss << "                arg0 += arg1;\n";
    ss << "        tem = fmod(arg0,arg1);\n";
    ss << "    }\n";
    ss << "    else\n";
    ss << "        tem = 0;\n";
    ss << "    if(arg1 < 0 && tem > 0)\n";
    ss << "        tem = -tem;\n";
    ss << "    return tem;\n";
    ss << "}";
}
void OpLog::GenSlidingWindowFunction(std::stringstream &ss,
            const std::string sSymName, SubArguments &vSubArguments)
{
    ss << "\ndouble " << sSymName;
    ss << "_"<< BinFuncName() <<"(";
    for (unsigned i = 0; i < vSubArguments.size(); i++)
    {
        if (i)
            ss << ",";
        vSubArguments[i]->GenSlidingWindowDecl(ss);
    }
    ss << ")\n{\n";
    ss << "    int gid0 = get_global_id(0);\n";
    ss << "    double tem;\n";
    ss << "    double arg0,arg1;\n";
    for (unsigned int i = 0; i < vSubArguments.size(); i++)
    {
        FormulaToken *pCur = vSubArguments[i]->GetFormulaToken();
        assert(pCur);
        ss << "    arg"<<i<<" = "<<vSubArguments[i]->GenSlidingWindowDeclRef();
        ss << ";\n";
        if(pCur->GetType() == formula::svSingleVectorRef)
        {
#ifdef ISNAN
            const formula::SingleVectorRefToken* pSVR =
            dynamic_cast< const formula::SingleVectorRefToken* >(pCur);
            ss << "    if(isNan(arg" << i <<")||(gid0 >= ";
            ss << pSVR->GetArrayLength();
            ss << "))\n";
            if( i == 0)
                ss << "        arg0 = 0;\n";
            else if ( i == 1)
                ss << "        arg1 = 10;\n";
        }
        else if (pCur->GetType() == formula::svDouble)
        {
            ss << "    if(isNan(arg" << i <<"))\n";
            if( i == 0)
                ss << "        arg0 = 0;\n";
            else if ( i == 1)
                ss << "        arg1 = 10;\n";
        }
#endif
    }
    if (vSubArguments.size() < 2)
        ss << "    arg1 = 10;\n";
    ss << "    tem = log10(arg0)/log10(arg1);;\n";
    ss << "    return tem;\n";
    ss << "}";
}
void OpCsc::GenSlidingWindowFunction(
    std::stringstream &ss, const std::string sSymName, SubArguments &vSubArguments)
{
    FormulaToken *tmpCur = vSubArguments[0]->GetFormulaToken();
    const formula::SingleVectorRefToken*tmpCurDVR= dynamic_cast<const
          formula::SingleVectorRefToken *>(tmpCur);
    ss << "\ndouble " << sSymName;
    ss << "_"<< BinFuncName() <<"(";
    for (unsigned i = 0; i < vSubArguments.size(); i++)
    {
        if (i)
            ss << ",";
        vSubArguments[i]->GenSlidingWindowDecl(ss);
    }
    ss << ")\n{\n\t";
    ss <<"int gid0=get_global_id(0);\n\t";
    ss << "double arg0 = " << vSubArguments[0]->GenSlidingWindowDeclRef();
    ss << ";\n\t";
#ifdef ISNAN
    ss<< "if(isNan(arg0)||(gid0>=";
    ss<<tmpCurDVR->GetArrayLength();
    ss<<"))\n\t\t";
    ss<<"arg0 = 0;\n\t";
#endif
    ss << "double tmp=1/sin(arg0);\n\t";
    ss << "return tmp;\n";
    ss << "}";
}
void OpCountIfs::GenSlidingWindowFunction(std::stringstream &ss,
            const std::string sSymName, SubArguments &vSubArguments)
{
    FormulaToken *tmpCur = vSubArguments[0]->GetFormulaToken();
    const formula::DoubleVectorRefToken*pCurDVR= dynamic_cast<const
         formula::DoubleVectorRefToken *>(tmpCur);
    size_t nCurWindowSize = pCurDVR->GetArrayLength() <
    pCurDVR->GetRefRowSize() ? pCurDVR->GetArrayLength():
    pCurDVR->GetRefRowSize() ;
    ss << "\ndouble " << sSymName;
    ss << "_"<< BinFuncName() <<"(";
    for (unsigned i = 0; i < vSubArguments.size(); i++)
    {
        if (i)
            ss << ",";
        vSubArguments[i]->GenSlidingWindowDecl(ss);
    }
    ss << ")\n    {\n";
    ss <<"    int gid0=get_global_id(0);\n";
    ss << "    double tmp =0;\n";
    ss << "    int i ;\n";
    GenTmpVariables(ss,vSubArguments);
    ss << "    for (i = ";
     if (!pCurDVR->IsStartFixed() && pCurDVR->IsEndFixed()) {
        ss << "gid0; i < "<< nCurWindowSize <<"; i++)\n";
     } else if (pCurDVR->IsStartFixed() && !pCurDVR->IsEndFixed()) {
        ss << "0; i < gid0+"<< nCurWindowSize <<"; i++)\n";
     } else {
        ss << "0; i < "<< nCurWindowSize <<"; i++)\n";
     }
     ss << "    {\n";
     if(!pCurDVR->IsStartFixed() && !pCurDVR->IsEndFixed())
     {
        ss<< "    int doubleIndex =i+gid0;\n";
     }else
     {
        ss<< "    int doubleIndex =i;\n";
     }
     ss<< "    int singleIndex =gid0;\n";
     int m=0;
     for(unsigned j=0;j<vSubArguments.size();j+=2,m++)
     {
        CheckSubArgumentIsNan(ss,vSubArguments,j);
        CheckSubArgumentIsNan(ss,vSubArguments,j+1);
        ss <<"    if(isequal(";
        ss <<"tmp";
        ss <<j;
        ss <<" , ";
        ss << "tmp";
        ss << j+1;
        ss << ")){\n";
     }
    ss << "    tmp =tmp +1;\n";
    for(unsigned j=0;j<=vSubArguments.size();j+=2,m--)
     {
         for(int n = 0;n<m+1;n++)
        {
            ss << "    ";
        }
        ss<< "}\n";
     }
    ss << "return tmp;\n";
    ss << "}";
}
void OpSumIfs::GenSlidingWindowFunction(std::stringstream &ss,
            const std::string sSymName, SubArguments &vSubArguments)
{
    FormulaToken *tmpCur = vSubArguments[0]->GetFormulaToken();
    const formula::DoubleVectorRefToken*pCurDVR= dynamic_cast<const
         formula::DoubleVectorRefToken *>(tmpCur);
    size_t nCurWindowSize = pCurDVR->GetArrayLength() <
    pCurDVR->GetRefRowSize() ? pCurDVR->GetArrayLength():
    pCurDVR->GetRefRowSize() ;
    ss << "\ndouble " << sSymName;
    ss << "_"<< BinFuncName() <<"(";
    for (unsigned i = 0; i < vSubArguments.size(); i++)
    {
        if (i)
            ss << ",";
        vSubArguments[i]->GenSlidingWindowDecl(ss);
    }
    ss << ")\n    {\n";
    ss <<"    int gid0=get_global_id(0);\n";
    ss << "    double tmp =0;\n";
    ss << "    int i ;\n";
    GenTmpVariables(ss,vSubArguments);
    ss << "    for (i = ";
     if (!pCurDVR->IsStartFixed() && pCurDVR->IsEndFixed()) {
        ss << "gid0; i < "<< nCurWindowSize <<"; i++)\n";
     } else if (pCurDVR->IsStartFixed() && !pCurDVR->IsEndFixed()) {
        ss << "0; i < gid0+"<< nCurWindowSize <<"; i++)\n";
     } else {
        ss << "0; i < "<< nCurWindowSize <<"; i++)\n";
     }
     ss << "    {\n";
     if(!pCurDVR->IsStartFixed() && !pCurDVR->IsEndFixed())
     {
        ss<< "    int doubleIndex =i+gid0;\n";
     }else
     {
        ss<< "    int doubleIndex =i;\n";
     }
     ss<< "    int singleIndex =gid0;\n";
     int m=0;
     for(unsigned j=1;j<vSubArguments.size();j+=2,m++)
     {
        CheckSubArgumentIsNan(ss,vSubArguments,j);
        CheckSubArgumentIsNan(ss,vSubArguments,j+1);
        ss <<"    if(isequal(";
        ss <<"tmp";
        ss <<j;
        ss <<" , ";
        ss << "tmp";
        ss << j+1;
        ss << ")){\n";
     }
     CheckSubArgumentIsNan(ss,vSubArguments,0);
    ss << "    tmp += tmp0;\n";
    for(unsigned j=1;j<=vSubArguments.size();j+=2,m--)
     {
         for(int n = 0;n<m+1;n++)
        {
            ss << "    ";
        }
        ss<< "}\n";
     }
    ss << "return tmp;\n";
    ss << "}";
}
void OpCscH::GenSlidingWindowFunction(
    std::stringstream &ss, const std::string sSymName, SubArguments &vSubArguments)
{
    FormulaToken *tmpCur = vSubArguments[0]->GetFormulaToken();
    const formula::SingleVectorRefToken*tmpCurDVR= dynamic_cast<const
          formula::SingleVectorRefToken *>(tmpCur);
    ss << "\ndouble " << sSymName;
    ss << "_"<< BinFuncName() <<"(";
    for (unsigned i = 0; i < vSubArguments.size(); i++)
    {
        if (i)
            ss << ",";
        vSubArguments[i]->GenSlidingWindowDecl(ss);
    }
    ss << ")\n{\n\t";
    ss <<"int gid0=get_global_id(0);\n\t";
    ss << "double arg0 = " << vSubArguments[0]->GenSlidingWindowDeclRef();
    ss << ";\n\t";
#ifdef ISNAN
    ss<< "if(isNan(arg0)||(gid0>=";
    ss<<tmpCurDVR->GetArrayLength();
    ss<<"))\n\t\t";
    ss<<"arg0 = 0;\n\t";
#endif
    ss << "double tmp=1/sinh(arg0);\n\t";
    ss << "return tmp;\n";
    ss << "}";
}
void OpExp::GenSlidingWindowFunction(std::stringstream &ss,
           const std::string sSymName, SubArguments &vSubArguments)
{
    FormulaToken *tmpCur = vSubArguments[0]->GetFormulaToken();
    const formula::SingleVectorRefToken*tmpCurDVR= dynamic_cast<const
          formula::SingleVectorRefToken *>(tmpCur);
    ss << "\ndouble " << sSymName;
    ss << "_"<< BinFuncName() <<"(";
    for (unsigned i = 0; i < vSubArguments.size(); i++)
    {
        if (i)
            ss << ",";
        vSubArguments[i]->GenSlidingWindowDecl(ss);
    }
    ss << ")\n{\n\t";
    ss <<"int gid0=get_global_id(0);\n\t";
    ss << "double arg0 = " << vSubArguments[0]->GenSlidingWindowDeclRef();
    ss << ";\n\t";
#ifdef ISNAN
    ss<< "if(isNan(arg0)||(gid0>=";
    ss<<tmpCurDVR->GetArrayLength();
    ss<<"))\n\t\t";
    ss<<"arg0 = 0;\n\t";
#endif
    ss << "double tmp=exp(arg0);\n\t";
    ss << "return tmp;\n";
    ss << "}";
}
void OpAverageIfs::GenSlidingWindowFunction(std::stringstream &ss,
            const std::string sSymName, SubArguments &vSubArguments)
{
    FormulaToken *tmpCur = vSubArguments[0]->GetFormulaToken();
    const formula::DoubleVectorRefToken*pCurDVR= dynamic_cast<const
         formula::DoubleVectorRefToken *>(tmpCur);
    size_t nCurWindowSize = pCurDVR->GetArrayLength() <
    pCurDVR->GetRefRowSize() ? pCurDVR->GetArrayLength():
    pCurDVR->GetRefRowSize() ;
    ss << "\ndouble " << sSymName;
    ss << "_"<< BinFuncName() <<"(";
    for (unsigned i = 0; i < vSubArguments.size(); i++)
    {
        if (i)
            ss << ",";
        vSubArguments[i]->GenSlidingWindowDecl(ss);
    }
    ss << ")\n    {\n";
    ss <<"     int gid0=get_global_id(0);\n";
    ss << "    double tmp =0;\n";
    ss << "    int count=0;\n";
    ss << "    int i ;\n";
    GenTmpVariables(ss,vSubArguments);
    ss << "    for (i = ";
     if (!pCurDVR->IsStartFixed() && pCurDVR->IsEndFixed()) {
        ss << "gid0; i < "<< nCurWindowSize <<"; i++)\n";
     } else if (pCurDVR->IsStartFixed() && !pCurDVR->IsEndFixed()) {
        ss << "0; i < gid0+"<< nCurWindowSize <<"; i++)\n";
     } else {
        ss << "0; i < "<< nCurWindowSize <<"; i++)\n";
     }
     ss << "    {\n";
     if(!pCurDVR->IsStartFixed() && !pCurDVR->IsEndFixed())
     {
        ss<< "    int doubleIndex =i+gid0;\n";
     }else
     {
        ss<< "    int doubleIndex =i;\n";
     }
     ss<< "    int singleIndex =gid0;\n";
     int m=0;
     for(unsigned j=1;j<vSubArguments.size();j+=2,m++)
     {
        CheckSubArgumentIsNan(ss,vSubArguments,j);
        CheckSubArgumentIsNan(ss,vSubArguments,j+1);
        ss <<"    if(isequal(";
        ss <<"tmp";
        ss <<j;
        ss <<" , ";
        ss << "tmp";
        ss << j+1;
        ss << ")){\n";
     }
     CheckSubArgumentIsNan(ss,vSubArguments,0);
    ss << "    tmp += tmp0;\n";
    ss << "    count++;\n";
    for(unsigned j=1;j<=vSubArguments.size();j+=2,m--)
     {
         for(int n = 0;n<m+1;n++)
        {
            ss << "    ";
        }
        ss<< "}\n";
     }
     ss << "    if(count!=0)\n";
     ss << "        tmp=tmp/count;\n";
     ss << "    else\n";
     ss << "        tmp= 0 ;\n";
    ss << "return tmp;\n";
    ss << "}";
}

void OpLog10::GenSlidingWindowFunction(std::stringstream &ss,
               const std::string sSymName, SubArguments &vSubArguments)
{
    FormulaToken *tmpCur = vSubArguments[0]->GetFormulaToken();
    const formula::SingleVectorRefToken*tmpCurDVR= dynamic_cast<const
          formula::SingleVectorRefToken *>(tmpCur);
    ss << "\ndouble " << sSymName;
    ss << "_"<< BinFuncName() <<"(";
    for (unsigned i = 0; i < vSubArguments.size(); i++)
    {
        if (i)
            ss << ",";
        vSubArguments[i]->GenSlidingWindowDecl(ss);
    }
    ss << ")\n{\n\t";
    ss <<"int gid0=get_global_id(0);\n\t";
    ss << "double arg0 = " << vSubArguments[0]->GenSlidingWindowDeclRef();
    ss << ";\n\t";
#ifdef ISNAN
    ss<< "if(isNan(arg0)||(gid0>=";
    ss<<tmpCurDVR->GetArrayLength();
    ss<<"))\n\t\t";
    ss<<"arg0 = 0;\n\t";
#endif
    ss << "double tmp=log10(arg0);\n\t";
    ss << "return tmp;\n";
    ss << "}";
}

void OpSinh::GenSlidingWindowFunction(std::stringstream &ss,
            const std::string sSymName, SubArguments &vSubArguments)
{
    FormulaToken *tmpCur = vSubArguments[0]->GetFormulaToken();
    const formula::SingleVectorRefToken*tmpCurDVR= dynamic_cast<const
              formula::SingleVectorRefToken *>(tmpCur);
    ss << "\ndouble " << sSymName;
    ss << "_"<< BinFuncName() <<"(";
    for (unsigned i = 0; i < vSubArguments.size(); i++)
    {
        if (i)
            ss << ",";
        vSubArguments[i]->GenSlidingWindowDecl(ss);
    }
    ss <<") {\n";
    ss <<"    int gid0=get_global_id(0);\n";
    ss <<"    double arg0 = " <<
        vSubArguments[0]->GenSlidingWindowDeclRef();
    ss <<";\n";
#ifdef ISNAN
    ss<< "    if(isNan(arg0)||(gid0>=";
    ss<<tmpCurDVR->GetArrayLength();
    ss<<"))\n";
    ss<<"        arg0 = 0;\n";
#endif
    ss << "    double tmp=( exp(arg0)-exp(-arg0) )/2;\n";
    ss << "    return tmp;\n";
    ss << "}";
}
void OpSin::GenSlidingWindowFunction(std::stringstream &ss,
            const std::string sSymName, SubArguments &vSubArguments)
{
    FormulaToken *tmpCur = vSubArguments[0]->GetFormulaToken();
    const formula::SingleVectorRefToken*tmpCurDVR= dynamic_cast<const
          formula::SingleVectorRefToken *>(tmpCur);
    ss << "\ndouble " << sSymName;
    ss << "_"<< BinFuncName() <<"(";
    for (unsigned i = 0; i < vSubArguments.size(); i++)
    {
        if (i)
            ss << ",";
        vSubArguments[i]->GenSlidingWindowDecl(ss);
    }
    ss << ")\n";
    ss << "{\n";
    ss << "    int gid0=get_global_id(0);\n";
    ss << "    double arg0 = "<< vSubArguments[0]->GenSlidingWindowDeclRef();
    ss << ";\n";
#ifdef ISNAN
    ss << "    if(isNan(arg0)||(gid0>=";
    ss << tmpCurDVR->GetArrayLength();
    ss << "))\n";
    ss << "        arg0 = 0;\n";
#endif
    ss << "    double tmp=sin(arg0);\n";
    ss << "    return tmp;\n";
    ss << "}";
}
void OpAbs::GenSlidingWindowFunction(std::stringstream &ss,
    const std::string sSymName, SubArguments &vSubArguments)
{
    ss << "\ndouble " << sSymName;
    ss << "_"<< BinFuncName() <<"(";
    for (unsigned i = 0; i < vSubArguments.size(); i++)
    {
        if (i)
            ss << ",";
        vSubArguments[i]->GenSlidingWindowDecl(ss);
    }
    ss << ") {\n";
    ss << "    int gid0   = get_global_id(0);\n";
    ss << "    double tmp = " << GetBottom() << ";\n";
#ifdef ISNAN
    FormulaToken *tmpCur0 = vSubArguments[0]->GetFormulaToken();
    const formula::SingleVectorRefToken*tmpCurDVR0=
        dynamic_cast<const formula::SingleVectorRefToken *>(tmpCur0);
    ss << "    int buffer_len = ";
    ss << tmpCurDVR0->GetArrayLength();
    ss << ";\n";
    ss << "    if((gid0)>=buffer_len || isNan(";
    ss << vSubArguments[0]->GenSlidingWindowDeclRef();
    ss << "))\n";
    ss << "        tmp = " << GetBottom() << ";\n    else \n";
#endif
    ss << "        tmp = ";
    ss << vSubArguments[0]->GenSlidingWindowDeclRef();
    ss << ";\n";
    ss << "    return fabs(tmp);\n";
    ss << "}";
}
void OpArcCos::GenSlidingWindowFunction(std::stringstream &ss,
    const std::string sSymName, SubArguments &vSubArguments)
{
    ss << "\ndouble " << sSymName;
    ss << "_"<< BinFuncName() <<"(";
    for (unsigned i = 0; i < vSubArguments.size(); i++)
    {
        if (i) ss << ",";
        vSubArguments[i]->GenSlidingWindowDecl(ss);
    }
    ss << ") {\n";
    ss << "    int gid0 = get_global_id(0);\n";
    ss << "    double tmp = " << GetBottom() << ";\n";
#ifdef ISNAN
    FormulaToken *tmpCur0 = vSubArguments[0]->GetFormulaToken();
    const formula::SingleVectorRefToken*tmpCurDVR0=
        dynamic_cast<const formula::SingleVectorRefToken *>(tmpCur0);
    ss << "    int buffer_len = "<< tmpCurDVR0->GetArrayLength()<< ";\n";
    ss << "    if((gid0)>=buffer_len || isNan(";
    ss << vSubArguments[0]->GenSlidingWindowDeclRef()<< "))\n";
    ss << "        tmp = " << GetBottom() << ";\n";
    ss << "    else \n    ";
#endif
    ss << "    tmp = ";
    ss << vSubArguments[0]->GenSlidingWindowDeclRef()<< ";\n";
    ss << "    return acos(tmp);\n";
    ss << "}";
}
void OpArcCosHyp::GenSlidingWindowFunction(std::stringstream &ss,
    const std::string sSymName, SubArguments &vSubArguments)
{
    ss << "\ndouble " << sSymName;
    ss << "_"<< BinFuncName() <<"(";
    for (unsigned i = 0; i < vSubArguments.size(); i++)
    {
        if (i) ss << ",";
        vSubArguments[i]->GenSlidingWindowDecl(ss);
    }
    ss << ") {\n";
    ss << "    int gid0   = get_global_id(0);\n";
    ss << "    double tmp = " << GetBottom() << ";\n";
#ifdef ISNAN
    FormulaToken *tmpCur0 = vSubArguments[0]->GetFormulaToken();
    const formula::SingleVectorRefToken*tmpCurDVR0=
        dynamic_cast<const formula::SingleVectorRefToken *>(tmpCur0);
    ss << "    int buffer_len = " << tmpCurDVR0->GetArrayLength()<< ";\n";
    ss << "    if((gid0)>=buffer_len || isNan(";
    ss << vSubArguments[0]->GenSlidingWindowDeclRef() << "))\n";
    ss << "        tmp = " << GetBottom() << ";\n";
    ss << "    else \n    ";
#endif
    ss << "    tmp = ";
    ss << vSubArguments[0]->GenSlidingWindowDeclRef() << ";\n";
    ss << "    return acosh(tmp);\n";
    ss << "}";
}
void OpTan::GenSlidingWindowFunction(std::stringstream &ss,
            const std::string sSymName, SubArguments &vSubArguments)
{
    FormulaToken *tmpCur = vSubArguments[0]->GetFormulaToken();
    const formula::SingleVectorRefToken*tmpCurDVR= dynamic_cast<const
          formula::SingleVectorRefToken *>(tmpCur);
    ss << "\ndouble " << sSymName;
    ss << "_"<< BinFuncName() <<"(";
    for (unsigned i = 0; i < vSubArguments.size(); i++)
    {
        if (i)
            ss << ",";
        vSubArguments[i]->GenSlidingWindowDecl(ss);
    }
    ss << ")\n";
    ss << "{\n";
    ss << "    int gid0=get_global_id(0);\n";
    ss << "    double arg0 = "<< vSubArguments[0]->GenSlidingWindowDeclRef();
    ss << ";\n";
#ifdef ISNAN
    ss << "    if(isNan(arg0)||(gid0>=";
    ss << tmpCurDVR->GetArrayLength();
    ss << "))\n";
    ss << "        arg0 = 0;\n";
#endif
    ss << "    double tmp=tan(arg0);\n";
    ss << "    return tmp;\n";
    ss << "}";
}
void OpTanH::GenSlidingWindowFunction(std::stringstream &ss,
            const std::string sSymName, SubArguments &vSubArguments)
{
    FormulaToken *tmpCur = vSubArguments[0]->GetFormulaToken();
    const formula::SingleVectorRefToken*tmpCurDVR= dynamic_cast<const
          formula::SingleVectorRefToken *>(tmpCur);
    ss << "\ndouble " << sSymName;
    ss << "_"<< BinFuncName() <<"(";
    for (unsigned i = 0; i < vSubArguments.size(); i++)
    {
        if (i)
            ss << ",";
        vSubArguments[i]->GenSlidingWindowDecl(ss);
    }
    ss << ")\n";
    ss << "{\n";
    ss << "    int gid0=get_global_id(0);\n";
    ss << "    double arg0 = "<< vSubArguments[0]->GenSlidingWindowDeclRef();
    ss << ";\n";
#ifdef ISNAN
    ss << "    if(isNan(arg0)||(gid0>=";
    ss << tmpCurDVR->GetArrayLength();
    ss << "))\n";
    ss << "        arg0 = 0;\n";
#endif
    ss << "    double tmp=tanh(arg0);\n";
    ss << "    return tmp;\n";
    ss << "}";
}
void OpPower::GenSlidingWindowFunction(
    std::stringstream &ss, const std::string sSymName,
    SubArguments &vSubArguments)
{
    FormulaToken *tmpCur = vSubArguments[0]->GetFormulaToken();
    const formula::SingleVectorRefToken*tmpCurDVR= dynamic_cast<const
        formula::SingleVectorRefToken *>(tmpCur);
    ss << "\ndouble " << sSymName;
    ss << "_"<< BinFuncName() <<"(";
    for (unsigned i = 0; i < vSubArguments.size(); i++)
    {
        if (i)
            ss << ",";
        vSubArguments[i]->GenSlidingWindowDecl(ss);
    }
    ss << ")\n{\n";
    ss <<"    int gid0=get_global_id(0);\n";
    ss << "    double arg0 = " << vSubArguments[0]->GenSlidingWindowDeclRef();
    ss << ";\n";
    ss << "    double arg1 = " << vSubArguments[1]->GenSlidingWindowDeclRef();
    ss << ";\n";
#ifdef ISNAN
    ss<< "    if(isNan(arg0)||(gid0>=";
    ss<<tmpCurDVR->GetArrayLength();
    ss<<"))\n";
    ss<<"        arg0 = 0;\n";
    ss<< "    if(isNan(arg1)||(gid0>=";
    ss<<tmpCurDVR->GetArrayLength();
    ss<<"))\n";
    ss<<"        arg1 = 0;\n";
#endif
    ss << "    double tmp=pow(arg0,arg1);\n";
    ss << "    return tmp;\n";
    ss << "}";
}
void OpSqrt::GenSlidingWindowFunction(std::stringstream &ss,
            const std::string sSymName, SubArguments &vSubArguments)
{
    FormulaToken *tmpCur = vSubArguments[0]->GetFormulaToken();
    const formula::SingleVectorRefToken*tmpCurDVR= dynamic_cast<const
          formula::SingleVectorRefToken *>(tmpCur);
    ss << "\ndouble " << sSymName;
    ss << "_"<< BinFuncName() <<"(";
    for (unsigned i = 0; i < vSubArguments.size(); i++)
    {
        if (i)
            ss << ",";
        vSubArguments[i]->GenSlidingWindowDecl(ss);
    }
    ss << ")\n";
    ss << "{\n";
    ss << "    int gid0=get_global_id(0);\n";
    ss << "    double arg0 = "<< vSubArguments[0]->GenSlidingWindowDeclRef();
    ss << ";\n";
#ifdef ISNAN
    ss << "    if(isNan(arg0)||(gid0>=";
    ss << tmpCurDVR->GetArrayLength();
    ss << "))\n";
    ss << "        arg0 = 0;\n";
#endif
    ss << "    double tmp=sqrt(arg0);\n";
    ss << "    return tmp;\n";
    ss << "}";
}
void OpArcCot::GenSlidingWindowFunction(std::stringstream &ss,
    const std::string sSymName, SubArguments &vSubArguments)
{
    ss << "\ndouble " << sSymName;
    ss << "_"<< BinFuncName() <<"(";
    for (unsigned i = 0; i < vSubArguments.size(); i++)
    {
        if (i) ss << ",";
        vSubArguments[i]->GenSlidingWindowDecl(ss);
    }
    ss << ") {\n";
    ss << "    int gid0   = get_global_id(0);\n";
    ss << "    double tmp = " << GetBottom() << ";\n";
#ifdef ISNAN
    FormulaToken *tmpCur0 = vSubArguments[0]->GetFormulaToken();
    const formula::SingleVectorRefToken*tmpCurDVR0=
        dynamic_cast<const formula::SingleVectorRefToken *>(tmpCur0);
    ss << "    int buffer_len = " << tmpCurDVR0->GetArrayLength()<< ";\n";
    ss << "    if((gid0)>=buffer_len || isNan(";
    ss << vSubArguments[0]->GenSlidingWindowDeclRef() << "))\n";
    ss << "        tmp = " << GetBottom() << ";\n";
    ss << "    else \n    ";
#endif
    ss << "    tmp = " << vSubArguments[0]->GenSlidingWindowDeclRef() <<";\n";
    ss << "    return M_PI_2 - atan(tmp);\n";
    ss << "}";
}
void OpArcCotHyp::GenSlidingWindowFunction(std::stringstream &ss,
    const std::string sSymName, SubArguments &vSubArguments)
{
    ss << "\ndouble " << sSymName;
    ss << "_"<< BinFuncName() <<"(";
    for (unsigned i = 0; i < vSubArguments.size(); i++)
    {
        if (i) ss << ",";
        vSubArguments[i]->GenSlidingWindowDecl(ss);
    }
    ss << ") {\n";
    ss << "    int gid0   = get_global_id(0);\n";
    ss << "    double tmp = " << GetBottom() << ";\n";
#ifdef ISNAN
    FormulaToken *tmpCur0 = vSubArguments[0]->GetFormulaToken();
    const formula::SingleVectorRefToken*tmpCurDVR0=
        dynamic_cast<const formula::SingleVectorRefToken *>(tmpCur0);
    ss << "    int buffer_len = " << tmpCurDVR0->GetArrayLength() << ";\n";
    ss << "    if((gid0)>=buffer_len || isNan(";
    ss << vSubArguments[0]->GenSlidingWindowDeclRef() << "))\n";
    ss << "        tmp = " << GetBottom() << ";\n";
    ss << "    else \n    ";
#endif
    ss << "    tmp = " << vSubArguments[0]->GenSlidingWindowDeclRef()<< ";\n";
    ss << "    return 0.5 * log((tmp + 1.0) / (tmp - 1.0));\n";
    ss << "}";
}
void OpArcSin::GenSlidingWindowFunction(std::stringstream &ss,
    const std::string sSymName, SubArguments &vSubArguments)
{
    ss << "\ndouble " << sSymName;
    ss << "_"<< BinFuncName() <<"(";
    for (unsigned i = 0; i < vSubArguments.size(); i++)
    {
        if (i) ss << ",";
        vSubArguments[i]->GenSlidingWindowDecl(ss);
    }
    ss << ") {\n";
    ss << "    int gid0   = get_global_id(0);\n";
    ss << "    double tmp = " << GetBottom() << ";\n";
#ifdef ISNAN
    FormulaToken *tmpCur0 = vSubArguments[0]->GetFormulaToken();
    const formula::SingleVectorRefToken*tmpCurDVR0=
        dynamic_cast<const formula::SingleVectorRefToken *>(tmpCur0);
    ss << "    int buffer_len = " << tmpCurDVR0->GetArrayLength() << ";\n";
    ss << "    if((gid0)>=buffer_len || isNan(";
    ss << vSubArguments[0]->GenSlidingWindowDeclRef() << "))\n";
    ss << "        tmp = " << GetBottom() << ";\n";
    ss << "    else \n    ";
#endif
    ss << "    tmp = " << vSubArguments[0]->GenSlidingWindowDeclRef() << ";\n";
    ss << "    return asin(tmp);\n";
    ss << "}";
}
void OpArcSinHyp::GenSlidingWindowFunction(std::stringstream &ss,
    const std::string sSymName, SubArguments &vSubArguments)
{
    ss << "\ndouble " << sSymName;
    ss << "_"<< BinFuncName() <<"(";
    for (unsigned i = 0; i < vSubArguments.size(); i++)
    {
        if (i) ss << ",";
        vSubArguments[i]->GenSlidingWindowDecl(ss);
    }
    ss << ") {\n";
    ss << "    int gid0   = get_global_id(0);\n";
    ss << "    double tmp = " << GetBottom() << ";\n";
#ifdef ISNAN
    FormulaToken *tmpCur0 = vSubArguments[0]->GetFormulaToken();
    const formula::SingleVectorRefToken*tmpCurDVR0=
        dynamic_cast<const formula::SingleVectorRefToken *>(tmpCur0);
    ss << "    int buffer_len = " << tmpCurDVR0->GetArrayLength() << ";\n";
    ss << "    if((gid0)>=buffer_len || isNan(";
    ss << vSubArguments[0]->GenSlidingWindowDeclRef() << "))\n";
    ss << "        tmp = " << GetBottom() << ";\n";
    ss << "    else \n    ";
#endif
    ss << "    tmp = " << vSubArguments[0]->GenSlidingWindowDeclRef() << ";\n";
    ss << "    return asinh(tmp);\n";
    ss << "}";
}
void OpArcTan2::GenSlidingWindowFunction(std::stringstream &ss,
    const std::string sSymName, SubArguments &vSubArguments)
{
    ss << "\ndouble " << sSymName;
    ss << "_"<< BinFuncName() <<"(";
    for (unsigned i = 0; i < vSubArguments.size(); i++)
    {
        if (i) ss << ",";
        vSubArguments[i]->GenSlidingWindowDecl(ss);
    }
    ss << ") {\n";
    ss << "    int gid0 = get_global_id(0);\n";
    ss << "    double x_num = " << GetBottom() << ";\n";
    ss << "    double y_num = " << GetBottom() << ";\n";
#ifdef ISNAN
    FormulaToken *iXNum = vSubArguments[0]->GetFormulaToken();
    const formula::SingleVectorRefToken*tmpCurDVRX=
        dynamic_cast<const formula::SingleVectorRefToken *>(iXNum);
    FormulaToken *iYNum = vSubArguments[1]->GetFormulaToken();
    const formula::SingleVectorRefToken*tmpCurDVRY=
        dynamic_cast<const formula::SingleVectorRefToken *>(iYNum);
    ss << "    int buffer_x_len = " << tmpCurDVRX->GetArrayLength() << ";\n";
    ss << "    int buffer_y_len = " << tmpCurDVRY->GetArrayLength() << ";\n";
    ss << "    if((gid0)>=buffer_x_len || isNan(";
    ss << vSubArguments[0]->GenSlidingWindowDeclRef() << "))\n";
    ss << "        x_num = " << GetBottom() << ";\n";
    ss << "    else \n    ";
#endif
    ss << "    x_num = "<< vSubArguments[0]->GenSlidingWindowDeclRef() << ";\n";
#ifdef ISNAN
    ss << "    if((gid0)>=buffer_y_len || isNan(";
    ss << vSubArguments[1]->GenSlidingWindowDeclRef() << "))\n";
    ss << "        y_num = " << GetBottom() << ";\n";
    ss << "    else \n    ";
#endif
    ss << "    y_num = "<< vSubArguments[1]->GenSlidingWindowDeclRef() << ";\n";
    ss << "    return atan2(y_num, x_num);\n";
    ss << "}";
}
void OpArcTan::GenSlidingWindowFunction(std::stringstream &ss,
    const std::string sSymName, SubArguments &vSubArguments)
{
    ss << "\ndouble " << sSymName;
    ss << "_"<< BinFuncName() <<"(";
    for (unsigned i = 0; i < vSubArguments.size(); i++)
    {
        if (i) ss << ",";
        vSubArguments[i]->GenSlidingWindowDecl(ss);
    }
    ss << ") {\n";
    ss << "    int gid0 = get_global_id(0);\n";
    ss << "    double tmp = " << GetBottom() << ";\n";
#ifdef ISNAN
    FormulaToken *tmpCur0 = vSubArguments[0]->GetFormulaToken();
    const formula::SingleVectorRefToken*tmpCurDVR0=
        dynamic_cast<const formula::SingleVectorRefToken *>(tmpCur0);
    ss << "    int buffer_len = " << tmpCurDVR0->GetArrayLength() << ";\n";
    ss << "    if((gid0)>=buffer_len || isNan(";
    ss << vSubArguments[0]->GenSlidingWindowDeclRef() << "))\n";
    ss << "        tmp = " << GetBottom() << ";\n";
    ss << "    else\n    ";
#endif
    ss << "    tmp = " << vSubArguments[0]->GenSlidingWindowDeclRef() << ";\n";
    ss << "    return atan(tmp);\n";
    ss << "}";
}
void OpArcTanH::GenSlidingWindowFunction(std::stringstream &ss,
    const std::string sSymName, SubArguments &vSubArguments)
{
    ss << "\ndouble " << sSymName;
    ss << "_"<< BinFuncName() <<"(";
    for (unsigned i = 0; i < vSubArguments.size(); i++)
    {
        if (i) ss << ",";
        vSubArguments[i]->GenSlidingWindowDecl(ss);
    }
    ss << ") {\n";
    ss << "    int gid0 = get_global_id(0);\n";
    ss << "    double tmp = " << GetBottom() << ";\n";
#ifdef ISNAN
    FormulaToken *tmpCur0 = vSubArguments[0]->GetFormulaToken();
    const formula::SingleVectorRefToken*tmpCurDVR0=
        dynamic_cast<const formula::SingleVectorRefToken *>(tmpCur0);
    ss << "    int buffer_len = " << tmpCurDVR0->GetArrayLength() << ";\n";
    ss << "    if((gid0)>=buffer_len || isNan(";
    ss << vSubArguments[0]->GenSlidingWindowDeclRef() << "))\n";
    ss << "        tmp = " << GetBottom() << ";\n";
    ss << "    else \n    ";
#endif
    ss << "    tmp = " << vSubArguments[0]->GenSlidingWindowDeclRef() << ";\n";
    ss << "    return atanh(tmp);\n";
    ss << "}";
}
void OpBitAnd::GenSlidingWindowFunction(std::stringstream &ss,
    const std::string sSymName, SubArguments &vSubArguments)
{
    ss << "\ndouble " << sSymName;
    ss << "_"<< BinFuncName() <<"(";
    for (unsigned i = 0; i < vSubArguments.size(); i++)
    {
        if (i) ss << ",";
        vSubArguments[i]->GenSlidingWindowDecl(ss);
    }
    ss << ") {\n";
    ss << "    int gid0 = get_global_id(0);\n";
    ss << "    double num1 = " << GetBottom() << ";\n";
    ss << "    double num2 = " << GetBottom() << ";\n";
#ifdef ISNAN
    FormulaToken *iNum1 = vSubArguments[0]->GetFormulaToken();
    const formula::SingleVectorRefToken* tmpCurDVRNum1=
        dynamic_cast<const formula::SingleVectorRefToken *>(iNum1);
    FormulaToken *iNum2 = vSubArguments[1]->GetFormulaToken();
    const formula::SingleVectorRefToken* tmpCurDVRNum2=
        dynamic_cast<const formula::SingleVectorRefToken *>(iNum2);
    ss << "    int buffer_num1_len = "<<tmpCurDVRNum1->GetArrayLength()<<";\n";
    ss << "    int buffer_num2_len = "<<tmpCurDVRNum2->GetArrayLength()<<";\n";
    ss << "    if((gid0)>=buffer_num1_len || isNan(";
    ss << vSubArguments[0]->GenSlidingWindowDeclRef() << "))\n";
    ss << "        num1 = " << GetBottom() << ";\n";
    ss << "    else \n    ";
#endif
    ss << "    num1 = " << vSubArguments[0]->GenSlidingWindowDeclRef() << ";\n";
#ifdef ISNAN
    ss << "    if((gid0)>=buffer_num2_len || isNan(";
    ss << vSubArguments[1]->GenSlidingWindowDeclRef() << "))\n";
    ss << "        num2 = " << GetBottom() << ";\n";
    ss << "    else \n    ";
#endif
    ss << "    num2 = " << vSubArguments[1]->GenSlidingWindowDeclRef() << ";\n";
    ss << "    return (int)num1 & (int)num2;\n";
    ss << "}";
}
void OpLn::GenSlidingWindowFunction(
    std::stringstream &ss, const std::string sSymName, SubArguments &vSubArguments)
{
    ss << "\ndouble " << sSymName;
    ss << "_"<< BinFuncName() <<"(";
    for (unsigned i = 0; i < vSubArguments.size(); i++)
    {
        if (i)
            ss << ",";
        vSubArguments[i]->GenSlidingWindowDecl(ss);
    }
    ss << ")\n{\n";
    ss << "    int gid0=get_global_id(0);\n";
    ss << "    int singleIndex =  gid0;\n";

    GenTmpVariables(ss,vSubArguments);
    CheckAllSubArgumentIsNan(ss,vSubArguments);

    ss << "    double tmp=log1p(tmp0-1);\n";
    ss << "    return tmp;\n";
    ss << "}";
}

void OpRound::GenSlidingWindowFunction(std::stringstream &ss,
             const std::string sSymName, SubArguments &vSubArguments)
{
    ss << "\ndouble " << sSymName;
    ss << "_"<< BinFuncName() <<"(";
    for (unsigned i = 0; i < vSubArguments.size(); i++)
    {
        if (i)
            ss << ",";
        vSubArguments[i]->GenSlidingWindowDecl(ss);
    }
    ss << ")\n{\n";
    ss << "    int gid0=get_global_id(0);\n";
    ss << "    int singleIndex =  gid0;\n";
    GenTmpVariables(ss,vSubArguments);
    CheckAllSubArgumentIsNan(ss,vSubArguments);
    ss << "    for(int i=0;i<tmp1;i++)\n";
    ss << "        tmp0 = tmp0 * 10;\n";
    ss << "    double tmp=round(tmp0);\n";
    ss << "    for(int i=0;i<tmp1;i++)\n";
    ss << "        tmp = tmp / 10;\n";
    ss << "    return tmp;\n";
    ss << "}";
}
void OpOdd::GenSlidingWindowFunction(
    std::stringstream &ss, const std::string sSymName,
    SubArguments &vSubArguments)
{
    FormulaToken *tmpCur = vSubArguments[0]->GetFormulaToken();
    const formula::SingleVectorRefToken*tmpCurDVR= dynamic_cast<const
        formula::SingleVectorRefToken *>(tmpCur);
    ss << Math_Intg_Str;
    ss << "\ndouble " << sSymName;
    ss << "_"<< BinFuncName() <<"(";
    for (unsigned i = 0; i < vSubArguments.size(); i++)
    {
        if (i)
            ss << ",";
        vSubArguments[i]->GenSlidingWindowDecl(ss);
    }
    ss << ")\n{\n";
    ss <<"    int gid0=get_global_id(0);\n";
    ss << "    double tmp=0;\n";
    ss << "    double arg0 = " << vSubArguments[0]->GenSlidingWindowDeclRef();
    ss << ";\n";
#ifdef ISNAN
    ss<< "    if(isNan(arg0)||(gid0>=";
    ss<<tmpCurDVR->GetArrayLength();
    ss<<"))\n";
    ss<<"        arg0 = 0;\n";
#endif
    ss << "    if (arg0 > 0.0 ){\n";
    ss << "        tmp=Intg(arg0);\n";
    ss << "        if(tmp-trunc(tmp/2)*2 == 0)\n";
    ss << "            tmp=tmp+1;\n";
    ss << "    }else if (arg0 < 0.0 ){\n";
    ss << "        tmp=Intg(arg0);\n";
    ss << "        if(tmp-trunc(tmp/2)*2 == 0)\n";
    ss << "            tmp=tmp-1.0;\n";
    ss << "    }else if (arg0 == 0.0 )\n";
    ss << "            tmp=1.0;\n";
    ss << "    return tmp;\n";
    ss << "}";
}
void OpTrunc::GenSlidingWindowFunction(std::stringstream &ss,
            const std::string sSymName, SubArguments &vSubArguments)
{
    ss << "\ndouble " << sSymName;
    ss << "_"<< BinFuncName() <<"(";
    for (unsigned i = 0; i < vSubArguments.size(); i++)
    {
        if (i)
            ss << ",";
        vSubArguments[i]->GenSlidingWindowDecl(ss);
    }
    ss << ")\n";
    ss << "{\n";
    ss << "    int gid0=get_global_id(0);\n";
    ss << "    double arg[2];\n";
    for( unsigned i=0; i < vSubArguments.size(); ++i)
    {
        FormulaToken *tmpCur = vSubArguments[i]->GetFormulaToken();
        assert(tmpCur);
        if(ocPush == vSubArguments[i]->GetFormulaToken()->GetOpCode())
        {
            if(tmpCur->GetType() == formula::svDoubleVectorRef)
            {
                const formula::DoubleVectorRefToken* tmpCurDVR =
                    dynamic_cast<
                    const formula::DoubleVectorRefToken *>(tmpCur);
                ss << "    int i = 0;\n";
                ss << "    arg["<<i<<"] = ";
                ss << vSubArguments[i]->GenSlidingWindowDeclRef();
                ss << ";\n";
#ifdef ISNAN
                ss << "    if(isNan(arg["<<i;
                ss << "])||(gid0>=";
                ss << tmpCurDVR->GetArrayLength();
                ss << "))\n";
                ss << "        arg["<<i;
                ss << "] = 0;\n";
#endif
            }
            else if(tmpCur->GetType() == formula::svSingleVectorRef)
            {
                const formula::SingleVectorRefToken* tmpCurDVR=
                      dynamic_cast<
                      const formula::SingleVectorRefToken *>(tmpCur);
                ss << "    arg["<<i<<"] = ";
                ss << vSubArguments[i]->GenSlidingWindowDeclRef();
                ss << ";\n";
#ifdef ISNAN
                ss << "    if(isNan(arg["<<i;
                ss << "])||(gid0>=";
                ss << tmpCurDVR->GetArrayLength();
                ss << "))\n";
                ss << "        arg["<<i;
                ss << "] = 0;\n";
#endif
            }
            else if(tmpCur->GetType() == formula::svDouble)
            {
                ss << "        arg["<<i<<"] = ";
                ss << tmpCur->GetDouble() << ";\n";
            }
        }
        else
        {
            ss << "        arg["<<i<<"] = ";
            ss << vSubArguments[i]->GenSlidingWindowDeclRef();
            ss << ";\n";
        }
    }
    ss << "    int n = (int)arg[1];\n";
    ss << "    int nn = 1;\n";
    ss << "    for(int i=0; i<n; ++i)\n";
    ss << "        nn *= 10;\n";
    ss << "    n = (int)(arg[0] * nn);\n";
    ss << "    arg[0] = (double)n / nn;\n";
    ss << "    return arg[0];\n";
    ss << "}";
}
void OpFloor::GenSlidingWindowFunction(
    std::stringstream &ss, const std::string sSymName,
    SubArguments &vSubArguments)
{
    FormulaToken *tmpCur = vSubArguments[0]->GetFormulaToken();
    const formula::SingleVectorRefToken*tmpCurDVR= dynamic_cast<const
        formula::SingleVectorRefToken *>(tmpCur);
    ss << "\ndouble " << sSymName;
    ss << "_"<< BinFuncName() <<"(";
    for (unsigned i = 0; i < vSubArguments.size(); i++)
    {
        if (i)
            ss << ",";
        vSubArguments[i]->GenSlidingWindowDecl(ss);
    }
    ss << ")\n{\n";
    ss <<"    int gid0=get_global_id(0);\n";
    ss << "    double arg0 = " << vSubArguments[0]->GenSlidingWindowDeclRef();
    ss << ";\n";
    ss << "    double arg1 = " << vSubArguments[1]->GenSlidingWindowDeclRef();
    ss << ";\n";
    ss << "    double arg2 = " << vSubArguments[2]->GenSlidingWindowDeclRef();
    ss << ";\n";
#ifdef ISNAN
    ss<< "    if(isNan(arg0)||(gid0>=";
    ss<<tmpCurDVR->GetArrayLength();
    ss<<"))\n";
    ss<<"        arg0 = 0;\n";
    ss<< "    if(isNan(arg1)||(gid0>=";
    ss<<tmpCurDVR->GetArrayLength();
    ss<<"))\n";
    ss<<"        arg1 = 0;\n";
    ss<< "    if(isNan(arg2)||(gid0>=";
    ss<<tmpCurDVR->GetArrayLength();
    ss<<"))\n";
    ss<<"        arg2 = 0;\n";
#endif
    ss <<"    if(arg1==0.0)\n";
    ss <<"        return 0.0;\n";
    ss <<"    else if(arg0*arg1<0.0)\n";
    ss <<"        return 0.0000000001;\n";
    ss <<"    else if(arg2==0.0&&arg0<0.0)\n";
    ss <<"        return (trunc(arg0/arg1)+1)*arg1;\n";
    ss <<"    else\n";
    ss <<"        return trunc(arg0/arg1)*arg1;\n";
    ss << "}\n";
}
void OpBitOr::GenSlidingWindowFunction(std::stringstream &ss,
    const std::string sSymName, SubArguments &vSubArguments)
{
    ss << "\ndouble " << sSymName;
    ss << "_"<< BinFuncName() <<"(";
    for (unsigned i = 0; i < vSubArguments.size(); i++)
    {
        if (i) ss << ",";
        vSubArguments[i]->GenSlidingWindowDecl(ss);
    }
    ss << ") {\n";
    ss << "    int gid0   = get_global_id(0);\n";
    ss << "    double num1 = " << GetBottom() << ";\n";
    ss << "    double num2 = " << GetBottom() << ";\n";
#ifdef ISNAN
    FormulaToken *iNum1 = vSubArguments[0]->GetFormulaToken();
    const formula::SingleVectorRefToken* tmpCurDVRNum1=
        dynamic_cast<const formula::SingleVectorRefToken *>(iNum1);
    FormulaToken *iNum2 = vSubArguments[1]->GetFormulaToken();
    const formula::SingleVectorRefToken* tmpCurDVRNum2=
        dynamic_cast<const formula::SingleVectorRefToken *>(iNum2);
    ss << "    int buffer_num1_len = "<<tmpCurDVRNum1->GetArrayLength()<<";\n";
    ss << "    int buffer_num2_len = "<<tmpCurDVRNum2->GetArrayLength()<<";\n";
    ss << "    if((gid0)>=buffer_num1_len || isNan(";
    ss << vSubArguments[0]->GenSlidingWindowDeclRef() << "))\n";
    ss << "        num1 = " << GetBottom() << ";\n";
    ss << "    else \n    ";
#endif
    ss << "    num1 = floor(" << vSubArguments[0]->GenSlidingWindowDeclRef();
    ss << ");\n";
#ifdef ISNAN
    ss << "    if((gid0)>=buffer_num2_len || isNan(";
    ss << vSubArguments[1]->GenSlidingWindowDeclRef() << "))\n";
    ss << "        num2 = " << GetBottom() << ";\n";
    ss << "    else\n    ";
#endif
    ss << "    num2 = floor(" << vSubArguments[1]->GenSlidingWindowDeclRef();
    ss << ");\n";
    ss << "    return (long)num1 | (long)num2;\n";
    ss << "}";
}
void OpBitXor::GenSlidingWindowFunction(std::stringstream &ss,
    const std::string sSymName, SubArguments &vSubArguments)
{
    ss << "\ndouble " << sSymName;
    ss << "_"<< BinFuncName() <<"(";
    for (unsigned i = 0; i < vSubArguments.size(); i++)
    {
        if (i) ss << ",";
        vSubArguments[i]->GenSlidingWindowDecl(ss);
    }
    ss << ") {\n";
    ss << "    int gid0 = get_global_id(0);\n";
    ss << "    double num1 = " << GetBottom() << ";\n";
    ss << "    double num2 = " << GetBottom() << ";\n";
#ifdef ISNAN
    FormulaToken *iNum1 = vSubArguments[0]->GetFormulaToken();
    const formula::SingleVectorRefToken* tmpCurDVRNum1=
        dynamic_cast<const formula::SingleVectorRefToken *>(iNum1);
    FormulaToken *iNum2 = vSubArguments[1]->GetFormulaToken();
    const formula::SingleVectorRefToken* tmpCurDVRNum2=
        dynamic_cast<const formula::SingleVectorRefToken *>(iNum2);
    ss << "    int buffer_num1_len = " << tmpCurDVRNum1->GetArrayLength() << ";\n";
    ss << "    int buffer_num2_len = " << tmpCurDVRNum2->GetArrayLength() << ";\n";

    ss << "    if((gid0)>=buffer_num1_len || isNan(";
    ss << vSubArguments[0]->GenSlidingWindowDeclRef() << "))\n";
    ss << "        num1 = " << GetBottom() << ";\n";
    ss << "    else\n    ";
#endif
    ss << "    num1 = floor(" << vSubArguments[0]->GenSlidingWindowDeclRef();
    ss << ");\n";
#ifdef ISNAN
    ss << "    if((gid0)>=buffer_num2_len || isNan(";
    ss << vSubArguments[1]->GenSlidingWindowDeclRef() << "))\n";
    ss << "        num2 = " << GetBottom() << ";\n";
    ss << "    else\n    ";
#endif
    ss << "    num2 = floor(" << vSubArguments[1]->GenSlidingWindowDeclRef();
    ss << ");\n";
    ss << "    return (long)num1 ^ (long)num2;\n";
    ss << "}";
}
void OpBitLshift::GenSlidingWindowFunction(std::stringstream &ss,
    const std::string sSymName, SubArguments &vSubArguments)
{
    ss << "\ndouble " << sSymName;
    ss << "_"<< BinFuncName() <<"(";
    for (unsigned i = 0; i < vSubArguments.size(); i++)
    {
        if (i) ss << ",";
        vSubArguments[i]->GenSlidingWindowDecl(ss);
    }
    ss << ") {\n";
    ss << "    int gid0 = get_global_id(0);\n";
    ss << "    double num = " << GetBottom() << ";\n";
    ss << "    double shift_amount = " << GetBottom() << ";\n";
#ifdef ISNAN
    FormulaToken *iNum = vSubArguments[0]->GetFormulaToken();
    const formula::SingleVectorRefToken* tmpCurDVRNum=
        dynamic_cast<const formula::SingleVectorRefToken*>(iNum);
    FormulaToken *iShiftAmount = vSubArguments[1]->GetFormulaToken();
    const formula::SingleVectorRefToken* tmpCurDVRShiftAmount=
        dynamic_cast<const formula::SingleVectorRefToken*>(iShiftAmount);
    ss << "    int buffer_num_len = "<< tmpCurDVRNum->GetArrayLength()<<";\n";
    ss << "    int buffer_shift_amount_len = ";
    ss << tmpCurDVRShiftAmount->GetArrayLength() << ";\n";
    ss << "    if((gid0)>=buffer_num_len || isNan(";
    ss << vSubArguments[0]->GenSlidingWindowDeclRef() << "))\n";
    ss << "        num = " << GetBottom() << ";\n";
    ss << "    else\n    ";
#endif
    ss << "    num = floor(";
    ss << vSubArguments[0]->GenSlidingWindowDeclRef() << ");\n";
#ifdef ISNAN
    ss << "    if((gid0)>=buffer_shift_amount_len || isNan(";
    ss << vSubArguments[1]->GenSlidingWindowDeclRef() << "))\n";
    ss << "        shift_amount = " << GetBottom() << ";\n";
    ss << "    else\n    ";
#endif
    ss << "    shift_amount = floor(";
    ss << vSubArguments[1]->GenSlidingWindowDeclRef() << ");\n";
    ss << "    return floor(" << "shift_amount >= 0 ? ";
    ss << "num * pow(2.0, shift_amount) : ";
    ss << "num / pow(2.0, fabs(shift_amount)));\n";
    ss << "}";
}
void OpBitRshift::GenSlidingWindowFunction(std::stringstream &ss,
    const std::string sSymName, SubArguments &vSubArguments)
{
    ss << "\ndouble " << sSymName;
    ss << "_"<< BinFuncName() <<"(";
    for (unsigned i = 0; i < vSubArguments.size(); i++)
    {
        if (i) ss << ",";
        vSubArguments[i]->GenSlidingWindowDecl(ss);
    }
    ss << ") {\n";
    ss << "    int gid0 = get_global_id(0);\n";
    ss << "    double num = " << GetBottom() << ";\n";
    ss << "    double shift_amount = " << GetBottom() << ";\n";
#ifdef ISNAN
    FormulaToken *iNum = vSubArguments[0]->GetFormulaToken();
    const formula::SingleVectorRefToken* tmpCurDVRNum=
        dynamic_cast<const formula::SingleVectorRefToken*>(iNum);
    FormulaToken *iShiftAmount = vSubArguments[1]->GetFormulaToken();
    const formula::SingleVectorRefToken* tmpCurDVRShiftAmount=
        dynamic_cast<const formula::SingleVectorRefToken*>(iShiftAmount);
    ss << "    int buffer_num_len = ";
    ss << tmpCurDVRNum->GetArrayLength() << ";\n";
    ss << "    int buffer_shift_amount_len = ";
    ss << tmpCurDVRShiftAmount->GetArrayLength() << ";\n";

    ss << "    if((gid0)>=buffer_num_len || isNan(";
    ss << vSubArguments[0]->GenSlidingWindowDeclRef() << "))\n";
    ss << "        num = " << GetBottom() << ";\n";
    ss << "    else\n    ";
#endif
    ss << "    num = floor(";
    ss << vSubArguments[0]->GenSlidingWindowDeclRef() << ");\n";
#ifdef ISNAN
    ss << "    if((gid0)>=buffer_shift_amount_len || isNan(";
    ss << vSubArguments[1]->GenSlidingWindowDeclRef() << "))\n";
    ss << "        shift_amount = " <<GetBottom()<< ";\n";
    ss << "    else\n    ";
#endif
    ss << "    shift_amount = floor(";
    ss << vSubArguments[1]->GenSlidingWindowDeclRef() << ");\n";
    ss << "    return floor(";
    ss << "shift_amount >= 0 ? num / pow(2.0, shift_amount) : ";
    ss << "num * pow(2.0, fabs(shift_amount)));\n";
    ss << "}";
}
void OpSumSQ::GenSlidingWindowFunction(std::stringstream &ss,
            const std::string sSymName, SubArguments &vSubArguments)
{
    ss << "\ndouble " << sSymName;
    ss << "_"<< BinFuncName() <<"(";
    for (unsigned i = 0; i < vSubArguments.size(); ++i)
    {
        if (i)
            ss << ",";
        vSubArguments[i]->GenSlidingWindowDecl(ss);
    }
    ss << ")\n";
    ss << "{\n";
    ss << "    int gid0=get_global_id(0);\n";
    ss << "    double sum = 0.0f, arg;\n";
    for( unsigned i=0; i < vSubArguments.size(); ++i)
    {
        FormulaToken *tmpCur = vSubArguments[i]->GetFormulaToken();
        assert(tmpCur);
        if(ocPush == vSubArguments[i]->GetFormulaToken()->GetOpCode())
        {
            if (tmpCur->GetType() == formula::svDoubleVectorRef)
            {
                const formula::DoubleVectorRefToken* pDVR =
            dynamic_cast<const formula::DoubleVectorRefToken *>(tmpCur);
                size_t nCurWindowSize = pDVR->GetRefRowSize();
                ss << "    for (int i = ";
                if (!pDVR->IsStartFixed() && pDVR->IsEndFixed())
                {
#ifdef  ISNAN
                    ss << "gid0; i < " << pDVR->GetArrayLength();
                    ss << " && i < " << nCurWindowSize  << "; ++i)\n";
                    ss << "    {\n";
#else
                    ss << "gid0; i < "<< nCurWindowSize << "; ++i)\n";
                    ss << "    {\n";
#endif
                }
                else if (pDVR->IsStartFixed() && !pDVR->IsEndFixed())
                {
#ifdef  ISNAN
                    ss << "0; i < " << pDVR->GetArrayLength();
                    ss << " && i < gid0+"<< nCurWindowSize << "; ++i)\n";
                    ss << "    {\n";
#else
                    ss << "0; i < gid0+"<< nCurWindowSize << "; ++i)\n";
                    ss << "    {\n";
#endif
                }
                else if (!pDVR->IsStartFixed() && !pDVR->IsEndFixed())
                {
#ifdef  ISNAN
                    ss << "0; i + gid0 < " << pDVR->GetArrayLength();
                    ss << " &&  i < "<< nCurWindowSize << "; ++i)\n";
                    ss << "    {\n";
#else
                    ss << "0; i < "<< nCurWindowSize << "; ++i)\n";
                    ss << "    {\n";
#endif
                }
                else
                {
#ifdef  ISNAN
                    ss << "0; i < "<< nCurWindowSize << "; ++i)\n";
                    ss << "    {\n";
#else
                    ss << "0; i < "<< nCurWindowSize << "; ++i)\n";
                    ss << "    {\n";
#endif
                }
                ss << "        arg = ";
                ss << vSubArguments[i]->GenSlidingWindowDeclRef();
                ss << ";\n";
#ifdef  ISNAN
                ss << "        if (isNan(arg))\n";
                ss << "            continue;\n";
#endif
                ss << "        sum += arg*arg;\n";
                ss << "    }\n";
            }
            else if(tmpCur->GetType() == formula::svSingleVectorRef)
            {
                const formula::SingleVectorRefToken* tmpCurDVR=
                      dynamic_cast<
                      const formula::SingleVectorRefToken *>(tmpCur);
                ss << "    arg = ";
                ss << vSubArguments[i]->GenSlidingWindowDeclRef();
                ss << ";\n";
#ifdef ISNAN
                ss << "    if(isNan(arg)||(gid0>=";
                ss << tmpCurDVR->GetArrayLength();
                ss << "))\n";
                ss << "        arg = 0.0f;\n";
                ss << "    sum += arg * arg;\n";
#endif
            }
            else if(tmpCur->GetType() == formula::svDouble)
            {
                ss << "        arg = ";
                ss << tmpCur->GetDouble() << ";\n";
                ss << "        sum += arg*arg;\n";
            }
        }
        else
        {
            ss << "        arg = ";
            ss << vSubArguments[i]->GenSlidingWindowDeclRef();
            ss << ";\n";
            ss << "        sum += arg*arg;\n";
        }
    }
    ss << "    return sum;\n";
    ss << "}";
}
void OpSqrtPi::GenSlidingWindowFunction(std::stringstream &ss,
            const std::string sSymName, SubArguments &vSubArguments)
{
    ss << "\ndouble " << sSymName;
    ss << "_"<< BinFuncName() <<"(";
    for (unsigned i = 0; i < vSubArguments.size(); i++)
    {
        if (i)
            ss << ",";
        vSubArguments[i]->GenSlidingWindowDecl(ss);
    }
    ss << ")\n";
    ss << "{\n";
    ss << "    int gid0=get_global_id(0);\n";
    ss << "    double arg0 = 0.0f;\n";
    FormulaToken *tmpCur = vSubArguments[0]->GetFormulaToken();
    assert(tmpCur);
    if(ocPush == vSubArguments[0]->GetFormulaToken()->GetOpCode())
    {
        if(tmpCur->GetType() == formula::svSingleVectorRef)
        {
            const formula::SingleVectorRefToken*tmpCurDVR=
                dynamic_cast
                <const formula::SingleVectorRefToken *>(tmpCur);
            ss << "    arg0 = ";
            ss << vSubArguments[0]->GenSlidingWindowDeclRef();
            ss << ";\n";
#ifdef ISNAN
            ss << "    if(isNan(";
            ss << vSubArguments[0]->GenSlidingWindowDeclRef();
            ss << ")||(gid0>=";
            ss << tmpCurDVR->GetArrayLength();
            ss << "))\n";
            ss << "    { arg0 = 0.0f; }\n";
#endif
        }
        else if(tmpCur->GetType() == formula::svDouble)
        {
            ss << "    arg0=";
            ss << tmpCur->GetDouble() << ";\n";
        }
    }
    else
    {
        ss << "        arg0 = ";
        ss << vSubArguments[0]->GenSlidingWindowDeclRef();
        ss << ";\n";
    }
    ss << "    return (double)sqrt(arg0 *";
    ss << " 3.1415926535897932384626433832795f);\n";
    ss << "}";
}
void OpCeil::GenSlidingWindowFunction(std::stringstream &ss,
    const std::string sSymName, SubArguments &vSubArguments)
{
    ss << "\ndouble " << sSymName;
    ss << "_"<< BinFuncName() <<"(";
    for (unsigned i = 0; i < vSubArguments.size(); i++)
    {
        if (i) ss << ",";
        vSubArguments[i]->GenSlidingWindowDecl(ss);
    }
    ss << ") {\n";
    ss << "    int gid0   = get_global_id(0);\n";
    ss << "    double num = " << GetBottom() << ";\n";
    ss << "    double significance = " << GetBottom() << ";\n";
    ss << "    double bAbs = 0;\n";
#ifdef ISNAN
    FormulaToken *iNum = vSubArguments[0]->GetFormulaToken();
    const formula::SingleVectorRefToken* tmpCurDVRNum=
        dynamic_cast<const formula::SingleVectorRefToken*>(iNum);
    FormulaToken *iSignificance = vSubArguments[1]->GetFormulaToken();
    const formula::SingleVectorRefToken* tmpCurDVRSignificance=
        dynamic_cast<const formula::SingleVectorRefToken*>(iSignificance);
    ss << "    int buffer_num_len = "<<tmpCurDVRNum->GetArrayLength() << ";\n";
    ss << "    int buffer_significance_len = ";
    ss << tmpCurDVRSignificance->GetArrayLength() << ";\n";
    ss << "    if((gid0)>=buffer_num_len || isNan(";
    ss << vSubArguments[0]->GenSlidingWindowDeclRef() << "))\n";
    ss << "        num = " << GetBottom() << ";\n";
    ss << "    else\n    ";
#endif
    ss << "    num = " << vSubArguments[0]->GenSlidingWindowDeclRef() << ";\n";
#ifdef ISNAN
    ss << "    if((gid0)>=buffer_significance_len || isNan(";
    ss << vSubArguments[1]->GenSlidingWindowDeclRef() << "))\n";
    ss << "        significance = " << GetBottom() << ";\n";
    ss << "    else\n    ";
#endif
    ss << "    significance = ";
    ss << vSubArguments[1]->GenSlidingWindowDeclRef() << ";\n";
    if (vSubArguments.size() > 2)
    {
#ifdef ISNAN
        FormulaToken *bAbs = vSubArguments[2]->GetFormulaToken();
        if(bAbs->GetType() == formula::svSingleVectorRef)
        {
            const formula::SingleVectorRefToken* tmpCurSVRIsAbs=
                dynamic_cast<const formula::SingleVectorRefToken*>(bAbs);
            ss<< "    if((gid0)>=" << tmpCurSVRIsAbs->GetArrayLength() << " ||";
        }
        if(bAbs->GetType() == formula::svDoubleVectorRef)
        {
            const formula::DoubleVectorRefToken* tmpCurDVRIsAbs=
                dynamic_cast<const formula::DoubleVectorRefToken*>(bAbs);
            ss<< "    if((gid0)>=" << tmpCurDVRIsAbs->GetArrayLength() << " ||";
        }
        if(bAbs->GetType() == formula::svDouble)
        {
            ss<< "    if(";
        }
        ss << "isNan(";
        ss << vSubArguments[2]->GenSlidingWindowDeclRef() << "))\n";
        ss << "        bAbs = 0;\n";
        ss << "    else\n    ";
#endif
        ss << "    bAbs = "<<vSubArguments[2]->GenSlidingWindowDeclRef()<<";\n";
    }
    ss << "    return ";
    ss << "( !(int)bAbs && num < 0.0 ? floor( num / significance ) : ";
    ss << "ceil( num / significance ) )";
    ss << "*significance;\n";
    ss << "}";
}
void OpKombin::GenSlidingWindowFunction(std::stringstream &ss,
    const std::string sSymName, SubArguments &vSubArguments)
{
    ss << "\ndouble " << sSymName;
    ss << "_"<< BinFuncName() <<"(";
    for (unsigned i = 0; i < vSubArguments.size(); i++)
    {
        if (i) ss << ",";
        vSubArguments[i]->GenSlidingWindowDecl(ss);
    }
    ss << ") {\n";
    ss << "    int gid0 = get_global_id(0);\n";
    ss << "    double num = " << GetBottom() << ";\n";
    ss << "    double num_chosen = " << GetBottom() << ";\n";
    ss << "    double result = " << GetBottom() << ";\n";
#ifdef ISNAN
    FormulaToken *iNum = vSubArguments[0]->GetFormulaToken();
    const formula::SingleVectorRefToken* tmpCurDVRNum=
        dynamic_cast<const formula::SingleVectorRefToken *>(iNum);
    FormulaToken *iNumChosen = vSubArguments[1]->GetFormulaToken();
    const formula::SingleVectorRefToken* tmpCurDVRNumChosen=
        dynamic_cast<const formula::SingleVectorRefToken *>(iNumChosen);
    ss << "    int buffer_num_len = ";
    ss << tmpCurDVRNum->GetArrayLength() << ";\n";
    ss << "    int buffer_num_chosen_len = ";
    ss << tmpCurDVRNumChosen->GetArrayLength() << ";\n";

    ss << "    if((gid0)>=buffer_num_len || isNan(";
    ss << vSubArguments[0]->GenSlidingWindowDeclRef() << "))\n";
    ss << "        num = " << GetBottom() << ";\n";
    ss << "    else\n    ";
#endif
    ss << "    num = floor(";
    ss << vSubArguments[0]->GenSlidingWindowDeclRef() << ");\n";
#ifdef ISNAN
    ss << "    if((gid0)>=buffer_num_chosen_len || isNan(";
    ss << vSubArguments[1]->GenSlidingWindowDeclRef() << "))\n";
    ss << "        num_chosen = " << GetBottom() << ";\n";
    ss << "    else\n    ";
#endif
    ss << "    num_chosen = floor(";
    ss << vSubArguments[1]->GenSlidingWindowDeclRef() << ");\n";
    ss << "    if (num < num_chosen)                 \n";
    ss << "        result = 0;                       \n";
    ss << "    else if (num_chosen == 0)             \n";
    ss << "        result = 1;                       \n";
    ss << "    else{                                 \n";
    ss << "        result = num / num_chosen;        \n";
    ss << "        num = num - 1.0;                  \n";
    ss << "        num_chosen = num_chosen - 1.0;    \n";
    ss << "        while (num_chosen > 0){           \n";
    ss << "            result *= num / num_chosen;   \n";
    ss << "            num = num - 1.0;              \n";
    ss << "            num_chosen = num_chosen - 1.0;\n";
    ss << "        }                                 \n";
    ss << "    }                                     \n";
    ss << "    return result;                        \n";
    ss << "}                                         \n";
}
void OpConvert::GenSlidingWindowFunction(
    std::stringstream &ss, const std::string sSymName,
    SubArguments &vSubArguments)
{
    int arg1=vSubArguments[1]->GetFormulaToken()->GetString().\
        getString().toAsciiUpperCase().hashCode();
    int arg2=vSubArguments[2]->GetFormulaToken()->GetString().\
        getString().toAsciiUpperCase().hashCode();
    if( !((arg1==5584&&arg2==108)||
        (arg1==108&&arg2==5584)||
        (arg1==5665&&arg2==268206)||
        (arg1==268206&&arg2==5665)) )
        throw Unhandled();

    FormulaToken *tmpCur = vSubArguments[0]->GetFormulaToken();
    const formula::SingleVectorRefToken*tmpCurDVR= dynamic_cast<const
        formula::SingleVectorRefToken *>(tmpCur);
    ss << "\ndouble " << sSymName;
    ss << "_"<< BinFuncName() <<"(";
    for (unsigned i = 0; i < vSubArguments.size(); i++)
    {
        if (i)
            ss << ",";
        vSubArguments[i]->GenSlidingWindowDecl(ss);
    }
    ss << ")\n{\n";
    ss <<"    int gid0=get_global_id(0);\n";
    ss << "    double arg0 = " << vSubArguments[0]->GenSlidingWindowDeclRef();
    ss << ";\n";
    ss << "    double arg1 = " << vSubArguments[1]->GenSlidingWindowDeclRef();
    ss << ";\n";
    ss << "    double arg2 = " << vSubArguments[2]->GenSlidingWindowDeclRef();
    ss << ";\n";
#ifdef ISNAN
    ss<< "    if(isNan(arg0)||(gid0>=";
    ss<<tmpCurDVR->GetArrayLength();
    ss<<"))\n";
    ss<<"        arg0 = 0;\n";
    ss<< "    if(isNan(arg1)||(gid0>=";
    ss<<tmpCurDVR->GetArrayLength();
    ss<<"))\n";
    ss<<"        arg1 = 0;\n";
    ss<< "    if(isNan(arg2)||(gid0>=";
    ss<<tmpCurDVR->GetArrayLength();
    ss<<"))\n";
    ss<<"        arg2 = 0;\n";
#endif
    ss<<"    if(arg1==5584U&&arg2==108U)\n";
    ss<<"        return arg0*1000.0;\n";
    ss<<"    else if(arg1==108U&&arg2==3385U)\n";
    ss<<"        return arg0/1000.0;\n";
    ss<<"    else if(arg1==5665U&&arg2==268206U)\n";
    ss<<"        return arg0*60.0;\n";
    ss<<"    else if(arg1==268206U&&arg2==5665U)\n";
    ss<<"        return arg0/60.0;\n";
    ss<<"    else\n";
    ss<<"        return -9999999999;\n";
    ss << "}\n";

}

void OpProduct::GenSlidingWindowFunction(std::stringstream &ss,
            const std::string sSymName, SubArguments &vSubArguments)
{
    ss << "\ndouble " << sSymName;
    ss << "_"<< BinFuncName() <<"( ";
    for (unsigned i = 0; i < vSubArguments.size(); i++)
    {
        if (i)
            ss << ",";
        vSubArguments[i]->GenSlidingWindowDecl(ss);
    }
    ss << ") {\n";
    ss << "    int gid0 = get_global_id(0);\n";
    ss << "    int i = 0;\n";
    ss << "    double product=0.0;\n\n";
    char sArgNoI[5];
    for (unsigned i = 0; i < vSubArguments.size(); i++)
    {
        sprintf(sArgNoI,"%d",i);
        ss << std::string("    double arg")+sArgNoI+";\n";
        FormulaToken *pCur = vSubArguments[i]->GetFormulaToken();
        assert(pCur);
        if (pCur->GetType() == formula::svDoubleVectorRef)
        {
            const formula::DoubleVectorRefToken* pDVR =
            dynamic_cast<const formula::DoubleVectorRefToken *>(pCur);
            size_t nCurWindowSize = pDVR->GetRefRowSize();
            ss << std::string("    arg")+sArgNoI+" = ";
            ss << vSubArguments[i]->GenSlidingWindowDeclRef();
            ss <<";\n";
#ifdef ISNAN
            ss << std::string("    if(isNan(arg")+sArgNoI+")||((gid0+i)>=";
            ss << pDVR->GetArrayLength();
            ss << "))\n";
            ss << "    {\n";
            ss << std::string("        arg")+sArgNoI+" = 0;\n";
            ss << "    }\n";
#endif
            ss << std::string("    product = arg")+sArgNoI+";\n";
            ss << "    for (i = ";
            ss << "1; i < "<< nCurWindowSize << "; i++)\n";
            ss << "    {\n";
            ss << std::string("        arg")+sArgNoI+" = ";
            ss << vSubArguments[i]->GenSlidingWindowDeclRef();
            ss << ";\n";
#ifdef ISNAN
            ss <<std::string("        if(isNan(arg")+sArgNoI+")||((gid0+i)>=";
            ss << pDVR->GetArrayLength();
            ss << "))\n";
            ss << "        {\n";
            ss << std::string("            arg")+sArgNoI+" = 0;\n";
            ss << "        }\n";
#endif
            ss << std::string("        product*=arg")+sArgNoI+";\n";
            ss << "    }\n";
            }
            else if (pCur->GetType() == formula::svSingleVectorRef)
            {
#ifdef  ISNAN
                ss << std::string("    arg")+sArgNoI+" = ";
                ss << vSubArguments[i]->GenSlidingWindowDeclRef();
                ss << ";\n";
                ss << std::string("    product*=arg")+sArgNoI+";\n";
#endif
            }
            else if (pCur->GetType() == formula::svDouble)
            {
#ifdef  ISNAN
                ss << std::string("    arg")+sArgNoI+" = ";
                ss << vSubArguments[i]->GenSlidingWindowDeclRef();
                ss << ";\n";
                ss << std::string("    product*=arg")+sArgNoI+";\n";
#endif
            }
        }
        ss << "    return product;\n";
        ss << "}";
}

}}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
