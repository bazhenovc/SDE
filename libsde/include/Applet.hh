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
#pragma once

#include <QtCore/QString>
#include <QtCore/QLibrary>

class QWidget;
class QLayout;

/**
	Applet capabilities. 0 means that the applet can be placed only on the
	desktop, 1 - on desktop and panel
*/
enum AppletCaps {
	AC_Desktop = 0,
	AC_Panel
};

/**
	A generic panel applet
	@brief
	An applet is a shared library, that contains 2 functions:
	AppletMain() which is an entry point
	AppletName() which returns unique applet name
	AppletCaps() which returns applet capabilities to embed into existing
	containers
*/
class Applet : public QLibrary {
public:

	typedef QWidget*   (*AppletMainFunc)(QWidget* parent);
	typedef QString    (*AppletNameFunc)();
	typedef AppletCaps (*AppletCapsFunc)();


	/**
		Construct and load an applet
	*/
	Applet(const QString& filename);

	/**
		Destructor
	*/
	virtual ~Applet();

	/**
		Get applet widget
	*/
	QWidget* getWidget(QWidget* parent);

	/**
		Reload with a different name
	*/
	void reload(const QString& name);

	/**
		Get applet name
	*/
	inline const QString& name() const {
		return _name;
	}

	/**
		Check whether applet is broken
	*/
	inline bool broken() const {
		return mainFunc == NULL;
	}

	/**
		Get applet capabilities
	*/
	inline AppletCaps caps() const {
		return _caps;
	}

private:

	void _load();

	AppletMainFunc mainFunc;
	void* libHandle;

	QWidget* _widget;

	QString _name;

	QString _filename;

	AppletCaps _caps;
};
