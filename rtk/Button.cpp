#include "pch.h"
#include "Button.h"

#include <stdexcept>
#include "utils.h"

// DELETE ME
#define IDC_MAIN_BUTTON	101

namespace rtk
{
    Button::Button(Control& parent, int x, int y, int width, int height, const std::string& caption)
    {
        DWORD dwStyle = WS_TABSTOP|WS_VISIBLE|WS_CHILD|BS_DEFPUSHBUTTON;

        hWnd = CreateWindowEx(NULL, L"BUTTON", widen(caption).c_str(), dwStyle, x, y, width, height, parent, (HMENU)IDC_MAIN_BUTTON, GetModuleHandle(NULL), NULL);
        if (hWnd == NULL) 
        {
            throw std::runtime_error(get_last_error());
        }
        SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)this);
    }

    Button::~Button() {}

    void Button::on_click(std::function<void ()> cb)
    {
        click_cb = cb;
    }

    void Button::handle_command()
    {
        if (click_cb)
        {
            click_cb();
        }
    }
}
