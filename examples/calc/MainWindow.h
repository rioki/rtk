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

#include <rtk/rtk.h>

namespace calc
{
	class MainWindow : public rtk::Window
	{
	public:

		MainWindow();
		
	private:	
        float value = 0.0f;
        enum OP
        {
            NOP,
            ADD,
            SUB,
            MUL,
            DIV,
            EVA
        };
        OP op;

		rtk::TextInput display      = {*this,   2,   2, 146, 24};
        rtk::Button    button_c     = {*this,   2,  28,  35, 35, "C"};
        rtk::Button    button_ce    = {*this,  39,  28,  35, 35, "CE"};
        rtk::Button    button_bk    = {*this,  76,  28,  35, 35, "<"};
        rtk::Button    button_add   = {*this, 113,  28,  35, 35, "+"};
        rtk::Button    button_1     = {*this,   2,  65,  35, 35, "1"};
        rtk::Button    button_2     = {*this,  39,  65,  35, 35, "2"};
        rtk::Button    button_3     = {*this,  76,  65,  35, 35, "3"};
        rtk::Button    button_sub   = {*this, 113,  65,  35, 35, "-"};
        rtk::Button    button_4     = {*this,   2, 102,  35, 35, "4"};
        rtk::Button    button_5     = {*this,  39, 102,  35, 35, "5"};
        rtk::Button    button_6     = {*this,  76, 102,  35, 35, "6"};
        rtk::Button    button_mul   = {*this, 113, 102,  35, 35, "*"};
        rtk::Button    button_7     = {*this,   2, 139,  35, 35, "7"};
        rtk::Button    button_8     = {*this,  39, 139,  35, 35, "8"};
        rtk::Button    button_9     = {*this,  76, 139,  35, 35, "9"};
        rtk::Button    button_div   = {*this, 113, 139,  35, 35, "/"};
        rtk::Button    button_neg   = {*this,   2, 176,  35, 35, "-"};
        rtk::Button    button_0     = {*this,  39, 176,  35, 35, "0"};
        rtk::Button    button_dot   = {*this,  76, 176,  35, 35, "."};
        rtk::Button    button_eva    = {*this, 113, 176,  35, 35, "="};
	
        void add_digit(char c);
        void push_op(OP next_op);
    };
}

