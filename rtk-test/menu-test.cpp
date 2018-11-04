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
	rtk::Window window;
    
    HMENU hMenu = GetMenu(window);
    EXPECT_TRUE(NULL == hMenu);
}

TEST(Menu, set_menu)
{
    rtk::Window window;
    auto menu = std::make_shared<rtk::Menu>();

    window.set_menu(menu);

    HMENU hMenu = GetMenu(window);
    EXPECT_TRUE(hMenu == static_cast<HMENU>(*menu));
}

TEST(Menu, set_menu_null)
{
    rtk::Window window;
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

TEST(Menu, add_ordering)
{
    auto menu = rtk::Menu::create();
    
    auto one = menu->add(L"&One", [&] () {});
    auto two = menu->add(L"&Two", [&] () {});

    auto items = menu->get_items();

    EXPECT_EQ(2, items.size());
    EXPECT_EQ(one, items.at(0));
    EXPECT_EQ(two, items.at(1));
}

TEST(Menu, item_caption)
{
    auto menu = rtk::Menu::create();
    
    auto one = menu->add(L"&One", [&] () {});
    
    EXPECT_EQ(L"&One", one->get_caption());    
}

TEST(Menu, insert_ordering)
{
    auto menu = rtk::Menu::create();
    
    auto one = menu->add(L"&One", [&] () {});
    auto two = menu->add(L"&Two", [&] () {});

    auto three = menu->insert(1, L"&Three", [&] () {});

    auto items = menu->get_items();

    EXPECT_EQ(3, items.size());
    EXPECT_EQ(one, items.at(0));
    EXPECT_EQ(three, items.at(1));
    EXPECT_EQ(two, items.at(2));
}

TEST(Menu, insert_maintains_internal_state)
{
    auto menu = rtk::Menu::create();
    
    auto one = menu->add(L"&One", [&] () {});
    auto two = menu->add(L"&Two", [&] () {});

    auto three = menu->insert(1, L"&Three", [&] () {});

    EXPECT_EQ(L"&One", one->get_caption());  
    EXPECT_EQ(L"&Two", two->get_caption());  
    EXPECT_EQ(L"&Three", three->get_caption());  
}
