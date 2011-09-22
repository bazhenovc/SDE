/**
	SDE configuration tool
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

#include <QPushButton>
#include <QMouseEvent>

class MainWindow;

class WidgetPushButton : public QPushButton {
	Q_OBJECT
public:

	// Defined in source/MainWindow.cc
	WidgetPushButton(QWidget* parent, QWidget* data);

	// Defined in source/MainWindow.cc
	WidgetPushButton(const QString& text, QWidget* parent, QWidget* data);

signals:

	void clicked2(QWidget*);

private:
	QWidget* _data;

protected:

	void mouseReleaseEvent(QMouseEvent *e) {
		if (e->button() == Qt::LeftButton)
			emit clicked2(_data);
	}
};
