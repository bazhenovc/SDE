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

#include <PanelWidget.hh>
#include <QtCore/QLinkedList>

class QLabel;
class QHBoxLayout;
class QSettings;
class Applet;
class PanelMenu;

/**
	Main panel.
*/
class Panel : public PanelWidget {
	Q_OBJECT
public:

	/**
		Constructor
	*/
	Panel(QWidget* parent);

	/**
		Destructor
	*/
	~Panel();

public:

	/**
		Set background image option for this panel
	*/
	void setBackgroundImageOpt(const QString& path);

	/**
		Set panel height option for this panel
	*/
	void setHeightOpt(int height);

	/**
		Load one applet from file
		@return
		Returns loaded applet especially for LookAndFeelWidget
	*/
	Applet* loadApplet(const QString& file);

	/**
		Add applet
		@brief
		Added applet is not managed here
	*/
	void addApplet(Applet* applet);

	/**
		Remove applet
	*/
	void removeApplet(const QString& name);

	/**
		Get applets list
	*/
	const QLinkedList<Applet*>& applets() const {
		return _applets;
	}

	/**
		Dump applets to the file
	*/
	void dumpApplets();

	/**
		Remove all applets
	*/
	void removeAll();


	/**
		Override
	*/
	virtual void showConfigDialog() {}

signals:

	void clicked();

private:
	/// Background image setting
	QString optBackgroundImage;

	/// Panel height
	int     optHeight;

	/// Settings file
	QSettings* settings;

	/// Panel menu
	PanelMenu* menu;

public slots:

	void showSettings();
	void doQuit();

private:
	/// Background image
	QLabel* _background;

	/// Layout
	QHBoxLayout* layout;

	/// Applets
	QLinkedList<Applet*> _applets;

	/**
		Create all widgets
	*/
	void createWidgets();

	/**
		Load default applets from .sde/panel-applets
	*/
	void loadDefaultApplets();

protected:

	void mouseReleaseEvent(QMouseEvent *);
};
