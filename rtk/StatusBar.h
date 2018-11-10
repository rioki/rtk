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

#include "Control.h"

namespace rtk
{

    /*!
     * Status Bar
     */
    class RTK_EXPORT StatusBar : public Control
    {
    public:

        StatusBar(Control& parent);

        /*!
         * Set the segment count.
         */
        void set_segment_count(size_t value);

        /*!
         * Get the segment count.
         */
        size_t get_segment_count() const;

        /*!
         * Set the text of one segment
         */
        void set_text(size_t segment, const std::wstring_view text);

        /*!
         * Get the text of one segment
         */
        std::wstring get_text(size_t segment) const;

        void handle_resize() override;

    private:
        size_t segment_count = 1;

        void reset_segments();
    };

}