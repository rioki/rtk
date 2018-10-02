
#include "Control.h"

namespace rtk
{
    Control::operator HWND () const
    {
        return hWnd;
    }

    void Control::handle_command() {}
}
