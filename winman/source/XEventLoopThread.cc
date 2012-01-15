/**
	SDE Window Manager
	Copyright (c) 2011 SDE development team

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <XEventLoopThread.hh>

#include <QDebug>
#include <X11/Xlib.h>
#include <stdlib.h>
#define X11_MISCELLANY
#include <X11/keysymdef.h>
#include <X11/cursorfont.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

void XEventLoopThread::run()
{
	Display* display = XOpenDisplay(getenv("DISPLAY"));
	if (display) {

		Window rootWindow = DefaultRootWindow(display);
		//XSelectInput(display, rootWindow, SubstructureRedirectMask);
#if 1
		int cursor_shape = XC_arrow;
		Cursor cursor = XCreateFontCursor(display, cursor_shape);
		XDefineCursor(display, rootWindow, cursor);
#endif

		XGrabKey(display, XKeysymToKeycode(display, XStringToKeysym("F1")), Mod1Mask, rootWindow,
				 True, GrabModeAsync, GrabModeAsync);
		XGrabButton(display, 1, Mod1Mask, rootWindow, True, ButtonPressMask, GrabModeAsync,
					GrabModeAsync, None, None);
		XGrabButton(display, 3, Mod1Mask, rootWindow, True, ButtonPressMask, GrabModeAsync,
					GrabModeAsync, None, None);

		int width, height;
		width = DisplayWidth(display, DefaultScreen(display));
		height = DisplayHeight(display, DefaultScreen(display));

		height -= 10; // 10 Pixels at the top of the screen for WM debug info

		for (;;) {

			XEvent ev;
			XWindowAttributes attr;
			XButtonEvent start;

			XNextEvent(display, &ev);
			if(ev.type == KeyPress && ev.xkey.subwindow != None)
				XRaiseWindow(display, ev.xkey.subwindow);
			else if(ev.type == ButtonPress && ev.xbutton.subwindow != None)
			{
				XGrabPointer(display, ev.xbutton.subwindow, True,
							 PointerMotionMask|ButtonReleaseMask, GrabModeAsync,
							 GrabModeAsync, None, None, CurrentTime);
				XGetWindowAttributes(display, ev.xbutton.subwindow, &attr);
				start = ev.xbutton;
			}
			else if(ev.type == MotionNotify)
			{
				int xdiff, ydiff;
				while(XCheckTypedEvent(display, MotionNotify, &ev));
				xdiff = ev.xbutton.x_root - start.x_root;
				ydiff = ev.xbutton.y_root - start.y_root;
				XMoveResizeWindow(display, ev.xmotion.window,
								  attr.x + (start.button==1 ? xdiff : 0),
								  attr.y + (start.button==1 ? ydiff : 0),
								  MAX(1, attr.width + (start.button==3 ? xdiff : 0)),
								  MAX(1, attr.height + (start.button==3 ? ydiff : 0)));
			}
			else if(ev.type == ButtonRelease)
				XUngrabPointer(display, CurrentTime);
		}
	}
	qDebug() << "Cannot open display";
	QThread::exit(1);
}
