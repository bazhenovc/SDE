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

#include <QWidget>

class QSettings;
class QTimer;

/**
	A possible base class for desktop applets.
	@brief
	This class provides configuration support and state saving for desktop
	applets.

	@brief
	Every applet, inheriting this class will have its own independant
	configuration.

	@brief
	By default, new widgets are centered at the screen

	@note
	Duplicated applets are also supported
*/
class AppletWidget : public QWidget {
	Q_OBJECT
public:

	/**
		Constructor
	*/
	AppletWidget(QWidget* parent, const QString& name);

	/**
		Destructor
	*/
	virtual ~AppletWidget();

protected:
	/**
		Get settings
	*/
	QSettings* settings() {
		return _settings;
	}


	bool   _dragging;
	QPoint _dragPoint;

	virtual void mousePressEvent(QMouseEvent *);
	virtual void mouseReleaseEvent(QMouseEvent *);
	virtual void mouseMoveEvent(QMouseEvent *);

private:
	/// Applet settings
	QSettings* _settings;

	/// Old geometry(for drag event)
	QSize _oldSize;
};
