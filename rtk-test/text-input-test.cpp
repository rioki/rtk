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

TEST(TextInput, construct) {
	rtk::Window window(__FUNCTION__);
	rtk::TextInput input(window, 0, 1, 151, 14);

	// CHECKME
	//EXPECT_EQ(0, input.get_left());
	//EXPECT_EQ(1, input.get_top());
	EXPECT_EQ(151, input.get_width());
	EXPECT_EQ(14, input.get_height());
}

TEST(TextInput, defaults)
{
	rtk::Window window(__FUNCTION__);
	rtk::TextInput input(window);

	EXPECT_EQ(150, input.get_width());
	EXPECT_EQ(24, input.get_height());
	EXPECT_EQ("", input.get_text());
}

TEST(TextInput, set_get_text)
{
	rtk::Window window(__FUNCTION__);
	rtk::TextInput input(window);

	EXPECT_EQ("", input.get_text());
	
	input.set_text("Yolo");
	EXPECT_EQ("Yolo", input.get_text());
}