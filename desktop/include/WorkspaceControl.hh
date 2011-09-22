/**
	SDE desktop
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

class Workspace;

/**
	D-Bus interface for remote desktop controlling
*/
class WorkspaceControl : public QObject {
	Q_OBJECT
public:

	/**
		Constructor
	*/
	WorkspaceControl(QObject *parent = 0);

	/**
		Set workspace
	*/
	inline void setWorkspace(Workspace* workspace) {
		_workspace = workspace;
	}

	/**
		Get workspace
	*/
	inline Workspace* workspace() {
		return _workspace;
	}

public slots:

	/**
		A remote method for setting workspace wallpaper
		@par arg
		Full image path. Example: /usr/share/sde/data/wallpaper.png
	*/
	Q_SCRIPTABLE void setWallpaper(const QString& arg);

	/**
		A remote method for adding a new applet
		@par arg
		Full applet path. Example: /usr/share/sde/applets/libsde-panel-applet.so
	*/
	Q_SCRIPTABLE void addApplet(const QString& arg);

	/**
		A remote method for removing an applet
		@par arg
		Applet name. Example: Panel
	*/
	Q_SCRIPTABLE void removeApplet(const QString& arg);

	/**
		A remote method for dumping applets to file
	*/
	Q_SCRIPTABLE void dumpApplets();

private:
	/// Workspace pointer
	Workspace* _workspace;
};

