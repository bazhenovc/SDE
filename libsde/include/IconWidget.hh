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

#include <QtGui/QAbstractButton>
#include <QtGui/QPixmap>
#include <QtGui/QResizeEvent>
#include <QtCore/QString>

class QLabel;

/**
	Icon widget contains application icon and text label.
	It has clicked() signal and basically it can act as a generic button
*/
class IconWidget : public QAbstractButton {
	Q_OBJECT
public:

	/**
		Constructor
		@brief
		This creates a icon widget from given pixmap and text
	*/
	IconWidget(const QPixmap& pixmap, const QString& text,
			   QWidget* parent = 0, int labelOffset = 12);

	/**
		Constructor
		@brief
		This creates a icon widget from given pixmap file and text
	*/
	IconWidget(const QString& pixmap, const QString& text, QWidget* parent = 0,
			   int labelOffset = 12);

	/**
		Set text
	*/
	void setText(const QString &text);

	/**
		Get text
	*/
	QString text() const;

private:
	/// Icon pixmap
	QPixmap _pixmap;

	/// Text
	QLabel* _text;

protected:
	/**
		Override paint event
	*/
	virtual void paintEvent(QPaintEvent *e);

private:

	void createWidgets(const QString& text, int labelOffset);
};
