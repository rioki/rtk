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
#include <vector>
#include <map>
#include <functional>
#include <memory>

namespace rtk
{
    /**
     * Menu 
     *
     * This class encapulates menus, submenus and popup menus.
     */
    class RTK_EXPORT Menu
    {
    public:
        
        class RTK_EXPORT MenuItem
        {
        public:

            MenuItem(HMENU menu, UINT position, DWORD id, std::function<void ()> callback);

            MenuItem(HMENU menu, UINT position, std::shared_ptr<Menu> submenu);
        
            MenuItem(const MenuItem&) = delete;

            MenuItem& operator = (const MenuItem&) = delete;

            DWORD get_id() const;

        private:
            HMENU menu = NULL;
            UINT position = 0;
            DWORD id = 0;
            std::function<void ()> callback;
            std::shared_ptr<Menu> submenu;

            friend class Menu;
        };

        /** 
         * Create a menu.
         */
        static std::shared_ptr<Menu> create();

        Menu();

        Menu(const Menu&) = delete;

        ~Menu();

        Menu& operator = (const Menu&) = delete;

        operator HMENU ();

        operator const HMENU () const;

        std::shared_ptr<MenuItem> add(const std::wstring_view caption, std::function<void ()> callback);

        std::shared_ptr<MenuItem> add(const std::wstring_view caption, std::shared_ptr<Menu> menu);

        void handle_command(WPARAM wParam);

    private:
        HMENU handle = NULL;
        
        std::vector<std::shared_ptr<MenuItem>> items;
    };
}
