#include "pch.h"

TEST(Window, default_contructor)
{
    rtk::Window window;
    // the caption is the name of the application
    EXPECT_EQ("rtk-test", window.get_caption());
}

TEST(Window, construct) {
	rtk::Window window(151, 152, 201, 202, "Hello World");
	EXPECT_EQ(151, window.get_left());
	EXPECT_EQ(152, window.get_top());
	EXPECT_EQ(201, window.get_width());
	EXPECT_EQ(202, window.get_height());
	EXPECT_EQ("Hello World", window.get_caption());
}

TEST(Window, onlyCaptionConstructor)
{
	rtk::Window window("Hello World");
	// NOTE: we actually don't know where windows puts the window
	EXPECT_EQ(350, window.get_width());
	EXPECT_EQ(350, window.get_height());
	EXPECT_EQ("Hello World", window.get_caption());
}

TEST(Window, show)
{
	rtk::Window window("Hello World");
	window.show();

	EXPECT_TRUE(window.is_visible());
}

TEST(Window, run)
{
	using namespace std::chrono_literals;

	rtk::Window window("Hello World");

	auto start = std::chrono::high_resolution_clock::now();

	auto future = std::async([&]() {
		std::this_thread::sleep_for(100ms);
		window.close();
	});

	window.run();

	auto end = std::chrono::high_resolution_clock::now();

	EXPECT_GE(start + 100ms, end);
} 

TEST(Window, window_as_container)
{
    rtk::Window window;
}
