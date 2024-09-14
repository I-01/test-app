/**
 * file: Main.cpp
 * encode: utf-8
 * cl /Wall /std:c++20 /EHsc /utf-8 /fp:fast /J /D_UNICODE /DUNICODE /GA /Fe"test" /MT Shell32.lib User32.lib Gdi32.lib Main.cpp
*/


// インクルード.
#include"lib/Include.hpp"


// メイン関数.
int main()
{
    char16_t testStr1[] = u"あいうえお";
    wchar_t testStr2[] = L"あいうえお";
    if(sizeof(char16_t) == sizeof(wchar_t))
    {
        std::printf("sizeof(char16_t) == sizeof(wchar_t)\n");
        if(memcmp(testStr1, testStr2, sizeof(wchar_t) * 6) == 0)
        {
            std::printf("char16_t == wchar_t\n");
        }
    }
    return 0;
}

