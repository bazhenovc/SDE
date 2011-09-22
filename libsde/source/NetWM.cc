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
#include <NetWM.hh>

Atom NetWM::UTF8_STRING = 0;
Atom NetWM::XROOTPMAP_ID = 0;

Atom NetWM::WM_STATE = 0;
Atom NetWM::WM_CLASS = 0;
Atom NetWM::WM_NAME = 0;
Atom NetWM::WM_DELETE_WINDOW = 0;
Atom NetWM::WM_PROTOCOLS = 0;
Atom NetWM::WM_CHANGE_STATE = 0;
Atom NetWM::WM_WINDOW_ROLE = 0;

Atom NetWM::NET_WORKAREA = 0;
Atom NetWM::NET_CLIENT_LIST = 0;
Atom NetWM::NET_CLIENT_LIST_STACKING = 0;
Atom NetWM::NET_NUMBER_OF_DESKTOPS = 0;
Atom NetWM::NET_CURRENT_DESKTOP = 0;
Atom NetWM::NET_DESKTOP_NAMES = 0;
Atom NetWM::NET_ACTIVE_WINDOW = 0;
Atom NetWM::NET_CLOSE_WINDOW = 0;
Atom NetWM::NET_SUPPORTED = 0;
Atom NetWM::NET_WM_DESKTOP = 0;
Atom NetWM::NET_SHOWING_DESKTOP = 0;

Atom NetWM::NET_WM_STATE = 0;
Atom NetWM::NET_WM_STATE_MODAL = 0;
Atom NetWM::NET_WM_STATE_STICKY = 0;
Atom NetWM::NET_WM_STATE_MAXIMIZED_VERT = 0;
Atom NetWM::NET_WM_STATE_MAXIMIZED_HORZ = 0;
Atom NetWM::NET_WM_STATE_SHADED = 0;
Atom NetWM::NET_WM_STATE_SKIP_TASKBAR = 0;
Atom NetWM::NET_WM_STATE_SKIP_PAGER = 0;
Atom NetWM::NET_WM_STATE_HIDDEN = 0;
Atom NetWM::NET_WM_STATE_FULLSCREEN = 0;
Atom NetWM::NET_WM_STATE_ABOVE = 0;
Atom NetWM::NET_WM_STATE_BELOW = 0;
Atom NetWM::NET_WM_STATE_STAYS_ON_TOP = 0;
Atom NetWM::NET_WM_STATE_STAYS_ON_BOTTOM = 0;
Atom NetWM::NET_WM_STATE_DEMANDS_ATTENTION = 0;

Atom NetWM::NET_WM_WINDOW_TYPE = 0;
Atom NetWM::NET_WM_WINDOW_TYPE_DESKTOP = 0;
Atom NetWM::NET_WM_WINDOW_TYPE_DOCK = 0;
Atom NetWM::MODERRO_WINDOW_TYPE_DOCK = 0;
Atom NetWM::NET_WM_WINDOW_TYPE_TOOLBAR = 0;
Atom NetWM::NET_WM_WINDOW_TYPE_MENU = 0;
Atom NetWM::NET_WM_WINDOW_TYPE_UTILITY = 0;
Atom NetWM::NET_WM_WINDOW_TYPE_SPLASH = 0;
Atom NetWM::NET_WM_WINDOW_TYPE_DIALOG = 0;
Atom NetWM::NET_WM_WINDOW_TYPE_DROPDOWN_MENU = 0;
Atom NetWM::NET_WM_WINDOW_TYPE_POPUP_MENU = 0;
Atom NetWM::NET_WM_WINDOW_TYPE_TOOLTIP = 0;
Atom NetWM::NET_WM_WINDOW_TYPE_NOTIFICATION = 0;
Atom NetWM::NET_WM_WINDOW_TYPE_COMBO = 0;
Atom NetWM::NET_WM_WINDOW_TYPE_DND = 0;
Atom NetWM::NET_WM_WINDOW_TYPE_NORMAL = 0;
Atom NetWM::NET_WM_WINDOW_OPACITY = 0;
Atom NetWM::NET_WM_NAME = 0;
Atom NetWM::NET_WM_VISIBLE_NAME = 0;
Atom NetWM::NET_WM_STRUT = 0;
Atom NetWM::NET_WM_STRUT_PARTIAL = 0;
Atom NetWM::NET_WM_ICON = 0;
Atom NetWM::NET_WM_PID = 0;

