
#include "Window.h"

#include <stdexcept>

#include "utils.h"

namespace rtk
{
    LRESULT CALLBACK Window_WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        switch(msg)
        {
            case WM_CREATE:
            {
                CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
                SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(cs->lpCreateParams));
                break;
            }            
            case WM_DESTROY:
            {
                PostQuitMessage(0);
                return 0;
            }
            case WM_COMMAND:
            {
                HWND hCtrl = (HWND)lParam;
                Control* ctrl = (Control*)GetWindowLongPtr(hCtrl, GWLP_USERDATA);
                if (ctrl != NULL) 
                {
                    ctrl->handle_command();
                }
                break;
            }
        }

        return DefWindowProc(hWnd, msg, wParam, lParam);
    }

    void create_rtk_window_class(HINSTANCE hInst)
    {
        static bool done = false;

        if (done == false)
        {
            WNDCLASSEX wClass;
            ZeroMemory(&wClass,sizeof(WNDCLASSEX));
            wClass.cbClsExtra    = NULL;
            wClass.cbSize        = sizeof(WNDCLASSEX);
            wClass.cbWndExtra    = NULL;
            wClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
            wClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
            wClass.hIcon         = NULL;
            wClass.hIconSm       = NULL;
            wClass.hInstance     = hInst;
            wClass.lpfnWndProc   = (WNDPROC)Window_WinProc;
            wClass.lpszClassName = L"RTK-WINDOW";
            wClass.lpszMenuName  = NULL;
            wClass.style         = CS_HREDRAW|CS_VREDRAW;

            if(!RegisterClassEx(&wClass))
            {
                throw std::runtime_error(get_last_error());
            }

            done = true;
        }
    }

    Window::Window(int x, int y, int width, int height, const std::string& title)
    {
        HINSTANCE hInst = GetModuleHandle(NULL);
        create_rtk_window_class(hInst);

        hWnd = CreateWindowEx(NULL, L"RTK-WINDOW", widen(title).c_str(), WS_OVERLAPPEDWINDOW, x, y, width, height, NULL, NULL, hInst, this);

        if(!hWnd)
        {
            throw std::runtime_error(get_last_error());
        } 
    }

    Window::~Window()
    {
        DestroyWindow(hWnd);
    }

    void Window::show(int cmd)
    {
        ShowWindow(hWnd, cmd);
    }

    void Window::hide()
    {
        show(SW_HIDE);
    }

    void Window::close()
    {
        DestroyWindow(hWnd);
    }

    void Window::run()
    {
        MSG msg;
        ZeroMemory(&msg,sizeof(MSG));

        while(GetMessage(&msg, NULL, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
}
