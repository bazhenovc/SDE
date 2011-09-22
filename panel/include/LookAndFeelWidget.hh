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

#include <QTabWidget>

namespace Ui {
	class dialog;
}

class Panel;
class Applet;

class LookAndFeelWidget : public QTabWidget {
	Q_OBJECT

public:
	LookAndFeelWidget(Panel* panel, QWidget *parent = 0);
	~LookAndFeelWidget();

private slots:
	void on_panel_size_valueChanged(int );

	void on_selectBackgroundBtn_clicked();

	void on_removeAppletBtn_clicked();

	void on_addAppletBtn_clicked();

	void on_up_clicked();

	void on_down_clicked();
private:
	Ui::dialog *ui;
	Panel* _panel;

	/**
		Add an applet to the list view
	*/
	void addApplet(Applet* applet);
};
