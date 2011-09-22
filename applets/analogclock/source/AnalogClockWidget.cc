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

#include <AnalogClockWidget.hh>

#include <QTime>
#include <QTimer>
#include <QPainter>
#include <QSettings>

AnalogClockWidget::AnalogClockWidget(QWidget *parent)
	: AppletWidget(parent, "AnalogClock") {
	QTimer* timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	timer->start(100);

	// Set background
	const QString path = "/usr/share/sde/data/clock.png";
	_pix = QPixmap(path);
	resize(_pix.size());

	// Restore geometry
	static const QRect kNullGeom = QRect(-1, -1, -1, -1);
	QRect geom = settings()->value("Misc/Geometry", kNullGeom).toRect();
	if (geom != kNullGeom)
		setGeometry(geom);
	else {
		settings()->setValue("Misc/Geometry", geometry());
		settings()->sync();
	}
}

void AnalogClockWidget::paintEvent(QPaintEvent *e) {
	AppletWidget::paintEvent(e);
	QPainter painter(this);

	static const QPoint hourHand[3] = {
		QPoint(7, 8),
		QPoint(-7, 8),
		QPoint(0, -40)
	};
	static const QPoint minuteHand[3] = {
		QPoint(7, 8),
		QPoint(-7, 8),
		QPoint(0, -70)
	};
	static const QPoint secondHand[3] = {
		QPoint(7, 8),
		QPoint(-7, 8),
		QPoint(0, -90)
	};

	QColor hourColor(127, 127, 127);
	QColor minuteColor(127, 127, 127);
	QColor secondColor(127, 127, 127);

	int side = qMin(width(), height());
	QTime time = QTime::currentTime();

	painter.drawPixmap(0, 0, width(), height(), _pix);

	painter.setRenderHint(QPainter::Antialiasing);
	painter.translate(width() / 2, height() / 2);
	painter.scale(side / 200.0, side / 200.0);

	// Seconds
	painter.setPen(Qt::SolidLine);
	painter.setBrush(secondColor);

	painter.save();
	painter.rotate(time.second() * 6);
	painter.drawConvexPolygon(secondHand, 3);
	painter.restore();

	// Minutes
	painter.setPen(Qt::SolidLine);
	painter.setBrush(minuteColor);

	painter.save();
	painter.rotate(6.0 * (time.minute() + time.second() / 60.0));
	painter.drawConvexPolygon(minuteHand, 3);
	painter.restore();

	// Hours
	painter.setPen(Qt::SolidLine);
	painter.setBrush(hourColor);

	painter.save();
	painter.rotate(30.0 * ((time.hour() + time.minute() / 60.0)));
	painter.drawConvexPolygon(hourHand, 3);
	painter.restore();

	painter.save();
	painter.drawEllipse(-side / 26, -side / 26, side / 13, side / 13);
	painter.restore();

	painter.setPen(minuteColor);
}
