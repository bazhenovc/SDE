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

#include <ScreenShotWidget.hh>

#include <QtGui/QPushButton>
#include <QtGui/QGroupBox>
#include <QtGui/QSpinBox>
#include <QtGui/QCheckBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QApplication>
#include <QtGui/QFileDialog>
#include <QtGui/QDesktopWidget>
#include <QtCore/QTimer>
#include <QtCore/QDir>

void ClickableLabel::onClick() {
	ScreenShotWidget* widget = new ScreenShotWidget;
	widget->show();
}

ScreenShotWidget::ScreenShotWidget() {
	screenshotLabel = new QLabel;
	screenshotLabel->setSizePolicy(QSizePolicy::Expanding,
								   QSizePolicy::Expanding);
	screenshotLabel->setAlignment(Qt::AlignCenter);
	screenshotLabel->setMinimumSize(240, 160);

	createOptionsGroupBox();
	createButtonsLayout();

	mainLayout = new QVBoxLayout;
	mainLayout->addWidget(screenshotLabel);
	mainLayout->addWidget(optionsGroupBox);
	mainLayout->addLayout(buttonsLayout);
	setLayout(mainLayout);

	shootScreen();
	delaySpinBox->setValue(5);

	setWindowTitle(tr("Screenshot"));
	resize(300, 200);
}

void ScreenShotWidget::resizeEvent(QResizeEvent * /* event */) {
	QSize scaledSize = originalPixmap.size();
	scaledSize.scale(screenshotLabel->size(), Qt::KeepAspectRatio);
	if (!screenshotLabel->pixmap()
			|| scaledSize != screenshotLabel->pixmap()->size())
		updateScreenshotLabel();
}

void ScreenShotWidget::newScreenshot() {
	if (hideThisWindowCheckBox->isChecked())
		hide();
	newScreenshotButton->setDisabled(true);

	QTimer::singleShot(delaySpinBox->value() * 1000, this, SLOT(shootScreen()));
}

void ScreenShotWidget::saveScreenshot() {
	QString format = "png";
	QString initialPath = QDir::currentPath() + tr("/untitled.") + format;

	QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
													initialPath,
													tr("%1 Files (*.%2);;All Files (*)")
													.arg(format.toUpper())
													.arg(format));
	if (!fileName.isEmpty())
		originalPixmap.save(fileName, format.toAscii());
}

void ScreenShotWidget::shootScreen() {
	if (delaySpinBox->value() != 0)
		qApp->beep();
	originalPixmap = QPixmap::grabWindow(QApplication::desktop()->winId());
	updateScreenshotLabel();

	newScreenshotButton->setDisabled(false);
	if (hideThisWindowCheckBox->isChecked())
		show();
}

void ScreenShotWidget::updateCheckBox() {
	if (delaySpinBox->value() == 0)
		hideThisWindowCheckBox->setDisabled(true);
	else
		hideThisWindowCheckBox->setDisabled(false);
}

void ScreenShotWidget::createOptionsGroupBox() {
	optionsGroupBox = new QGroupBox(tr("Options"));

	delaySpinBox = new QSpinBox;
	delaySpinBox->setSuffix(tr(" s"));
	delaySpinBox->setMaximum(60);
	connect(delaySpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateCheckBox()));

	delaySpinBoxLabel = new QLabel(tr("Screenshot Delay:"));

	hideThisWindowCheckBox = new QCheckBox(tr("Hide This Window"));

	optionsGroupBoxLayout = new QGridLayout;
	optionsGroupBoxLayout->addWidget(delaySpinBoxLabel, 0, 0);
	optionsGroupBoxLayout->addWidget(delaySpinBox, 0, 1);
	optionsGroupBoxLayout->addWidget(hideThisWindowCheckBox, 1, 0, 1, 2);
	optionsGroupBox->setLayout(optionsGroupBoxLayout);
}

void ScreenShotWidget::createButtonsLayout() {
	newScreenshotButton = createButton(tr("New Screenshot"),
									   this, SLOT(newScreenshot()));

	saveScreenshotButton = createButton(tr("Save Screenshot"),
										this, SLOT(saveScreenshot()));

	quitScreenshotButton = createButton(tr("Quit"), this, SLOT(close()));

	buttonsLayout = new QHBoxLayout;
	buttonsLayout->addStretch();
	buttonsLayout->addWidget(newScreenshotButton);
	buttonsLayout->addWidget(saveScreenshotButton);
	buttonsLayout->addWidget(quitScreenshotButton);
}

QPushButton *ScreenShotWidget::createButton(const QString &text, QWidget *receiver,
									  const char *member) {
	QPushButton *button = new QPushButton(text);
	button->connect(button, SIGNAL(clicked()), receiver, member);
	return button;
}

void ScreenShotWidget::updateScreenshotLabel() {
	screenshotLabel->setPixmap(originalPixmap.scaled(screenshotLabel->size(),
													 Qt::KeepAspectRatio,
													 Qt::SmoothTransformation));
}

