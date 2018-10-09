#pragma once

#include "config.h"

#include <string>
#include <functional>

#include "Control.h"

namespace rtk
{
    class RTK_EXPORT Button : public Control
    {
    public:

		Button(Control& parent, const std::string_view caption);

        Button(Control& parent, int x, int y, int width, int height, const std::string_view caption);

        ~Button();

		void set_caption(const std::string_view value);

		std::string get_caption() const;
    
        void on_click(std::function<void ()> cb);

        void handle_command();

    private:
        std::function<void ()> click_cb;

    };
}
