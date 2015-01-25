
#ifndef _RTK_CONTROL_H_
#define _RTK_CONTROL_H_

#include "config.h"

namespace rtk
{
    class RTK_EXPORT Control
    {
    public:
        Control();

        ~Control();

        HWND get_hwnd() const;

        virtual void handle_command();

    protected:        
        HWND hWnd;

    private:
        Control(const Control&);
        const Control& operator = (const Control&);
    };
}

#endif
