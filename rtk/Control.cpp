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

namespace rtk
{
    Control::operator HWND () const
    {
        return hWnd;
    }

	int Control::get_left() const
	{
		return getRect().left;
	}

	int Control::get_top() const
	{
		return getRect().top;
	}

	int Control::get_right() const
	{
		return getRect().right;
	}

	int Control::get_bottom() const
	{
		return getRect().bottom;
	}

	int Control::get_width() const
	{
		RECT rect = getRect();
		return rect.right - rect.left;
	}

	int Control::get_height() const
	{
		RECT rect = getRect();
		return rect.bottom - rect.top;
	}

	bool Control::is_visible() const
	{
		return IsWindowVisible(hWnd) == TRUE;
	}

    void Control::handle_command() {}

	void Control::set_window_text(const std::string_view value)
	{
		BOOL r = SetWindowText(hWnd, widen(value).data());
		if (r == FALSE)
		{
			throw std::runtime_error(get_last_error());
		}
	}

	std::string Control::get_window_text() const
	{
		int len1 = GetWindowTextLength(hWnd);
		if (len1 < 0)
		{
			throw std::runtime_error(get_last_error());
		}

		if (len1 == 0)
		{
			return std::string();
		}

		std::vector<wchar_t> buffer(len1 + 1);
		int len2 = GetWindowText(hWnd, buffer.data(), static_cast<int>(buffer.size()));
		if (len1 != len2)
		{
			throw std::runtime_error(get_last_error());
		}

		return narrow(buffer.data());
	}

	RECT Control::getRect() const
	{
		RECT rect;
		
		BOOL r = GetWindowRect(hWnd, &rect);
		if (r == FALSE)
		{
			throw std::runtime_error(get_last_error());
		}

		return rect;
	}
}
