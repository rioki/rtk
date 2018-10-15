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

		int get_inner_width() const;

		int get_inner_height() const;

		bool is_visible() const;

        virtual void handle_command(WPARAM wParam);

    protected:        
        HWND hWnd = nullptr;

		void set_window_text(const std::string_view value);
		std::string get_window_text() const;

		RECT get_rect() const;
		RECT get_client_rect() const;

    };
}

