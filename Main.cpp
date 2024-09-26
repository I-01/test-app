/**
 * file: Main.cpp
 * encode: utf-8
 * cl /Wall /std:c++20 /EHsc /utf-8 /fp:fast /J /D_UNICODE /DUNICODE /GA /Fo"obj\" /Fe"test" /MT User32.lib Gdi32.lib Shell32.lib Main.cpp lib/GetArgs.cpp lib/Win32.cpp
*/


// Windows api.
// https://learn.microsoft.com/en-us/windows/win32/winprog/windows-data-types
#ifdef _WIN32
    // includes.
    #include"lib/Include.hpp"
    #include"lib/Win32.hpp"
    #include"lib/GetArgs.hpp"


    // global variables.
    HWND main_windowHandle = nullptr;
    const wchar_t *main_className = L"I01 className";
    const wchar_t *main_windowName = L"I01 windowName";


    //
    LRESULT CALLBACK main_WndProc(HWND windowHandle, unsigned int msg, WPARAM wParam, LPARAM lParam)
    {
        switch(msg)
        {
            case WM_DESTROY:
                PostQuitMessage(0);
                return 0;
            default:
                return DefWindowProcW(windowHandle, msg, wParam, lParam);
        }
    }


    // PrevInstanceHandle, args.
    int APIENTRY wWinMain(HINSTANCE instanceHandle, HINSTANCE, wchar_t*, int)
    {
        try
        {
            std::unique_ptr<I01::ArgGetter> args = std::make_unique<I01::ArgGetter>();
            MessageBoxW(nullptr, args->GetArgv(0), L"test", MB_ICONINFORMATION);
            I01::RegisterClassExW(CS_VREDRAW | CS_HREDRAW, main_WndProc, 0, 0, instanceHandle, I01::LoadIconW(nullptr, IDI_APPLICATION), I01::LoadCursorW(nullptr, IDC_ARROW), (HBRUSH)I01::GetStockObject(WHITE_BRUSH), nullptr, main_className, I01::LoadIconW(nullptr, IDI_APPLICATION));
            main_windowHandle = I01::CreateWindowExW(0, main_className, main_windowName, WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, nullptr, nullptr, instanceHandle, nullptr);
            MSG msg; int flag;
            while(true)
            {
                flag = GetMessageW(&msg, main_windowHandle, 0, 0);
                if(flag == -1 || flag == 0) break;
                DispatchMessageW(&msg);
            }
        }
        catch(const std::exception& e)
        {
            MessageBoxA(nullptr, e.what(), "error", MB_ICONERROR);
            return 1;
        }
        return 0;
    }
#endif

