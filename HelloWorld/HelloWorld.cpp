#include <stdio.h>
#include <string>
#include "base.h"
#include "base.cpp"


#define EvalPrint(x) printf("%s = %d\n", #x, (S32)x)
#define EvalPrintLL(x) printf("%s = %lld\n", #x, (S64)x)
#define EvalPrintU(x) printf("%s = %u\n", #x, (U32)x)
#define EvalPrintULL(x) printf("%s = %llu\n", #x, (U64)x)
#define EvalPrintF(x) printf("%s = [%f]\n", #x, (F64)x)



int main()
{
    std::string s = " ";
    printf("cl      =%d\n",COMPILER_CL);
    printf("clang   =%d\n",COMPILER_CLANG);
    printf("gcc     =%d\n",COMPILER_GCC);
    printf("windows =%d\n",OS_WINDOWS);
    printf("linux   =%d\n",OS_LINUX);
    printf("mac     =%d\n",OS_MAC);
    printf("x64     =%d\n",ARCH_X64);
    printf("x86     =%d\n",ARCH_X86);
    printf("ARM     =%d\n",ARCH_ARM);
    printf("ARM64   =%d\n",ARCH_ARM64);

    int foo[100];
    for(int n=0 ;n<100;n++)
    {
        foo[n]=n;
    }

    EvalPrint(foo[50]);
    EvalPrint(Min(1,2));
    EvalPrint(Clamp(1,0,3));

    EvalPrint(min_S8);
    EvalPrint(min_S16);
    EvalPrint(min_S32);
    EvalPrintLL(min_S64);
    EvalPrint(max_S8);
    EvalPrint(max_S16);
    EvalPrint(max_S32);
    EvalPrintLL(max_S64);
    EvalPrintU(max_U8);
    EvalPrintU(max_U16);
    EvalPrintU(max_U32);
    EvalPrintULL(max_U64);
    
    EvalPrintF(inf_F32());
    EvalPrintF(neg_inf_F32());
    EvalPrintF(inf_F64());
    EvalPrintF(neg_inf_F64());

    EvalPrintF(abs_F32(-100.));
    EvalPrintF(abs_F32(100.));
    EvalPrintF(abs_F32(0));
    EvalPrintF(abs_F32(-0));
    EvalPrintF(abs_F32(neg_inf_F32()));
    EvalPrintF(abs_F32(inf_F32()));

    EvalPrintF(abs_F64(-100.));
    EvalPrintF(abs_F64(100.));
    EvalPrintF(abs_F64(0));
    EvalPrintF(abs_F64(-0));
    EvalPrintF(abs_F64(neg_inf_F64()));
    EvalPrintF(abs_F64(inf_F64()));

    int list[4];

    printf("%d\n",list);
    printf("%d\n", &list);
    printf("%d\n",*list);
    printf("%d\n",list[1]);
    list[1]=5;
    printf("%d\n",list[1]);

    
    

}