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
#include <SdeApplication.hh>

#include <QApplication>
#include <QSettings>
#include <QImage>
#include <QPalette>
#include <unistd.h>

void SdeApplication::init() {
	// Load application settings
	QString path = getenv("HOME");
	path += "/.sde/app.conf";

	QSettings settings(path, QSettings::NativeFormat, 0);

	// Load palette
	QImage img(settings.value("LookAndFeel/Palette",
							  "/usr/share/sde/data/black.png").toString());
	QPalette pal;
	pal.setBrush(QPalette::Window, img);
	qApp->setPalette(pal);
}
