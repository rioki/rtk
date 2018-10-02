#pragma once

#include "config.h"

namespace rtk
{
    class RTK_EXPORT Control
    {
    public:
        Control() = default;

		Control(const Control&) = delete;

        virtual ~Control() = default;

		const Control& operator = (const Control&) = delete;

		operator HWND () const;

        virtual void handle_command();

    protected:        
        HWND hWnd = nullptr;

    };
}

