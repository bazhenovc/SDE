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

#include <QWidget>
#include <QList>

class Applet;
class PanelWidget;

/**
	Workspace manages all desktop widgets and user data
*/
class Workspace : public QWidget {
	Q_OBJECT
public:

	/**
		Constructor
	*/
	Workspace();

	virtual ~Workspace();

	/**
		Load one applet
	*/
	Applet* loadApplet(const QString& path);

	/**
		Remove applet by its file name
	*/
	void removeApplet(const QString& name);

	/**
		Remove all applets
	*/
	void removeAllApplets();

	/**
		Load default applets from file
	*/
	void loadApplets();

	/**
		Dump applets to file
	*/
	void dumpApplets();

	/**
		Get applet list
	*/
	QList<Applet*>& applets() {
		return _applets;
	}

	/**
		Reload settings
	*/
	void reloadSettings();

	/**
		Set desktop wallpaper
	*/
	void setWallpaperOpt(const QString& path);

	/**
		Find applet by name
	*/
	Applet* findApplet(const QString& name);

	/**
		Find applet by file name
	*/
	Applet* findAppletByFileName(const QString& filename);
private:

	/**
		Create default widgets
	*/
	void createWidgets();

	/// List all applets
	QList<Applet*> _applets;

	/// Desktop settings file
	QString desktopSettingsFile;

	/// Applets file
	QString appletsFile;

private slots:

	void onAppsBtnClick();

};
