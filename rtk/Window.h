#pragma once

#include "config.h"

#include <string>

#include "Control.h"

namespace rtk
{
    class RTK_EXPORT Window : public Control
    {
    public:

		Window(const std::string_view caption);

        Window(int left, int top, int width, int height, const std::string_view caption);

        ~Window();

		std::string get_caption() const;

        void show(int cmd = SW_SHOW);

        void hide();

        void close();

        void run();
    };

}
