/**
 * file: Main.cpp
 * encode: UTF-8
 * command: cl /Wall /std:c++20 /EHsc /SUBSYSTEM:WINDOWS /utf-8 /fp:fast /J /D_UNICODE /DUNICODE /GA /Fe"test" /MT User32.lib Gdi32.lib Main.c
*/


// インクルード.
#include<Windows.h>
#include<vector>
#include<new>
#include<exception>


// グローバル変数.
CONST WCHAR *CONST classNames[10] = {L"I01's WNDCLASS name"};
CONST WCHAR *CONST windowNames[10] = {L"I01's Window"};
HICON hIcons[10];
HCURSOR hCursors[10];
HBRUSH brushes[10];
I01::Array<HWND> *windows = nullptr;


// プロトタイプ宣言.
LRESULT CALLBACK I01_mainWindow_Proc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);


// メイン関数.
INT APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, INT nCmdShow)
{
    try
    {
        windows = new(std::nothrow) I01::Array<HWND>(I01::Array<HWND>::DestroyWindow);
        if(windows == nullptr) return 1;
        windows->Initialize();

        HICON hIcon = I01::LoadIconW(nullptr, IDI_APPLICATION);
        HCURSOR hCursor = I01::LoadCursorW(nullptr, IDC_ARROW);
        HBRUSH whiteBrush = (HBRUSH)I01::GetStockObject(WHITE_BRUSH);
        WNDCLASSEXW wc;
        wc.cbSize         = sizeof(WNDCLASSEXW);
        wc.style          = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc    = I01_mainWindow_Proc;
        wc.cbClsExtra     = wc.cbWndExtra = 0;
        wc.hInstance      = hInstance;
        wc.hIcon          = hIcon;
        wc.hCursor        = hCursor;
        wc.hbrBackground  = whiteBrush;
        wc.lpszMenuName   = nullptr;
        wc.lpszClassName  = classNames[0];
        wc.hIconSm        = nullptr;
        I01::RegisterClassExW(&wc);
        windows->Push(I01::CreateWindowExW(WS_EX_LEFT, classNames[0], windowNames[0], WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, nullptr, nullptr, hInstance, nullptr));
        MSG msg;
        BOOL flag;
        while(TRUE)
        {
            flag = GetMessageW(&msg, windows->At(0), 0, 0);
            if(flag == -1 || flag == 0) break;
            DispatchMessageW(&msg);
        }
    }
    catch(CONST WCHAR *CONST &e)
    {
    }
    catch(CONST std::exception &e)
    {
    }
    return 0;
}


// ウィンドウプロシージャ.
LRESULT CALLBACK I01_mainWindow_Proc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch(msg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_PAINT:
            {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hWnd, &ps);
                TextOutW(hdc, 10, 10, L"test", lstrlenW(L"test"));
                EndPaint(hWnd, &ps);
            }
            return 0;
        default:
            return DefWindowProcW(hWnd, msg, wp, lp);
    }
}

