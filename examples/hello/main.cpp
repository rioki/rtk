
#include <rtk/rtk.h>

INT WINAPI wWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPWSTR lpCmdLine, INT nShowCmd)
{
    try
    {
        rtk::Window window(rtk::Point(200, 200), rtk::Size(150, 100), "Hello RTK");

        rtk::Button button(window, rtk::Point(30, 20), rtk::Size(80, 30), "Click Me!");
        button.on_click([&] () {
            window.close();
        });

        window.show(nShowCmd);
        window.run();

        return 0;
    }
    catch (const std::exception& ex)
    {
        rtk::show_message_box("Error", ex.what());
        return -1;
    }        
}
