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

#include <QObject>

/**
	A remote interface to control panel
*/
class PanelControl : public QObject {
public:

	/**
		Constructor
	*/
	PanelControl(Panel* parent);

	/**
		Destructor
	*/
	virtual ~PanelControl();

	/**
		A remote method to change panel size
	*/
	Q_SCRIPTABLE void setSize(int newSize);

	/**
		A remote method to change panel background
	*/
	Q_SCRIPTABLE void setBackground(const QString& newBackground);

	/**
		A remote method to add panel applet
	*/
	Q_SCRIPTABLE void addApplet(const QString& appletPath);

	/**
		A remote method to remove panel applet
	*/
	Q_SCRIPTABLE void removeApplet(const QString& applet);
};
