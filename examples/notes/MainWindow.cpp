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

#include "MainWindow.h"

namespace notes
{
    MainWindow::MainWindow()
    : rtk::Window(L"notes")
    {
        create_menu();    
    }

    void MainWindow::create_menu()
    {
        auto menu = std::make_shared<rtk::Menu>();

        auto fileMenu = std::make_shared<rtk::Menu>();

        auto fileNewMenu = std::make_shared<rtk::Menu>();

        fileNewMenu->add(L"New &Text", [this] () {
        
        });

        fileNewMenu->add(L"New &Hex", [this] () {
        
        });

        fileMenu->add(L"&New", fileNewMenu);

        fileMenu->add(L"&Exit\tAlt+F4", [this] () {
            close();
        });

        menu->add(L"&File", fileMenu);


        set_menu(menu);
    }
}
