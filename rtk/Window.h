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

#include <string>
#include <memory>

#include "Control.h"

namespace rtk
{
    class Menu;
    class StatusBar;

    class RTK_EXPORT Window : public Control
    {
    public:

        explicit Window();

        explicit Window(const std::wstring_view caption);

        Window(int left, int top, int width, int height, const std::wstring_view caption);

		std::wstring get_caption() const;

        void show(int cmd = SW_SHOW);

        void hide();

        void close();

        void run();

        void set_menu(std::shared_ptr<Menu> value);

        std::shared_ptr<Menu> get_menu() const;

        std::shared_ptr<StatusBar> create_status_bar();

        std::shared_ptr<StatusBar> get_status_bar() const;

        void handle_command(WPARAM wParam) override;

        void handle_resize() override;

    private:
        std::shared_ptr<Menu> menu;
        std::shared_ptr<StatusBar> status_bar;
    };

}
