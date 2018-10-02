
#ifndef _RTK_WINDOW_H_
#define _RTK_WINDOW_H_

#include "config.h"

#include <string>

#include "Control.h"

namespace rtk
{
    class RTK_EXPORT Window : public Control
    {
    public:
        Window(int x, int y, int width, int height, const std::string& caption);

        ~Window();

        void show(int cmd = SW_SHOW);

        void hide();

        void close();

        void run();

    private:

        Window(const Window&);
        const Window& operator = (const Window&);
    };

}

#endif
