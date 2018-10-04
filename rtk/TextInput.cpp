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

#include "TextInput.h"

#include <stdexcept>
#include "utils.h"

namespace rtk
{
	TextInput::TextInput(Control& parent)
	: TextInput(parent, 0, 0, 150, 24) {}

	TextInput::TextInput(Control& parent, int left, int top, int width, int height)
	{
		DWORD dwStyle = WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL;

		hWnd = CreateWindowEx(NULL, L"EDIT", L"", dwStyle, left, top, width, height, parent, NULL, GetModuleHandle(NULL), NULL);
		if (hWnd == NULL)
		{
			throw std::runtime_error(get_last_error());
		}
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)this);
	}

	void TextInput::set_text(const std::string_view value)
	{
		set_window_text(value);
	}

	std::string TextInput::get_text() const
	{
		return get_window_text();
	}
}
