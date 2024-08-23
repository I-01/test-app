/**
 * file: I01_Func.h
 * encode: utf-8
*/


// インクルードガード.
#pragma once


// インクルード.
#include"Include.h"


VOID I01_DoNothing(VOID)
{
    return;
}
VOID I01_Error(jmp_buf e, WCHAR CONST *errMsg)
{
    I01_errMsg = errMsg;
    longjmp(e, 1);
}

