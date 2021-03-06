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

#include "Control.h"
#include "utils.h"
#include "dbg.h"

namespace rtk
{
    Control::~Control()
    {
        if (hWnd)
        {
            SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)NULL);

            BOOL r = DestroyWindow(hWnd);
            if (r == FALSE)
            {
                DBG_TRACE("Failed to destroy window.");
            }
        }
        hWnd = NULL;
    }

    Control::operator HWND () const
    {
        return hWnd;
    }

    Control* Control::get_parent()
    {
        DBG_ASSERT(hWnd != NULL);

        HWND hParentWnd = GetParent(hWnd);
        if (hParentWnd != NULL)
        {
            Control* parent = (Control*)GetWindowLongPtr(hParentWnd, GWLP_USERDATA);
            if (parent != nullptr)
            {
                return parent;
            }
        }
        DBG_TRACE("returning null parent");
        return nullptr;
    }

    const Control* Control::get_parent() const
    {
        return const_cast<Control*>(this)->get_parent();
    }

	int Control::get_left() const
	{
		return get_rect().left;
	}

	int Control::get_top() const
	{
		return get_rect().top;
	}

	int Control::get_right() const
	{
		return get_rect().right;
	}

	int Control::get_bottom() const
	{
		return get_rect().bottom;
	}

	int Control::get_width() const
	{
		RECT rect = get_rect();
		return rect.right - rect.left;
	}

	int Control::get_height() const
	{
		RECT rect = get_rect();
		return rect.bottom - rect.top;
	}

	int Control::get_inner_width() const
	{
		return get_client_rect().right;
	}

	int Control::get_inner_height() const
	{
		return get_client_rect().bottom;
	}

    void Control::resize(int width, int height)
    {
        BOOL r = SetWindowPos(hWnd, NULL, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER);
        if (r == FALSE)
		{
			throw std::runtime_error(narrow(get_last_error()));
		}
    }

	bool Control::is_visible() const
	{
		return IsWindowVisible(hWnd) == TRUE;
	}

    void Control::handle_command(WPARAM wParam) {}

    void Control::handle_resize() {}

	void Control::set_window_text(const std::wstring_view value)
	{
		BOOL r = SetWindowText(hWnd, value.data());
		if (r == FALSE)
		{
			throw std::runtime_error(narrow(get_last_error()));
		}
	}

	std::wstring Control::get_window_text() const
	{
		int len1 = GetWindowTextLength(hWnd);
		if (len1 < 0)
		{
			throw std::runtime_error(narrow(get_last_error()));
		}

		if (len1 == 0)
		{
			return std::wstring();
		}

		std::vector<wchar_t> buffer(len1 + 1);
		int len2 = GetWindowText(hWnd, buffer.data(), static_cast<int>(buffer.size()));
		if (len1 != len2)
		{
			throw std::runtime_error(narrow(get_last_error()));
		}

		return buffer.data();
	}

	RECT Control::get_rect() const
	{
		RECT rect;

		BOOL r = GetWindowRect(hWnd, &rect);
		if (r == FALSE)
		{
			throw std::runtime_error(narrow(get_last_error()));
		}

		return rect;
	}

	RECT Control::get_client_rect() const
	{
		RECT rect;

		BOOL r = GetClientRect(hWnd, &rect);
		if (r == FALSE)
		{
			throw std::runtime_error(narrow(get_last_error()));
		}

		return rect;
	}
}
