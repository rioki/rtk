#include "pch.h"

TEST(Window, construct) {
	rtk::Window window(151, 152, 201, 202, "Hello World");
	EXPECT_EQ(151, window.get_left());
	EXPECT_EQ(152, window.get_top());
	EXPECT_EQ(201, window.get_width());
	EXPECT_EQ(202, window.get_height());
	EXPECT_EQ("Hello World", window.get_caption());
}

