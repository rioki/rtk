
#ifndef _RTK_BUTTON_H_
#define _RTK_BUTTON_H_

#include "config.h"

#include <string>
#include <functional>

#include "Control.h"

namespace rtk
{
    class RTK_EXPORT Button : public Control
    {
    public:
        Button(Control& parent, int x, int y, int width, int height, const std::string& caption);

        ~Button();
    
        void on_click(std::function<void ()> cb);

        void handle_command();

    private:
        std::function<void ()> click_cb;

    };
}

#endif
