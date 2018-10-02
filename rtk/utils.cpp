#include "pch.h"
#include "utils.h"

namespace rtk
{
    std::wstring widen(const char* value)
    {
        return widen(std::string(value));
    }

    std::wstring widen(const std::string& value)
    {
        if (value.empty())
        {
            return std::wstring();
        }
        
        std::vector<wchar_t> buff(value.size() + 126);
        int r = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, value.c_str(), value.size(), &buff[0], buff.size());
        if (r == 0)
        {
            throw std::logic_error("widen failed");        
        }
        else
        {
            return std::wstring(&buff[0]);
        }    
    }

    std::string narrow(const wchar_t* value)
    {
        return narrow(std::wstring(value));
    }

    std::string narrow(const std::wstring& value)
    {
        if (value.empty())
        {
            return std::string();
        }
        
        std::vector<char> buff(value.size() * 2);
        int r = WideCharToMultiByte(CP_UTF8, 0, value.c_str(), value.size(), &buff[0], buff.size(), NULL, NULL);
        if (r == 0)
        {
            throw std::logic_error("narrow failed");        
        }
        else
        {
            return std::string(&buff[0]);
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
}
