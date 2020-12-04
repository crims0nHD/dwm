/* cc transient.c -o transient -lX11 */

#include <stdlib.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

int main(void) {
	Display *display;
	Window rootWindow, f, t = None;
	XSizeHints h;
	XEvent event;

	display = XOpenDisplay(NULL);
	if (!display)
		exit(1);
	rootWindow = DefaultRootWindow(display);

	f = XCreateSimpleWindow(display, rootWindow, 100, 100, 400, 400, 0, 0, 0);
	h.min_width = h.max_width = h.min_height = h.max_height = 400;
	h.flags = PMinSize | PMaxSize;
	XSetWMNormalHints(display, f, &h);
	XStoreName(display, f, "floating");
	XMapWindow(display, f);

	XSelectInput(display, f, ExposureMask);
	while (1) {
		XNextEvent(display, &event);

		if (t == None) {
			sleep(5);
			t = XCreateSimpleWindow(display, rootWindow, 50, 50, 100, 100, 0, 0, 0);
			XSetTransientForHint(display, t, f);
			XStoreName(display, t, "transient");
			XMapWindow(display, t);
			XSelectInput(display, t, ExposureMask);
		}
	}

	XCloseDisplay(display);
	exit(0);
}
