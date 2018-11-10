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

#include "StatusBar.h"
#include "utils.h"
#include "dbg.h"

namespace rtk
{
    StatusBar::StatusBar(Control& parent)
    {
        InitCommonControls();

        DWORD dwStyle = SBARS_SIZEGRIP | WS_CHILD | WS_VISIBLE;

        DWORD id = get_unique_id();

        hWnd = CreateWindowExW(NULL, STATUSCLASSNAME, NULL, dwStyle, 0, 0, 0, 0, parent, (HMENU)id, GetModuleHandle(NULL), NULL);
        if (hWnd == NULL)
        {
            throw std::runtime_error(narrow(get_last_error()));
        }
        SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)this);

        reset_segments();
    }

    void StatusBar::set_segment_count(size_t value)
    {
        segment_count = value;
        reset_segments();
    }

    size_t StatusBar::get_segment_count() const
    {
        return segment_count;
    }

    void StatusBar::set_text(size_t segment, const std::wstring_view text)
    {
        if (segment >= segment_count)
        {
            throw std::invalid_argument("StatusBar::set_text segment segment >= segment_count");
        }

        SendMessageW(hWnd, SB_SETTEXT, segment, (LPARAM)text.data());
    }

    std::wstring StatusBar::get_text(size_t segment) const
    {
        if (segment >= segment_count)
        {
            throw std::invalid_argument("StatusBar::set_text segment segment >= segment_count");
        }

        int len = SendMessageW(hWnd, SB_GETTEXTLENGTH, segment, 0);

        std::vector<wchar_t> buffer(len + 1);

        len = SendMessageW(hWnd, SB_GETTEXT, segment, (LPARAM)buffer.data());
        if (len + 1 != buffer.size())
        {
            throw std::runtime_error("Failed to get text from statusbar.");
        }

        return std::wstring(buffer.data(), buffer.size() - 1);
    }

    void StatusBar::handle_resize()
    {
        reset_segments();
        SendMessageW(hWnd, WM_SIZE, 0, 0);
    }

    void StatusBar::reset_segments()
    {
        Control* parent = get_parent();
        DBG_ASSERT(parent != nullptr);

        int width = parent->get_width();

        std::vector<int> segment_ends(segment_count);

        int segment_width = width / segment_count;
        int right_edge = segment_width;
        for (size_t i = 0; i < segment_count; i++)
        {
           segment_ends[i] = right_edge;
           right_edge += segment_width;
        }

        SendMessageW(hWnd, SB_SETPARTS, (WPARAM)segment_width, (LPARAM)segment_ends.data());
    }
}