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

#include <BatteryWidget.hh>

#include <QtCore/QTimer>
#include <QtCore/QSettings>

#include <QtGui/QLabel>

#include <FileUtils.hh>

QLabel* label = 0;

BatteryWidget::BatteryWidget(QWidget *parent)
	: QLCDNumber(parent) {
	setSegmentStyle(Filled);
	setNumDigits(3);

	// Load settings
	QString path = getenv("HOME");
	path += "/.sde/panel.conf";
	QSettings settings(path, QSettings::NativeFormat);

	// Create timer
	QTimer* timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(displayInfo()));
	timer->start(settings.value("Misc/UpdateInterval", 10).toInt());

	// Get battery name
	_batteryName = settings.value("Misc/BatteryID", "BAT1").toString();
}

BatteryWidget::~BatteryWidget() {}

void BatteryWidget::displayInfo() {

	QString now = FileUtils::cat("/sys/class/power_supply/"
								 + _batteryName + "/charge_now");
	QString full = FileUtils::cat("/sys/class/power_supply/"
								  + _batteryName + "/charge_full");

	if (now == "" || full == "") {
		display("Err");
		return;
	}

	double charge_now = now.toDouble();
	double charge_full = full.toDouble();

	display((charge_now / charge_full) * 100.0);
}
