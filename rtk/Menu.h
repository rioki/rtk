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
    /*!
     * Menu
     *
     * This class encapulates menus, submenus and popup menus.
     */
    class RTK_EXPORT Menu
    {
    public:
        /*!
         * Menu Item
         *
         * The menu item is a wraper around commands and submenu anchor
         * points.
         */
        class RTK_EXPORT MenuItem
        {
        public:

            MenuItem(HMENU menu, DWORD id, std::function<void ()> callback);

            MenuItem(HMENU menu, std::shared_ptr<Menu> submenu);

            MenuItem(const MenuItem&) = delete;

            MenuItem& operator = (const MenuItem&) = delete;

            /*!
             * Get the menu item's id.
             *
             * This is the id used for WM_COMMAND.
             *
             * @return the id
             */
            DWORD get_id() const;

            /*!
             * Get the menu item's caption.
             *
             * @return the caption
             */
            std::wstring get_caption() const;

            /*!
             * Set the menu item's caption.
             *
             * @param value the caption
             */
            void set_caption(const std::wstring_view value);

        private:
            HMENU menu = NULL;
            DWORD id = 0;
            std::function<void ()> callback;
            std::shared_ptr<Menu> submenu;

            friend class Menu;
        };

        /*!
         * Create a menu.
         */
        static std::shared_ptr<Menu> create();

        Menu();

        Menu(const Menu&) = delete;

        ~Menu();

        Menu& operator = (const Menu&) = delete;

        /*!
         * Get the HMENU handle for this menu.
         *
         * This cast operator is provided for interoprability with WIN32 function.
         */
        operator HMENU ();

        /*!
         * Get the HMENU handle for this menu.
         *
         * This cast operator is provided for interoprability with WIN32 function.
         */
        operator const HMENU () const;

        /*!
         * Get the HMENU handle for this menu.
         *
         * This function is provided for interoprability with WIN32 function.
         */
        HMENU get_handle();

        /*!
         * Get the HMENU handle for this menu.
         *
         * This function is provided for interoprability with WIN32 function.
         */
        const HMENU get_handle() const;

        /*!
         * Appends a Menu Command
         *
         * @param caption the command's caption
         * @param callback the callback that is triggered when the command is triggered
         *
         * @returns pointer to the MenuItem wrapping this command
         */
        std::shared_ptr<MenuItem> add(const std::wstring_view caption, std::function<void ()> callback);

        /*!
         * Appends a Submenu
         *
         * @param caption the submenu's caption
         * @param menu the submenu
         *
         * @returns pointer to the MenuItem wrapping this submenu
         */
        std::shared_ptr<MenuItem> add(const std::wstring_view caption, std::shared_ptr<Menu> menu);

        /*!
         * Insert a Menu Command
         *
         * @param position the position to insert the command
         * @param caption the command's caption
         * @param callback the callback that is triggered when the command is triggered
         *
         * @returns pointer to the MenuItem wrapping this command
         */
        std::shared_ptr<MenuItem> insert(size_t position, const std::wstring_view caption, std::function<void ()> callback);

        /*!
         * Appends a Submenu
         *
         * @param position the position to insert the submenu
         * @param caption the submenu's caption
         * @param menu the submenu
         *
         * @returns pointer to the MenuItem wrapping this submenu
         */
        std::shared_ptr<MenuItem> insert(size_t position, const std::wstring_view caption, std::shared_ptr<Menu> menu);

        /*!
         * Remove menu item
         *
         * @param position the posiiton of the item to remove
         */
        void remove(size_t position);

        /*!
         * Get all items
         *
         * @returns the items in this menu
         */
        const std::vector<std::shared_ptr<MenuItem>>& get_items() const;

        /*!
         * Handle a command.
         *
         * This function is provided to intercept and handle WM_COMMAND. This
         * is done by the Window class.
         */
        void handle_command(WPARAM wParam);

    private:
        HMENU handle = NULL;

        std::vector<std::shared_ptr<MenuItem>> items;
    };
}
