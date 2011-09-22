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

#include <QWidget>

//
// Ported from Qt "Screenshot" example
//

#include <QtGui/QLabel>
#include <QtGui/QMouseEvent>

class QPushButton;
class QGroupBox;
class QSpinBox;
class QCheckBox;
class QVBoxLayout;
class QGridLayout;
class QHBoxLayout;

class ClickableLabel : public QLabel
{
	Q_OBJECT
public:
	ClickableLabel(QWidget* parent) : QLabel(parent) {}
	virtual ~ClickableLabel() {}

signals:
	void clicked();

private slots:

	void onClick();

protected:

	void mouseReleaseEvent(QMouseEvent *ev) {
		if (ev->button() == Qt::LeftButton) {
			emit clicked();
		}
	}
};

class ScreenShotWidget : public QWidget {
	Q_OBJECT

public:
	ScreenShotWidget();

protected:
	void resizeEvent(QResizeEvent *event);

private slots:
	void newScreenshot();
	void saveScreenshot();
	void shootScreen();
	void updateCheckBox();

private:
	void createOptionsGroupBox();
	void createButtonsLayout();
	QPushButton *createButton(const QString &text, QWidget *receiver,
							  const char *member);
	void updateScreenshotLabel();

	QPixmap originalPixmap;

	QLabel *screenshotLabel;
	QGroupBox *optionsGroupBox;
	QSpinBox *delaySpinBox;
	QLabel *delaySpinBoxLabel;
	QCheckBox *hideThisWindowCheckBox;
	QPushButton *newScreenshotButton;
	QPushButton *saveScreenshotButton;
	QPushButton *quitScreenshotButton;

	QVBoxLayout *mainLayout;
	QGridLayout *optionsGroupBoxLayout;
	QHBoxLayout *buttonsLayout;
};
