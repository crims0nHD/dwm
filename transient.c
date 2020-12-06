/* cc transient.c -o transient -lX11 */

#include <stdlib.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

int main(void) {
	Display *display;
	Window rootWindow, f, t = None;
	XSizeHints hintSize;
	XEvent event;

	display = XOpenDisplay(NULL);
	if (!display)
		exit(1);
	rootWindow = DefaultRootWindow(display);

	//Window XCreateSimpleWindow(display, parent, x, y, width, height, border_width, border, background) 
	f = XCreateSimpleWindow(display, rootWindow, 100, 100, 400, 400, 0, 0, 0);
	hintSize.min_width = hintSize.max_width = hintSize.min_height = hintSize.max_height = 400;
	hintSize.flags = PMinSize | PMaxSize;
	XSetWMNormalHints(display, f, &hintSize);
	XStoreName(display, f, "floating");
	XMapWindow(display, f);

	XSelectInput(display, f, ExposureMask);
	while (1) {
		XNextEvent(display, &event);

		if (t == None) {
			sleep(5);
			t = XCreateSimpleWindow(display, rootWindow, 50, 50, 100, 100, 0, 0, 0);
			
			//int XSetTransientForHint(Display *display, Window w, Window prop_window);
			XSetTransientForHint(display, t, f);

			//int XStoreName(Display *display, Window w, char *window_name);	
			XStoreName(display, t, "transient");

			//int XMapWindow(Display *display, Window w);
			XMapWindow(display, t);

			XSelectInput(display, t, ExposureMask);
		}
	}

	XCloseDisplay(display);
	exit(0);
}