void NetWM::init(Display* dpy) {

	UTF8_STRING                = XInternAtom(dpy, "UTF8_STRING", False);
	XROOTPMAP_ID               = XInternAtom(dpy, "_XROOTPMAP_ID", False);
	WM_STATE                   = XInternAtom(dpy, "WM_STATE", False);
	WM_CLASS                   = XInternAtom(dpy, "WM_CLASS", False);
	WM_NAME                    = XInternAtom(dpy, "WM_NAME", False);
	WM_DELETE_WINDOW           = XInternAtom(dpy, "WM_DELETE_WINDOW", False);
	WM_CHANGE_STATE            = XInternAtom(dpy, "WM_CHANGE_STATE", False);
	WM_WINDOW_ROLE             = XInternAtom(dpy, "WM_WINDOW_ROLE", False);
	WM_PROTOCOLS               = XInternAtom(dpy, "WM_PROTOCOLS", False);
	NET_WORKAREA               = XInternAtom(dpy, "_NET_WORKAREA", False);
	NET_CLIENT_LIST            = XInternAtom(dpy, "_NET_CLIENT_LIST", False);
	NET_CLIENT_LIST_STACKING   = XInternAtom(dpy, "_NET_CLIENT_LIST_STACKING", False);
	NET_NUMBER_OF_DESKTOPS     = XInternAtom(dpy, "_NET_NUMBER_OF_DESKTOPS", False);
	NET_CURRENT_DESKTOP        = XInternAtom(dpy, "_NET_CURRENT_DESKTOP", False);
	NET_DESKTOP_NAMES          = XInternAtom(dpy, "_NET_DESKTOP_NAMES", False);
	NET_ACTIVE_WINDOW          = XInternAtom(dpy, "_NET_ACTIVE_WINDOW", False);
	NET_CLOSE_WINDOW           = XInternAtom(dpy, "_NET_CLOSE_WINDOW", False);
	NET_SUPPORTED              = XInternAtom(dpy, "_NET_SUPPORTED", False);
	NET_WM_DESKTOP             = XInternAtom(dpy, "_NET_WM_DESKTOP", False);
	NET_SHOWING_DESKTOP        = XInternAtom(dpy, "_NET_SHOWING_DESKTOP", False);

	NET_WM_STATE                     = XInternAtom(dpy, "_NET_WM_STATE", False);
	NET_WM_STATE_MODAL               = XInternAtom(dpy, "_NET_WM_STATE_MODAL", False);
	NET_WM_STATE_STICKY              = XInternAtom(dpy, "_NET_WM_STATE_STICKY", False);
	NET_WM_STATE_MAXIMIZED_VERT      = XInternAtom(dpy, "_NET_WM_STATE_MAXIMIZED_VERT", False);
	NET_WM_STATE_MAXIMIZED_HORZ      = XInternAtom(dpy, "_NET_WM_STATE_MAXIMIZED_HORZ", False);
	NET_WM_STATE_SHADED              = XInternAtom(dpy, "_NET_WM_STATE_SHADED", False);
	NET_WM_STATE_SKIP_TASKBAR        = XInternAtom(dpy, "_NET_WM_STATE_SKIP_TASKBAR", False);
	NET_WM_STATE_SKIP_PAGER          = XInternAtom(dpy, "_NET_WM_STATE_SKIP_PAGER", False);
	NET_WM_STATE_HIDDEN              = XInternAtom(dpy, "_NET_WM_STATE_HIDDEN", False);
	NET_WM_STATE_FULLSCREEN          = XInternAtom(dpy, "_NET_WM_STATE_FULLSCREEN", False);
	NET_WM_STATE_ABOVE               = XInternAtom(dpy, "_NET_WM_STATE_ABOVE", False);
	NET_WM_STATE_BELOW               = XInternAtom(dpy, "_NET_WM_STATE_BELOW", False);
	NET_WM_STATE_STAYS_ON_TOP        = XInternAtom(dpy, "_NET_WM_STATE_STAYS_ON_TOP", False);
	NET_WM_STATE_STAYS_ON_BOTTOM     = XInternAtom(dpy, "_NET_WM_STATE_STAYS_ON_BOTTOM", False);
	NET_WM_STATE_DEMANDS_ATTENTION   = XInternAtom(dpy, "_NET_WM_STATE_DEMANDS_ATTENTION", False);

	NET_WM_WINDOW_TYPE               = XInternAtom(dpy, "_NET_WM_WINDOW_TYPE", False);
	NET_WM_WINDOW_TYPE_DESKTOP       = XInternAtom(dpy, "_NET_WM_WINDOW_TYPE_DESKTOP", False);
	NET_WM_WINDOW_TYPE_DOCK          = XInternAtom(dpy, "_NET_WM_WINDOW_TYPE_DOCK", False);
	MODERRO_WINDOW_TYPE_DOCK         = XInternAtom(dpy, "_MODERRO_WINDOW_TYPE_DOCK", False);
	NET_WM_WINDOW_TYPE_TOOLBAR       = XInternAtom(dpy, "_NET_WM_WINDOW_TYPE_TOOLBAR", False);
	NET_WM_WINDOW_TYPE_MENU          = XInternAtom(dpy, "_NET_WM_WINDOW_TYPE_MENU", False);
	NET_WM_WINDOW_TYPE_UTILITY       = XInternAtom(dpy, "_NET_WM_WINDOW_TYPE_UTILITY", False);
	NET_WM_WINDOW_TYPE_SPLASH        = XInternAtom(dpy, "_NET_WM_WINDOW_TYPE_SPLASH", False);
	NET_WM_WINDOW_TYPE_DIALOG        = XInternAtom(dpy, "_NET_WM_WINDOW_TYPE_DIALOG", False);
	NET_WM_WINDOW_TYPE_DROPDOWN_MENU = XInternAtom(dpy, "_NET_WM_WINDOW_TYPE_DROPDOWN_MENU", False);
	NET_WM_WINDOW_TYPE_POPUP_MENU    = XInternAtom(dpy, "_NET_WM_WINDOW_TYPE_POPUP_MENU", False);
	NET_WM_WINDOW_TYPE_TOOLTIP       = XInternAtom(dpy, "_NET_WM_WINDOW_TYPE_TOOLTIP", False);
	NET_WM_WINDOW_TYPE_NOTIFICATION  = XInternAtom(dpy, "_NET_WM_WINDOW_TYPE_NOTIFICATION", False);
	NET_WM_WINDOW_TYPE_COMBO         = XInternAtom(dpy, "_NET_WM_WINDOW_TYPE_COMBO", False);
	NET_WM_WINDOW_TYPE_DND           = XInternAtom(dpy, "_NET_WM_WINDOW_TYPE_DND", False);
	NET_WM_WINDOW_TYPE_NORMAL        = XInternAtom(dpy, "_NET_WM_WINDOW_TYPE_NORMAL", False);

	NET_WM_WINDOW_OPACITY      = XInternAtom(dpy, "_NET_WM_WINDOW_OPACITY", False);
	NET_WM_NAME                = XInternAtom(dpy, "_NET_WM_NAME", False);
	NET_WM_VISIBLE_NAME        = XInternAtom(dpy, "_NET_WM_VISIBLE_NAME", False);
	NET_WM_STRUT               = XInternAtom(dpy, "_NET_WM_STRUT", False);
	NET_WM_STRUT_PARTIAL       = XInternAtom(dpy, "_NET_WM_STRUT_PARTIAL", False);
	NET_WM_ICON                = XInternAtom(dpy, "_NET_WM_ICON", False);
	NET_WM_PID                 = XInternAtom(dpy, "_NET_WM_PID", False);
}

void* NetWM::getProperty(Display *dpy, Window win, Atom prop, Atom type,
						 int *nitems, bool *ok) {
	Atom type_ret;
	int format_ret;
	unsigned long items_ret;
	unsigned long after_ret;
	unsigned char *prop_data = 0;

	if(XGetWindowProperty(dpy,
						  win,
						  prop,
						  0,
						  0x7fffffff,
						  False,
						  type,
						  &type_ret,
						  &format_ret,
						  &items_ret,
						  &after_ret,
						  &prop_data) != Success) {
		if(ok)
			*ok = false;
		return 0;
	}

	if(nitems)
		*nitems = items_ret;

	if(ok)
		*ok = true;

	return prop_data;
}
