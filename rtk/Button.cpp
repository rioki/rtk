#include "pch.h"
#include "Button.h"

#include <stdexcept>
#include "utils.h"

// DELETE ME
#define IDC_MAIN_BUTTON	101

namespace rtk
{

	Button::Button(Control& parent, const std::wstring_view caption)
	: Button(parent, 0, 0, 150, 35, caption) {}

    Button::Button(Control& parent, int x, int y, int width, int height, const std::wstring_view caption)
    {
        DWORD dwStyle = WS_TABSTOP|WS_VISIBLE|WS_CHILD|BS_DEFPUSHBUTTON;

        hWnd = CreateWindowEx(NULL, L"BUTTON", caption.data(), dwStyle, x, y, width, height, parent, (HMENU)IDC_MAIN_BUTTON, GetModuleHandle(NULL), NULL);
        if (hWnd == NULL) 
        {
            throw std::runtime_error(narrow(get_last_error()));
        }
        SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)this);
    }

	Button::~Button() {}

	void Button::set_caption(const std::wstring_view value)
	{
		set_window_text(value);
	}

	std::wstring Button::get_caption() const
	{
		return get_window_text();
	}

    void Button::on_click(std::function<void ()> cb)
    {
        click_cb = cb;
    }

    void Button::handle_command(WPARAM wParam)
    {
        if (click_cb)
        {
            click_cb();
        }
    }
}
