
#include "Control.h"

namespace rtk
{
    Control::Control()
    : hWnd(NULL) {}

    Control::~Control() {}

    HWND Control::get_hwnd() const
    {
        return hWnd;
    }

    void Control::handle_command() {}
}
