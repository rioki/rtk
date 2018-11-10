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

TEST(StatusBar, construct)
{
	rtk::Window window;
	auto status_bar = window.create_status_bar();

	EXPECT_EQ(status_bar, window.get_status_bar());
}

TEST(StatusBar, resize)
{
	rtk::Window window;
	auto status_bar = window.create_status_bar();

	EXPECT_EQ(window.get_inner_width(), status_bar->get_width());
	EXPECT_EQ(22, status_bar->get_height());

    window.resize(1000, 500);

    EXPECT_EQ(window.get_inner_width(), status_bar->get_width());
	EXPECT_EQ(22, status_bar->get_height());
}

TEST(StatusBar, segments)
{
	rtk::Window window;
	auto status_bar = window.create_status_bar();

	EXPECT_EQ(1, status_bar->get_segment_count());

    status_bar->set_segment_count(3);
	EXPECT_EQ(3, status_bar->get_segment_count());

    status_bar->set_text(1, L"YOLO");
    EXPECT_EQ(L"YOLO", status_bar->get_text(1));
}

TEST(StatusBar, segment_out_of_bounds)
{
	rtk::Window window;
	auto status_bar = window.create_status_bar();

	status_bar->set_segment_count(3);

    EXPECT_THROW(status_bar->set_text(3, L"YOLO"), std::invalid_argument);
    EXPECT_THROW(status_bar->get_text(3), std::invalid_argument);
}