/**
 * file: Main.c
 * encode: utf-8
 * command: cl /Wall /std:c17 /EHsc /utf-8 /fp:fast /J /D_UNICODE /DUNICODE /GA /Fe"test" /MT User32.lib Gdi32.lib Main.c
 * command: cl /Wall /std:c17 /EHsc /SUBSYSTEM:WINDOWS /utf-8 /fp:fast /J /D_UNICODE /DUNICODE /GA /Fe"test" /MT User32.lib Gdi32.lib Main.c
*/


// インクルード.
#include"Include.h"
#include"I01_ARRAY.h"
#include"I01_Func.h"


// メイン関数.
INT main(VOID)
{
    jmp_buf e;
    I01_ARRAY *array = NULL;
    if(!setjmp(e))
    {
        array = I01_ARRAY_Constructor(e, sizeof(INT32), I01_DoNothing);
        INT32 **i = &array->rawData;
        SIZE_T i0 = I01_ARRAY_Get(e, array); (*i)[i0] = 10;
        SIZE_T i1 = I01_ARRAY_Get(e, array); (*i)[i1] = 20;
        printf("[%p] %zu: %d, %zu: %d\n", *i, i0, (*i)[i0], i1, (*i)[i1]);
        I01_ARRAY_Erase(e, array, i0);
        SIZE_T i2 = I01_ARRAY_Get(e, array); (*i)[i2] = 30;
        SIZE_T i3 = I01_ARRAY_Get(e, array); (*i)[i3] = 40;
        i0 = I01_ARRAY_Get(e, array); (*i)[i0] = 50;
        printf("[%p] %zu: %d, %zu: %d, %zu: %d, %zu: %d\n", *i, i0, (*i)[i0], i1, (*i)[i1], i2, (*i)[i2], i3, (*i)[i3]);
    }
    else
    {
        I01_return = 1;
        MessageBoxW(NULL, L"Error", I01_errMsg, 0);
    }
    I01_ARRAY_Destructor(&array);
    return I01_return;
}

