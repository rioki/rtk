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

TEST(Menu, construct) 
{
	auto menu = rtk::Menu::create();
    EXPECT_TRUE(nullptr != menu);
	EXPECT_TRUE(NULL != static_cast<HMENU>(*menu));
}

TEST(Menu, initial_menu_is_null) 
{
	rtk::Window window(__FUNCTION__);
    
    HMENU hMenu = GetMenu(window);
    EXPECT_TRUE(NULL == hMenu);
}

TEST(Menu, set_menu)
{
    rtk::Window window(__FUNCTION__);
    auto menu = std::make_shared<rtk::Menu>();

    window.set_menu(menu);

    HMENU hMenu = GetMenu(window);
    EXPECT_TRUE(hMenu == static_cast<HMENU>(*menu));
}

TEST(Menu, set_menu_null)
{
    rtk::Window window(__FUNCTION__);
    std::shared_ptr<rtk::Menu> menu;

    window.set_menu(menu);

    HMENU hMenu = GetMenu(window);
    EXPECT_TRUE(NULL == hMenu);
}

TEST(Menu, dispatch)
{
    auto menu = rtk::Menu::create();
    
    bool triggered = false;
    auto menuItem = menu->add(L"&Test", [&] () {
        triggered = true;
    });

    menu->handle_command(menuItem->get_id());

    EXPECT_EQ(true, triggered);
}

