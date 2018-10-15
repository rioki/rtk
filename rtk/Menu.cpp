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
    Menu::Menu()
    {
        hMenu = CreateMenu();
        if (hMenu == NULL)
        {
			throw std::runtime_error(get_last_error());
		}
    }

    Menu::~Menu()
    {
        DestroyMenu(hMenu);
    }

    Menu::operator HMENU ()
    {
        DBG_ASSERT(hMenu != NULL);
        return hMenu;
    }

    Menu::operator const HMENU () const
    {
        DBG_ASSERT(hMenu != NULL);
        return hMenu;
    }
    
    void Menu::add(const std::wstring_view caption, std::function<void()> callback)
    {
        DBG_ASSERT(hMenu != NULL);
        DBG_ASSERT(callback != NULL);

        DWORD id = get_unique_id();
        callbacks[id] = callback;

        BOOL r = AppendMenu(hMenu, MF_STRING, id, caption.data());
        if (r != TRUE)
        {
			throw std::runtime_error(get_last_error());
        }
    }

    void Menu::add(const std::wstring_view caption, std::shared_ptr<Menu> menu)
    {
        DBG_ASSERT(hMenu != NULL);
        DBG_ASSERT(menu != NULL);

        submenus.push_back(menu);

        HMENU hSubMenu = *menu;

        BOOL r = AppendMenu(hMenu,MF_POPUP, reinterpret_cast<INT_PTR>(hSubMenu), caption.data());
        if (r != TRUE)
        {
			throw std::runtime_error(get_last_error());
        }
    }

    void Menu::handle_command(WPARAM wParam)
    {
        auto i = callbacks.find(static_cast<DWORD>(wParam));
        if (i != callbacks.end())
        {
            DBG_ASSERT(i->second);
            i->second();
        }
        else
        {
            for (auto submenu : submenus)
            {
                submenu->handle_command(wParam);
            }
        }
    }
}
