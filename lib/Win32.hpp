/**
 * file: Win32.hpp
 * encode: utf-8
*/


// Windows api.
#ifdef _WIN32
    // include guard.
    #ifndef I01__lib__Windows_hpp
        #define I01__lib__Windows_hpp
        // include.
        #include"Include.hpp"
        namespace I01
        {
            HGDIOBJ GetStockObject(int i);
            HICON LoadIconW(HINSTANCE instanceHandle, const wchar_t *iconName);
            HCURSOR LoadCursorW(HINSTANCE instanceHandle, const wchar_t *cursorName);
            ATOM RegisterClassExA(unsigned int style, WNDPROC WndProc, int cbClsExtra, int cbWndExtra, HINSTANCE instanceHandle, HICON iconHandle, HCURSOR cursorHandle, HBRUSH brushHandle, const char *menuName, const char *className, HICON smallIconHandle);
            ATOM RegisterClassExW(unsigned int style, WNDPROC WndProc, int cbClsExtra, int cbWndExtra, HINSTANCE instanceHandle, HICON iconHandle, HCURSOR cursorHandle, HBRUSH brushHandle, const wchar_t *menuName, const wchar_t *className, HICON smallIconHandle);
            HWND CreateWindowExW(DWORD exStyle, const wchar_t *className, const wchar_t *windowName, DWORD style, int x, int y, int width, int height, HWND windowParentHandle, HMENU menueHandle, HINSTANCE instanceHandle, void *param);
            BOOL SetLayeredWindowAttributes(HWND windowHandle, COLORREF color, BYTE alpha, DWORD flags);
        }
    #endif
#endif

