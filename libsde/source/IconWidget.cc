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
#include <IconWidget.hh>

#include <QtGui/QLabel>
#include <QtGui/QPainter>
#include <QtGui/QVBoxLayout>

IconWidget::IconWidget(const QPixmap &pixmap, const QString &text,
					   QWidget *parent, int labelOffset)
	: QAbstractButton(parent), _pixmap(pixmap) {

	createWidgets(text, labelOffset);
}

IconWidget::IconWidget(const QString &pixmap, const QString &text,
					   QWidget *parent, int labelOffset)
	: QAbstractButton(parent) {

	// Set pixmap
	_pixmap = QPixmap(pixmap);

	createWidgets(text, labelOffset);
}

void IconWidget::setText(const QString &text) {
	_text->setText(text);
}

QString IconWidget::text() const {
	return _text->text();
}

void IconWidget::paintEvent(QPaintEvent *e) {
	QPainter painter(this);
	painter.drawPixmap(0, 0, _pixmap);
}

void IconWidget::createWidgets(const QString& text, int labelOffset) {
	setFixedSize(_pixmap.size().width(), _pixmap.size().height() + labelOffset);

	// Create text label
	_text = new QLabel(this);
	_text->setGeometry(geometry());
	_text->setText(text);
	_text->setAlignment(Qt::AlignBottom | Qt::AlignCenter);
	_text->setWordWrap(true);

	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
#if 0
	setAttribute(Qt::WA_StyledBackground);
	setAttribute(Qt::WA_TranslucentBackground);
	setStyleSheet("background: transparent;");
#endif
}
