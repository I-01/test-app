/**
 * file: Windows.cpp
 * encode: utf-8
*/


// include.
#include "Win32.hpp"


HGDIOBJ I01::GetStockObject(int i)
{
    // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-getstockobject
    HGDIOBJ rslt = ::GetStockObject(i);
    if(rslt == nullptr) throw std::runtime_error("I01::GetStockObject\nGetStockObject() failed.");
    return rslt;
}


HICON I01::LoadIconW(HINSTANCE instanceHandle, const wchar_t *iconName)
{
    // https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-loadiconw
    HICON rslt = ::LoadIconW(instanceHandle, iconName);
    if(rslt == nullptr) throw std::runtime_error("I01::LoadIconW()\nLoadIconW() failed.");
    return rslt;
}
HCURSOR I01::LoadCursorW(HINSTANCE instanceHandle, const wchar_t *cursorName)
{
    // https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-loadcursorw
    HCURSOR rslt = ::LoadCursorW(instanceHandle, cursorName);
    if(rslt == nullptr) throw std::runtime_error("I01::LoadCursorW()\nLoadCursorW() failed.");
    return rslt;
}


ATOM I01::RegisterClassExA(unsigned int style, WNDPROC WndProc, int cbClsExtra, int cbWndExtra, HINSTANCE instanceHandle, HICON iconHandle, HCURSOR cursorHandle, HBRUSH brushHandle, const char *menuName, const char *className, HICON smallIconHandle)
{
    // https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-wndclassexa
    WNDCLASSEXA wc;
    wc.cbSize           = sizeof(WNDCLASSEXA);
    wc.style            = style;
    wc.lpfnWndProc      = WndProc;
    wc.cbClsExtra       = cbClsExtra;
    wc.cbWndExtra       = cbWndExtra;
    wc.hInstance        = instanceHandle;
    wc.hIcon            = iconHandle;
    wc.hCursor          = cursorHandle;
    wc.hbrBackground    = brushHandle;
    wc.lpszMenuName     = menuName;
    wc.lpszClassName    = className;
    wc.hIconSm          = smallIconHandle;
    // https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-registerclassexa
    ATOM rslt = ::RegisterClassExA(&wc);
    if(rslt == 0) throw std::runtime_error("I01::RegisterClassExA()\nRegisterClassExA() failed.");
    return rslt;
}
ATOM I01::RegisterClassExW(unsigned int style, WNDPROC WndProc, int cbClsExtra, int cbWndExtra, HINSTANCE instanceHandle, HICON iconHandle, HCURSOR cursorHandle, HBRUSH brushHandle, const wchar_t *menuName, const wchar_t *className, HICON smallIconHandle)
{
    // https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-wndclassexw
    WNDCLASSEXW wc;
    wc.cbSize           = sizeof(WNDCLASSEXW);
    wc.style            = style;
    wc.lpfnWndProc      = WndProc;
    wc.cbClsExtra       = cbClsExtra;
    wc.cbWndExtra       = cbWndExtra;
    wc.hInstance        = instanceHandle;
    wc.hIcon            = iconHandle;
    wc.hCursor          = cursorHandle;
    wc.hbrBackground    = brushHandle;
    wc.lpszMenuName     = menuName;
    wc.lpszClassName    = className;
    wc.hIconSm          = smallIconHandle;
    // https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-registerclassexw
    ATOM rslt = ::RegisterClassExW(&wc);
    if(rslt == 0) throw std::runtime_error("I01::RegisterClassExW()\nRegisterClassExW() failed.");
    return rslt;
}


HWND I01::CreateWindowExW(DWORD exStyle, const wchar_t *className, const wchar_t *windowName, DWORD style, int x, int y, int width, int height, HWND windowParentHandle, HMENU menueHandle, HINSTANCE instanceHandle, void *param)
{
    // https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-createwindowexw
    HWND rslt = ::CreateWindowExW(exStyle, className, windowName, style, x, y, width, height, windowParentHandle, menueHandle, instanceHandle, param);
    if(rslt == nullptr) throw std::runtime_error("I01::CreateWindowExW()\nCreateWindowExW() failed.");
    return rslt;
}


BOOL I01::SetLayeredWindowAttributes(HWND windowHandle, COLORREF color, BYTE alpha, DWORD flags)
{
    // https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setlayeredwindowattributes
    BOOL rslt = ::SetLayeredWindowAttributes(windowHandle, color, alpha, flags);
    if(rslt == 0) throw std::runtime_error("I01::SetLayeredWindowAttributes()\nSetLayeredWindowAttributes() failed.");
    return rslt;
}

