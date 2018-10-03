#pragma once

#include "config.h"

#include <string>

namespace rtk
{
    RTK_EXPORT std::wstring widen(const std::string_view str);
    RTK_EXPORT std::string narrow(const std::wstring_view str);    
    RTK_EXPORT std::string get_last_error();

    enum MessageBoxButtons
    {
        
    };

    enum MessageBoxIcon
    {
    
    };

    RTK_EXPORT void show_message_box(const std::string& caption, const std::string& text);
}
