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
#include <Applet.hh>

#include <QtCore/QObject>
#include <QtGui/QLabel>

Applet::Applet(const QString& filename)
	: QLibrary(filename), mainFunc(0), libHandle(0), _widget(0) {
	if (!load())
		return;
	_load();
}

Applet::~Applet() {
	if (_widget)
		delete _widget;
}

QWidget* Applet::getWidget(QWidget* parent) {
	if (!_widget)
	{
		if (!mainFunc) {
			QLabel* lbl = new QLabel(parent);
			lbl->setText(QObject::tr("Invalid or broken applet"));
			_widget = lbl;
		} else
			_widget = mainFunc(parent);
	}
	return _widget;
}

void Applet::reload(const QString &name) {
	QLibrary::setFileName(name);
	if (!load())
		return;
	_load();
}

void Applet::_load() {
	mainFunc = (AppletMainFunc)resolve("AppletMain");
	if (!mainFunc) {
		return;
	}
	AppletNameFunc nameFunc = (AppletNameFunc)resolve("AppletName");
	if (nameFunc) {
		_name = nameFunc();
	}
	AppletCapsFunc capsFunc = (AppletCapsFunc)resolve("AppletCaps");
	if (capsFunc) {
		_caps = capsFunc();
	}
}
