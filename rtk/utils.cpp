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

#include "dbg.h"
#include "utils.h"

namespace rtk
{
    std::wstring widen(const std::string_view value)
    {
        if (value.empty())
        {
            return std::wstring();
        }
        
        std::vector<wchar_t> buff(value.size() + 126);
        int r = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, value.data(), value.size(), buff.data(), buff.size());
        if (r == 0)
        {
            throw std::logic_error("widen failed");        
        }
        else
        {
            return std::wstring(buff.data());
        }    
    }

    std::string narrow(const std::wstring_view value)
    {
        if (value.empty())
        {
            return std::string();
        }
        
        std::vector<char> buff(value.size() * 2);
        int r = WideCharToMultiByte(CP_UTF8, 0, value.data(), value.size(), buff.data(), buff.size(), NULL, NULL);
        if (r == 0)
        {
            throw std::logic_error("narrow failed");        
        }
        else
        {
            return std::string(buff.data());
        }
    }

    std::string get_last_error() 
    { 
        LPVOID lpMsgBuf;
        DWORD dw = GetLastError(); 
        DWORD dwFlags = FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS;

        FormatMessage(dwFlags, NULL, dw, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);

        std::string r = narrow((LPCTSTR)lpMsgBuf);

        LocalFree(lpMsgBuf);
        
        return r;
    }

    void show_message_box(const std::string& caption, const std::string& text)
    {
        MessageBox(NULL, widen(text).c_str(), widen(caption).c_str(), MB_OK|MB_ICONERROR);
    }

    std::wstring get_app_name()
    {
        std::array<wchar_t, MAX_PATH> buffer;
        DWORD r = GetModuleFileName(NULL, buffer.data(), buffer.size());
        DBG_ASSERT(r != 0); // an executable must have a name
        
        std::wstring path(buffer.data(), r);
        size_t b = path.rfind(L'\\');
        if (b == std::wstring::npos) // it may be just the executable
        {
            b = 0;
        }
        else
        {
            b += 1;
        }

        size_t e = path.rfind(L'.');
        DBG_ASSERT(e != std::wstring::npos); // executables end in .exe
        DBG_ASSERT(b < e);

        return path.substr(b, e - b);
    }
}
