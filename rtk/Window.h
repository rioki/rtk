
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
        Window(int left, int top, int width, int height, const std::string& caption);

        ~Window();

		int get_left() const;

		int get_top() const;

		int get_right() const;

		int get_bottom() const;

		int get_width() const;

		int get_height() const;

		std::string get_caption() const;

        void show(int cmd = SW_SHOW);

        void hide();

        void close();

        void run();

	private:
		RECT getRect() const;
    };

}

#endif
