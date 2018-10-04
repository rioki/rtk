//
// rtk - rioki's windows ui toolkit
// Copyright 2018 Sean "rioki" Farrell <sean.farrell@rioki.org>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to 
// deal in the Software without restriction, including without limitation the 
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
// sell copies of the Software, and to permit persons to whom the Software is 
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE 
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
// DEALINGS IN THE SOFTWARE.
//

#include "pch.h"

#include "Window.h"

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

	Window::Window(const std::string_view caption)
	: Window(CW_USEDEFAULT, CW_USEDEFAULT, 350, 350, caption) {}

    Window::Window(int left, int top, int width, int height, const std::string_view caption)
    {
        HINSTANCE hInst = GetModuleHandle(NULL);
        create_rtk_window_class(hInst);

		auto wcaption = widen(caption);

        hWnd = CreateWindowEx(NULL, L"RTK-WINDOW", wcaption.data(), WS_OVERLAPPEDWINDOW, left, top, width, height, NULL, NULL, hInst, this);

        if(!hWnd)
        {
            throw std::runtime_error(get_last_error());
        } 

		SetWindowText(hWnd, wcaption.data());
    }

    Window::~Window()
    {
        DestroyWindow(hWnd);
    }

	std::string Window::get_caption() const
	{
		return get_window_text();
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
