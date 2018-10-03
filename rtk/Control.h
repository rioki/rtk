#pragma once

#include "config.h"

namespace rtk
{
    class RTK_EXPORT Control
    {
    public:
        Control() = default;

		Control(const Control&) = delete;

        virtual ~Control() = default;

		const Control& operator = (const Control&) = delete;

		operator HWND () const;

		int get_left() const;

		int get_top() const;

		int get_right() const;

		int get_bottom() const;

		int get_width() const;

		int get_height() const;

		bool is_visible() const;

        virtual void handle_command();

    protected:        
        HWND hWnd = nullptr;

	private:
		RECT getRect() const;

    };
}

