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

#include <rtk/dbg.h>
#include "MainWindow.h"

namespace calc
{
	MainWindow::MainWindow()
	: rtk::Window(CW_USEDEFAULT, CW_USEDEFAULT, 166, 252, L"Calculator")
	{
        display.set_text(L"0");

        button_c.on_click([this] () {
            display.set_text(L"0");
        });
        button_ce.on_click([this] () {
            value = 0.0f;
            op = NOP;
            display.set_text(L"0");
        });
        button_bk.on_click([this] () {
            auto text = display.get_text();
            if (text.size() == 1)
            {
                display.set_text(L"0");
            }
            else
            {
                display.set_text(text.substr(0, text.size() - 1));
            }
        });

        button_1.on_click([this] () {
            add_digit(L'1');
        });
        button_2.on_click([this] () {
            add_digit(L'2');
        });
        button_3.on_click([this] () {
            add_digit(L'3');
        });
        button_4.on_click([this] () {
            add_digit(L'4');
        });
        button_5.on_click([this] () {
            add_digit(L'5');
        });
        button_6.on_click([this] () {
            add_digit(L'6');
        });
        button_7.on_click([this] () {
            add_digit(L'7');
        });
        button_8.on_click([this] () {
            add_digit(L'8');
        });
        button_9.on_click([this] () {
            add_digit(L'9');
        });
        button_0.on_click([this] () {
            add_digit(L'0');
        });

        button_dot.on_click([this] () {
            add_digit(L'.');
        });
        button_neg.on_click([this] () {
            add_digit(L'-');
        });
        
        button_add.on_click([this] () {
            push_op(ADD);
        });
        button_sub.on_click([this] () {
            push_op(SUB);
        });
        button_mul.on_click([this] () {
            push_op(MUL);
        });
        button_div.on_click([this] () {
            push_op(DIV);
        });
        button_eva.on_click([this] () {
            push_op(EVA);
        });
	}

    void MainWindow::add_digit(char c) 
    {
        auto text = display.get_text();

        if (op == EVA)
        {
            op = NOP;
            text = L"0";
        }

        if (c == '.')
        {
            if (text.find(L'.') == std::wstring::npos)
            {
                text.push_back(c);    
            }
        }
        else if (c == L'-')
        {
            if (text[0] != L'-')
            {
                text = L"-" + text;
            }
        }
        else
        {
            if (text == L"0")
            {
                text = c;
            }
            else if (text == L"-0")
            {
                text = L"-";
                text.push_back(c);
            }
            else
            {
                text.push_back(c);  
            }
        }

        display.set_text(text);
    }

    void MainWindow::push_op(OP next_op)
    {
        auto text = display.get_text();
        float v = std::stof(text);
        
        switch (op)
        {
            case NOP:
                value = v;
                break;
            case ADD:
                value += v;
                break;
            case SUB:
                value -= v;
                break;
            case MUL:
                value *= v;
                break;
            case DIV:
                value /= v;
                break;
            case EVA:
                // nothing
                break;
            default:
                DBG_FAIL("Unkown OP");
        }

        op = next_op;
        if (next_op != EVA)
        {
            display.set_text(L"0");
        }
        else
        {
            display.set_text(std::to_wstring(value));
        }
    }
}
