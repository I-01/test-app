/**
 * file: GetArgs.cpp
 * encode: utf-8
*/


// include.
#include "GetArgs.hpp"


I01::ArgGetter::ArgGetter()
{
    argv = ::CommandLineToArgvW(::GetCommandLineW(), &argc);
    if(argv == nullptr) throw std::runtime_error("I01::ArgGetter::ArgGetter()\nCommandLineToArgvW() failed.");
}
I01::ArgGetter::~ArgGetter() noexcept
{
    ::LocalFree(argv);
}


int I01::ArgGetter::GetArgc() noexcept
{
    return argc;
}
const wchar_t *I01::ArgGetter::GetArgv(int i)
{
    if(i < 0 || argc <= i) throw std::invalid_argument("I01::ArgGetter::GetArgv()\nThe i was out of range.");
    return argv[i];
}

