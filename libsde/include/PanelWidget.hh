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

#include <QtGui/QWidget>

enum PanelPlacement {
	PP_Top,
	PP_Bottom,
	PP_Left,
	PP_Right
};

/**
	Panel widget is a base class for all widgets want to implement panel
	functionality: regular panels, virtual keyboards, etc.
*/
class PanelWidget: public QWidget {
	Q_OBJECT
public:

	/**
		Constructor
	*/
	PanelWidget(QWidget* parent = 0);

	/**
		Destructor
	*/
	virtual ~PanelWidget();

	/**
		Show config dialog.
		@brief
		Reimplement this method if you want your panel to be configurable
	*/
	virtual void showConfigDialog() {}

	/**
		Set background image option
		@brief
		Reimplement this method if you want your panel to have configurable
		backgrounds
	*/
	virtual void setBackgroundImageOpt(const QString& path) {}

protected:

	/**
		Initialize X11 strut
	*/
	void setStrut();

	/**
		Init NetWM hints
	*/
	void setNetWMHints();

private:
	/// Panel placement
	PanelPlacement _placement;

	/**
		This is a dirty hack to avoid including QX11Info and QApplication in the
		same file. Implemented in source/PanelWidget_setGeometry.cc
	*/
	void _setGeometry();
};
