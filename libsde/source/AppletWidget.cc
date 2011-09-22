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

#include <AppletWidget.hh>
#include <QSettings>
#include <QString>
#include <QApplication>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QFile>
#include <QTimer>

#include <unistd.h>

/// TODO: implement it
QString buildFilePath(const QString& name) {
	QString ret = getenv("HOME");
	ret += "/.sde/applets";
	ret += name;
	//ret += "/";
	//while (QFile::exists(ret)) {
	//	ret += "0";
	//}
	return ret;
}

AppletWidget::AppletWidget(QWidget *parent, const QString &name)
	: QWidget(parent), _dragging(false) {

	// Create settings
	QString path = buildFilePath(name);
	_settings = new QSettings(path,
							  QSettings::NativeFormat, this);

	// Center
	const QRect kNullGeometry(100, 100, 100, 100);
	QRect newGeometry = _settings->value("Misc/Geometry", kNullGeometry).toRect();
	setGeometry(newGeometry);
}

AppletWidget::~AppletWidget() {}

void AppletWidget::mousePressEvent(QMouseEvent *e) {
	if (e->button() == Qt::LeftButton) {
		if (!_dragging) {
			_dragPoint = e->pos();
			_oldSize = size();
			resize(size().width() + 10,
				   size().height() + 10);
			_dragging = true;
		}
	} else {
		///
	}
}

void AppletWidget::mouseReleaseEvent(QMouseEvent *) {
	if (_dragging) {
		_dragging = false;
		resize(_oldSize);
		_settings->setValue("Misc/Geometry", geometry());
		_settings->sync();
	}
}

void AppletWidget::mouseMoveEvent(QMouseEvent *e) {
	if (_dragging)
		move(e->globalPos() - _dragPoint);
}
