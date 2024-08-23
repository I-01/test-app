/**
 * file: I01_ARRAY.h
 * encode: utf-8
*/


// インクルードガード.
#pragma once


// インクルード.
#include"Include.h"
#include"I01_Func.h"


// 変数管理用.
typedef struct
{
    BYTE *rawData;
    SIZE_T dataLen;
    SIZE_T datumBytes;
    SIZE_T *unuse;
    SIZE_T unuseTop;
    BYTE *flag;
    SIZE_T flagBytes;
    VOID (*eraser)(VOID*);
} I01_ARRAY;


// I01_ARRAYのコンストラクタ.
I01_ARRAY *I01_ARRAY_Constructor(jmp_buf e, SIZE_T datumBytes, VOID (*eraser)(VOID*))
{
    if(datumBytes == 0) I01_Error(e, L"I01_ARRAY_Constructor: datumBytes should be not 0.");
    if(CHAR_BIT != 8) I01_Error(e, L"I01_ARRAY_Constructor: CHAR_BIT should be 8.");
    I01_ARRAY *rslt = malloc(sizeof(I01_ARRAY));
    if(rslt == NULL) I01_Error(e, L"I01_ARRAY_Constructor: malloc() was failed.");
    rslt->dataLen = rslt->unuseTop = rslt->flagBytes = 0;
    rslt->datumBytes = datumBytes;
    rslt->eraser = eraser;
    rslt->rawData = malloc(2 * rslt->datumBytes);
    rslt->unuse = malloc(2 * sizeof(SIZE_T));
    rslt->flag = malloc(1);
    if(rslt->rawData == NULL || rslt->unuse == NULL || rslt->flag == NULL)
    {
        if(rslt->rawData != NULL) free(rslt->rawData);
        if(rslt->unuse != NULL) free(rslt->unuse);
        if(rslt->flag != NULL) free(rslt->flag);
        free(rslt);
        I01_Error(e, L"I01_ARRAY_Constructor: malloc() was failed.");
    }
    rslt->dataLen = 2;
    rslt->flagBytes = 1;
    rslt->unuse[0] = 0;
    rslt->unuse[1] = 1;
    rslt->flag[0] = 0;
    return rslt;
}
// I01_ARRAYのリサイズ.
VOID I01_ARRAY_Resize(jmp_buf e, I01_ARRAY *array)
{
    if(array == NULL) I01_Error(e, L"I01_ARRAY_Resize: array should be not NULL.");
    if(array->dataLen == 0) I01_Error(e, L"I01_ARRAY_Resize: I01_ARRAY's data should be allocated.");
    SIZE_T newDataLen = 2 * array->dataLen;
    VOID *temp;
    if((temp = realloc(array->rawData, newDataLen * array->datumBytes)) == NULL) I01_Error(e, L"I01_ARRAY_Resize: realloc() was failed.");
    array->rawData = temp;
    if((temp = realloc(array->unuse, newDataLen * sizeof(SIZE_T))) == NULL) I01_Error(e, L"I01_ARRAY_Resize: realloc() was failed.");
    array->unuse = temp;
    SIZE_T i;
    for(i = array->dataLen;i < newDataLen;++i) array->unuse[i] = i;
    array->dataLen = newDataLen;
    SIZE_T newFlagBytes = newDataLen / 8 + (0 < newDataLen % 8);
    if(array->flagBytes < newFlagBytes)
    {
        if((temp = realloc(array->flag, newFlagBytes)) == NULL) I01_Error(e, L"I01_ARRAY_Resize: realloc() was failed.");
        array->flag = temp;
        array->flagBytes = newFlagBytes;
    }
    return;
}
// I01_ARRAYの未使用の場所を探す.
// 戻り値: 確保したデータの場所.
SIZE_T I01_ARRAY_Get(jmp_buf e, I01_ARRAY *array)
{
    if(array == NULL) I01_Error(e, L"I01_ARRAY_Get: array should be not NULL.");
    if(array->dataLen <= array->unuseTop) I01_ARRAY_Resize(e, array);
    SIZE_T CONST rslt = array->unuse[array->unuseTop++];
    if(array->flag[rslt / 8] >> rslt % 8 & 1) I01_Error(e, L"I01_ARRAY_Get: unuse stack was not worked.");
    array->flag[rslt / 8] += 1 << rslt % 8;
    return rslt;
}
// I01_ARRAYの使用済みの場所を未使用にする.
VOID I01_ARRAY_Erase(jmp_buf e, I01_ARRAY *array, SIZE_T index)
{
    if(array == NULL) I01_Error(e, L"I01_ARRAY_Erase: array should be not NULL.");
    if(!(array->flag[index / 8] >> index % 8 & 1)) I01_Error(e, L"I01_ARRAY_Erase: this index was unused.");
    array->eraser(array->rawData + index * array->datumBytes);
    array->unuse[--array->unuseTop] = index;
    array->flag[index / 8] -= 1 << index % 8;
    return;
}
// I01_ARRAYのデストラクタ.
VOID I01_ARRAY_Destructor(I01_ARRAY **array)
{
    if(*array != NULL)
    {
        free((*array)->rawData);
        free((*array)->unuse);
        free((*array)->flag);
        free(*array);
        *array = NULL;
    }
    return;
}

