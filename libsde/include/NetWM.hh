/**
	SDE panel
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
#pragma once

#include <X11/Xlib.h>

struct NetWM {
	static Atom UTF8_STRING;
	static Atom XROOTPMAP_ID;

	static Atom WM_STATE;
	static Atom WM_CLASS;
	static Atom WM_NAME;
	static Atom WM_DELETE_WINDOW;
	static Atom WM_PROTOCOLS;
	static Atom WM_CHANGE_STATE;
	static Atom WM_WINDOW_ROLE;

	static Atom NET_WORKAREA;
	static Atom NET_CLIENT_LIST;
	static Atom NET_CLIENT_LIST_STACKING;
	static Atom NET_NUMBER_OF_DESKTOPS;
	static Atom NET_CURRENT_DESKTOP;
	static Atom NET_DESKTOP_NAMES;
	static Atom NET_ACTIVE_WINDOW;
	static Atom NET_CLOSE_WINDOW;
	static Atom NET_SUPPORTED;
	static Atom NET_WM_DESKTOP;
	static Atom NET_SHOWING_DESKTOP;

	static Atom NET_WM_STATE;
	static Atom NET_WM_STATE_MODAL;
	static Atom NET_WM_STATE_STICKY;
	static Atom NET_WM_STATE_MAXIMIZED_VERT;
	static Atom NET_WM_STATE_MAXIMIZED_HORZ;
	static Atom NET_WM_STATE_SHADED;
	static Atom NET_WM_STATE_SKIP_TASKBAR;
	static Atom NET_WM_STATE_SKIP_PAGER;
	static Atom NET_WM_STATE_HIDDEN;
	static Atom NET_WM_STATE_FULLSCREEN;
	static Atom NET_WM_STATE_ABOVE;
	static Atom NET_WM_STATE_BELOW;
	static Atom NET_WM_STATE_STAYS_ON_TOP;
	static Atom NET_WM_STATE_STAYS_ON_BOTTOM;
	static Atom NET_WM_STATE_DEMANDS_ATTENTION;

	static Atom NET_WM_WINDOW_TYPE;
	static Atom NET_WM_WINDOW_TYPE_DESKTOP;
	static Atom NET_WM_WINDOW_TYPE_DOCK;
	static Atom MODERRO_WINDOW_TYPE_DOCK;
	static Atom NET_WM_WINDOW_TYPE_TOOLBAR;
	static Atom NET_WM_WINDOW_TYPE_MENU;
	static Atom NET_WM_WINDOW_TYPE_UTILITY;
	static Atom NET_WM_WINDOW_TYPE_SPLASH;
	static Atom NET_WM_WINDOW_TYPE_DIALOG;
	static Atom NET_WM_WINDOW_TYPE_DROPDOWN_MENU;
	static Atom NET_WM_WINDOW_TYPE_POPUP_MENU;
	static Atom NET_WM_WINDOW_TYPE_TOOLTIP;
	static Atom NET_WM_WINDOW_TYPE_NOTIFICATION;
	static Atom NET_WM_WINDOW_TYPE_COMBO;
	static Atom NET_WM_WINDOW_TYPE_DND;
	static Atom NET_WM_WINDOW_TYPE_NORMAL;
	static Atom NET_WM_WINDOW_OPACITY;
	static Atom NET_WM_NAME;
	static Atom NET_WM_VISIBLE_NAME;
	static Atom NET_WM_STRUT;
	static Atom NET_WM_STRUT_PARTIAL;
	static Atom NET_WM_ICON;
	static Atom NET_WM_PID;

	static void init(Display* dpy);

	static void* getProperty(Display* dpy, Window win, Atom prop, Atom type,
							 int* nitems, bool* ok);
};
