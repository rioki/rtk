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

#include "Menu.h"

#include "dbg.h"
#include "utils.h"

namespace rtk
{
    Menu::MenuItem::MenuItem(HMENU m, UINT p, DWORD i, std::function<void()> c)
    : menu(m), position(p), id(i), callback(c) {}

    Menu::MenuItem::MenuItem(HMENU m, UINT p, std::shared_ptr<Menu> sm)
    : menu(m), position(p), submenu(sm) {}
    
    DWORD Menu::MenuItem::get_id() const
    {
        return id;
    }

    std::shared_ptr<Menu> Menu::create()
    {
        return std::make_shared<Menu>();
    }

    Menu::Menu()
    {
        handle = CreateMenu();
        if (handle == NULL)
        {
			throw std::runtime_error(get_last_error());
		}
    }

    Menu::~Menu()
    {
        DestroyMenu(handle);
    }

    Menu::operator HMENU ()
    {
        DBG_ASSERT(handle != NULL);
        return handle;
    }

    Menu::operator const HMENU () const
    {
        DBG_ASSERT(handle != NULL);
        return handle;
    }
    
    std::shared_ptr<Menu::MenuItem> Menu::add(const std::wstring_view caption, std::function<void()> callback)
    {
        DBG_ASSERT(handle != NULL);
        DBG_ASSERT(callback != NULL);

        DWORD id = get_unique_id();
        
        BOOL r = AppendMenu(handle, MF_STRING, id, caption.data());
        if (r != TRUE)
        {
			throw std::runtime_error(get_last_error());
        }

        auto item = std::make_shared<MenuItem>(handle, items.size(), id, callback);
        items.push_back(item);

        return item;
    }

    std::shared_ptr<Menu::MenuItem> Menu::add(const std::wstring_view caption, std::shared_ptr<Menu> menu)
    {
        DBG_ASSERT(handle != NULL);
        DBG_ASSERT(menu != NULL);

        HMENU hSubMenu = *menu;

        BOOL r = AppendMenu(handle,MF_POPUP, reinterpret_cast<INT_PTR>(hSubMenu), caption.data());
        if (r != TRUE)
        {
			throw std::runtime_error(get_last_error());
        }

        auto item = std::make_shared<MenuItem>(handle, items.size(), menu);
        items.push_back(item);

        return item;
    }

    void Menu::handle_command(WPARAM wParam)
    {
        for (auto item : items)
        {
            if (item->id == wParam)
            {
                DBG_ASSERT(item->callback);
                item->callback();
            }
            else if (item->submenu)
            {
                item->submenu->handle_command(wParam);
            }
        }
    }
    
}
