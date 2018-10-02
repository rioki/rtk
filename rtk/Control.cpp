#include "pch.h"
#include "Control.h"

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

    void Control::handle_command() {}

	RECT Control::getRect() const
	{
		RECT rect;
		BOOL r = GetWindowRect(hWnd, &rect);
		if (r == FALSE)
		{
			throw std::runtime_error(__FUNCTION__);
		}
		return rect;
	}
}
