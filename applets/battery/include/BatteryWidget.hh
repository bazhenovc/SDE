/**
	SDE applets
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

#include <QtGui/QLCDNumber>

/**
	This widget displays battery charge status. It relies on
	/sys/class/power_supply/BAT{0-N}/charge_full and
	/sys/class/power_supply/BAT{0-N}/charge_now
*/
class BatteryWidget : public QLCDNumber {
	Q_OBJECT
public:

	/**
		Constructor
	*/
	BatteryWidget(QWidget* parent = 0);

	/**
		Destructor
	*/
	~BatteryWidget();

private:

	/// Battery name
	QString _batteryName;

private slots:

	void displayInfo();
};
