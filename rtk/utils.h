#pragma once

#include "config.h"

#include <string>

namespace rtk
{
    RTK_EXPORT std::wstring widen(const char* str);
    RTK_EXPORT std::wstring widen(const std::string& str);
    RTK_EXPORT std::string narrow(const wchar_t* str);
    RTK_EXPORT std::string narrow(const std::wstring& str);    
    RTK_EXPORT std::string get_last_error();

    enum MessageBoxButtons
    {
        
    };

    enum MessageBoxIcon
    {
    
    };

    RTK_EXPORT void show_message_box(const std::string& caption, const std::string& text);
}
