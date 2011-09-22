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
#include <Panel.hh>

#include <QtGui/QApplication>
#include <QtGui/QDesktopWidget>
#include <QtGui/QX11Info>
#include <QtGui/QPixmap>
#include <QtGui/QLabel>
#include <QtGui/QHBoxLayout>
#include <QtGui/QPushButton>
#include <QtCore/QSettings>
#include <QtCore/QFile>
#include <QtCore/QTextStream>

#include <QMouseEvent>

#include <LookAndFeelWidget.hh>
#include <Applet.hh>
#include <PanelWidget.hh>
#include <PanelMenu.hh>

Panel::Panel(QWidget* parent)
	: PanelWidget(0) {
	// Load setting
	QString path = getenv("HOME");
	path += "/.sde/panel.conf";
	settings = new QSettings(path, QSettings::NativeFormat);

	optBackgroundImage = settings->value("LookAndFeel/BackgroundImage",
										 "/usr/share/sde/data/panel.png").toString();

	optHeight = settings->value("Misc/Height", 40).toInt();

	// Set attributes
	setAttribute(Qt::WA_DeleteOnClose);
	setFixedHeight(optHeight);

	// Setup PanelWidget
	setStrut();
	setNetWMHints();

	// Set background image
	setBackgroundImageOpt(optBackgroundImage);

	// Create widgets
	createWidgets();
}

Panel::~Panel() {
	delete settings;
}

void Panel::setBackgroundImageOpt(const QString &path) {
	QPalette pal;

#if 0
	// Cropped pixmap
	QImage img(path);
	img = img.copy(0, 0, width(), height());
#endif
	QImage img(path);
	// Set background
	pal.setBrush(backgroundRole(), img.scaled(size()));
	setPalette(pal);
	// Store in the config file
	settings->setValue("LookAndFeel/BackgroundImage", path);
	settings->sync();
}

void Panel::setHeightOpt(int height) {
	optHeight = height;
	setFixedHeight(optHeight);
	setStrut();
	settings->setValue("Misc/Height", optHeight);
	settings->sync();
}

Applet* Panel::loadApplet(const QString &file) {
	Applet* applet = new Applet(file);
	addApplet(applet);
	_applets.push_back(applet);
	return applet;
}

void Panel::addApplet(Applet *applet) {
	if (!applet->broken()) {
		if (applet->caps() == AC_Panel) {
			QWidget* widget = applet->getWidget(this);
			layout->addWidget(widget);
		}
	}
}

void Panel::removeApplet(const QString &name) {
	// This is ugly
	for (QLinkedList<Applet*>::iterator itr = _applets.begin();
		 itr != _applets.end(); ++itr) {
		if ((*itr)->name() == name) {
			QWidget* widget = (*itr)->getWidget(this);
			layout->removeWidget(widget);
			delete widget;
			itr = _applets.erase(itr);
			break;
		}
	}
}

void Panel::dumpApplets() {
	QString path(getenv("HOME"));
	path += "/.sde/panel-applets";

	QFile file(path);
	file.open(QFile::Truncate | QFile::ReadWrite);
	if (file.isOpen()) {
		QTextStream stream(&file);
		for (QLinkedList<Applet*>::iterator itr = _applets.begin();
			 itr != _applets.end(); ++itr) {
			if (!(*itr)->broken())
				stream << (*itr)->fileName() <<  " ";
		}
		stream << "\n";
		file.close();
	}
}

void Panel::removeAll() {
	for (QLinkedList<Applet*>::iterator itr = _applets.begin();
		 itr != _applets.end();
		 ++itr) {
		delete (*itr);
	}
	_applets.clear();
}

void Panel::showConfigDialog() {
	LookAndFeelWidget* widget = new LookAndFeelWidget(this);
	widget->show();
}

void Panel::showSettings() {
	LookAndFeelWidget* widget = new LookAndFeelWidget(this);
	widget->show();
}

void Panel::doQuit() {
	removeAll();
	exit(0);
}

void Panel::createWidgets() {
	// Create menu
	menu = new PanelMenu(this);
	connect(this, SIGNAL(clicked()), menu, SLOT(show()));
	// Create layout
	layout = new QHBoxLayout;
	layout->setContentsMargins(1, 1, 1, 1);
	layout->setAlignment(Qt::AlignLeft);
	setLayout(layout);

	loadDefaultApplets();
}

void Panel::loadDefaultApplets() {
	QString path(getenv("HOME"));
	path += "/.sde/panel-applets";

	QFile file(path);
	file.open(QFile::ReadOnly);

	if (!file.isOpen())
		return;

	QTextStream stream(&file);

	while (!stream.atEnd()) {
		QString applet;
		stream >> applet;
		if (applet != "") // Filter '\n' & co
			(void)loadApplet(applet);
	}

	file.close();
}

void Panel::mouseReleaseEvent(QMouseEvent *e) {
	if (e->button() == Qt::LeftButton) {
		emit clicked();
	}
}
