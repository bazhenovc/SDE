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
#include <ClockWidget.hh>

#include <QtCore/QTime>
#include <QtCore/QTimer>

ClockWidget::ClockWidget(QWidget *parent)
	: QLCDNumber(parent) {
	// Set LCD number properties
	setSegmentStyle(Filled);
	setNumDigits(8);

	// Create timer
	QTimer* timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(displayTime()));
	timer->start(1000);

	displayTime();
}

void ClockWidget::displayTime() {
	QTime time = QTime::currentTime();
	QString text = time.toString("hh:mm:ss");
	display(text);
}
