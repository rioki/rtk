#include "Button.h"

#include <stdexcept>
#include "utils.h"

// DELETE ME
#define IDC_MAIN_BUTTON	101

namespace rtk
{
    Button::Button(Control& parent, Point& pos, Size& size, const std::string& caption) 
    {
        HWND  hParent = parent.get_hwnd();
        DWORD dwStyle = WS_TABSTOP|WS_VISIBLE|WS_CHILD|BS_DEFPUSHBUTTON;

        hWnd = CreateWindowEx(NULL, L"BUTTON", widen(caption).c_str(), dwStyle, pos.x, pos.y, size.w, size.h, hParent, (HMENU)IDC_MAIN_BUTTON, GetModuleHandle(NULL), NULL);
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
