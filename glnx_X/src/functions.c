#include "../../shared/functions.h"
#include <X11/Xlib.h>
#include <stdio.h>

/*Thanks to the example on
 * https://en.wikipedia.org/wiki/Xlib
 */

int launchWindow()
{
    Display *display;
    Window window;
    XEvent event;
    int s;

    /*Open connection with display server*/
    display = XOpenDisplay(NULL);
    if (display == NULL)
    {
        fprintf(stderr, "Cannot open display\n");
    }

    s = DefaultScreen(display);

    /*Create window */
    window = XCreateSimpleWindow(display,
            RootWindow(display,s),
            10,10,200,200,1,
            BlackPixel(display, s),
            WhitePixel(display, s));

    /*Select the events of interest */
    XSelectInput(display, window, KeyPressMask);

    /*Map shows the window*/
    XMapWindow(display,window);

    /*The event loop! */
    for (;;)
    {
        XNextEvent(display, &event);
        if (event.type == KeyPress)
            break;
    }

    /*close the connection to the display server */
    XCloseDisplay(display);
    return 0;
}

