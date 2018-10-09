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

TEST(Button, construct) {
	rtk::Window window(__FUNCTION__);
	rtk::Button button(window, 0, 1, 151, 14, "YOLO");

	// CHECKME
	//EXPECT_EQ(0, button.get_left());
	//EXPECT_EQ(1, button.get_top());
	EXPECT_EQ(151, button.get_width());
	EXPECT_EQ(14, button.get_height());
	EXPECT_EQ("YOLO", button.get_caption());
}

TEST(Button, defaults)
{
	rtk::Window window(__FUNCTION__);
	rtk::Button button(window, "Kick ME");

	EXPECT_EQ(150, button.get_width());
	EXPECT_EQ(24, button.get_height());
	EXPECT_EQ("Kick ME", button.get_caption());
}

TEST(Textbutton, capyion)
{
	rtk::Window window(__FUNCTION__);
	rtk::Button button(window, "Yolo");

	EXPECT_EQ("Yolo", button.get_caption());

	button.set_caption("Swag");
	EXPECT_EQ("Swag", button.get_caption());
}