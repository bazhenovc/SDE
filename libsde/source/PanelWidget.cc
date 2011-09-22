/**
	SDE core libraries
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

#include <PanelWidget.hh>
#include <NetWM.hh>

#include <QX11Info>

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>

PanelWidget::PanelWidget(QWidget *parent)
	: QWidget(parent) {
	//setWindowFlags(Qt::WindowStaysOnTopHint);
	setWindowFlags(Qt::FramelessWindowHint);
	setWindowFlags(Qt::WindowStaysOnTopHint);
	NetWM::init(QX11Info::display());
	_setGeometry();
}

PanelWidget::~PanelWidget() {
}

void PanelWidget::setStrut() {
	unsigned long data[12] = { 0 };

	int i = 2;
	data[i] = height();
	data[4 + i*2] = x();
	data[5 + i*2] = x() + width();

	XChangeProperty(QX11Info::display(), winId(),
					NetWM::NET_WM_STRUT_PARTIAL,
					XA_CARDINAL, 32, PropModeReplace,
					(unsigned char *)data, 12);

	XChangeProperty(QX11Info::display(), winId(),
					NetWM::NET_WM_STRUT,
					XA_CARDINAL, 32, PropModeReplace, (unsigned char *)data, 4);

}

void PanelWidget::setNetWMHints() {
	Atom state[3];
	unsigned int val;

	state[0] = NetWM::NET_WM_WINDOW_TYPE_DOCK;

	XChangeProperty(QX11Info::display(), winId(),
					NetWM::NET_WM_WINDOW_TYPE, XA_ATOM,
					32, PropModeReplace, (unsigned char *)state, 1);

	// Panel is visible on all desktops
	val = 0xffffffff;

	XChangeProperty(QX11Info::display(), winId(),
					NetWM::NET_WM_DESKTOP, XA_CARDINAL, 32,
					PropModeReplace, (unsigned char *)&val, 1);

	state[0] = NetWM::NET_WM_STATE_SKIP_PAGER;
	state[1] = NetWM::NET_WM_STATE_SKIP_TASKBAR;
	state[2] = NetWM::NET_WM_STATE_STICKY;

	XChangeProperty(QX11Info::display(), winId(),
					NetWM::NET_WM_STATE, XA_ATOM,
					32, PropModeReplace, (unsigned char *)state, 3);
}

