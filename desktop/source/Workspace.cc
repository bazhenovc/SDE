/**
	SDE desktop
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

#include <Workspace.hh>

#include <QtCore/QSettings>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtGui/QDesktopWidget>
#include <QtGui/QApplication>

#include <QProcess>

#include <IconWidget.hh>
#include <Applet.hh>
#include <PanelWidget.hh>

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <QX11Info>
#include <NetWM.hh>


Workspace::Workspace() {
	resize(QApplication::desktop()->size());

	// Set paths
	desktopSettingsFile = getenv("HOME");
	desktopSettingsFile += "/.sde/desktop.conf";

	appletsFile = getenv("HOME");
	appletsFile += "/.sde/desktop-applets";

	// Load settings
	reloadSettings();

	// Create widgets
	createWidgets();
}

Workspace::~Workspace() {}

Applet* Workspace::loadApplet(const QString &filename) {
	Applet* applet = findAppletByFileName(filename);
	if (applet == 0) {
		applet = new Applet(filename);
		if (!applet->broken()) {
			//Desktop::addApplet(applet);
			QWidget* widget = applet->getWidget(this);
			widget->show();
			_applets.push_back(applet);
		} else {
			delete applet;
			applet = 0;
		}
	}
	return applet;
}

void Workspace::removeApplet(const QString &aname) {
	// This is ugly
	for (QList<Applet*>::iterator itr = _applets.begin();
		 itr != _applets.end(); ++itr) {
		if ((*itr)->fileName() == aname) {
			QWidget* widget = (*itr)->getWidget(this);
			delete widget;
			itr = _applets.erase(itr);
			break;
		}
	}
}

void Workspace::removeAllApplets() {
	for (QList<Applet*>::iterator itr = _applets.begin();
		 itr != _applets.end();
		 ++itr) {
		delete (*itr);
	}
	_applets.clear();
}

void Workspace::dumpApplets() {
	QFile file(appletsFile);
	file.open(QFile::Truncate | QFile::ReadWrite);
	if (file.isOpen()) {
		QTextStream stream(&file);
		for (QList<Applet*>::iterator itr = _applets.begin();
			 itr != _applets.end(); ++itr) {
			if (!(*itr)->broken())
				stream << (*itr)->fileName() <<  " ";
		}
		stream << "\n";
		file.close();
	}
}

void Workspace::loadApplets() {
//	removeAllApplets();

	QFile file(appletsFile);
	file.open(QFile::ReadOnly);

	if (!file.isOpen())
		return;

	QTextStream stream(&file);

	while (!stream.atEnd()) {
		QString applet;
		stream >> applet;
		if (applet != "") // Filter '\n' & co
			loadApplet(applet);
	}

	file.close();
}

void Workspace::reloadSettings() {
	QSettings settings(desktopSettingsFile, QSettings::NativeFormat);

	// Get wallpaper
	QString path = settings.value("LookAndFeel/Wallpaper").toString();
	if (path != "") {
		QPalette pal;
		pal.setBrush(backgroundRole(), QBrush(QImage(path).scaled(size())));
		setPalette(pal);
	}
}

void Workspace::setWallpaperOpt(const QString &path) {
	QSettings settings(desktopSettingsFile, QSettings::NativeFormat);

	// Get wallpaper
	settings.setValue("LookAndFeel/Wallpaper", path);

	QPalette pal;
	pal.setBrush(backgroundRole(), QBrush(QImage(path).scaled(size())));
	setPalette(pal);
}

Applet* Workspace::findApplet(const QString &name) {
	for (QList<Applet*>::iterator itr = _applets.begin();
		 itr != _applets.end(); ++itr) {
		if ((*itr)->name() == name) {
			return (*itr);
		}
	}
	return 0;
}

Applet* Workspace::findAppletByFileName(const QString &filename) {
	for (QList<Applet*>::iterator itr = _applets.begin();
		 itr != _applets.end(); ++itr) {
		if ((*itr)->fileName() == filename) {
			return (*itr);
		}
	}
	return 0;
}

void Workspace::createWidgets() {
	IconWidget* appsButton = new IconWidget("/usr/share/sde/data/apps.png",
											tr("Apps"),
											this);
	appsButton->move(QApplication::desktop()->width() - appsButton->width() - 1,
					 QApplication::desktop()->height() - appsButton->height() - 1);
	appsButton->show();
	connect(appsButton, SIGNAL(clicked()), this, SLOT(onAppsBtnClick()));

	IconWidget* systemButton = new IconWidget("/usr/share/sde/data/system.png",
											  tr("System"),
											  this);
	systemButton->move(1, QApplication::desktop()->height()
					   - systemButton->height() - 1);
	systemButton->show();
	connect(systemButton, SIGNAL(clicked()), this, SLOT(onSystemBtnClick()));

	NetWM::init(QX11Info::display());

	Atom atoms[2];

	atoms[0] = NetWM::NET_WM_WINDOW_TYPE_DESKTOP;
	atoms[1] = 0xffffffff;

	XChangeProperty(QX11Info::display(), winId(),
					NetWM::NET_WM_WINDOW_TYPE, XA_ATOM,
					32, PropModeReplace, (unsigned char *)atoms, 2);
}

void Workspace::onAppsBtnClick() {
	static QProcess process;
	if (process.state() != QProcess::Running || process.state() != QProcess::Starting) {
		process.start("sde-appview");
	}
}

void Workspace::onSystemBtnClick() {
	static QProcess process;
	if (process.state() != QProcess::Running || process.state() != QProcess::Starting) {
		process.start("sde-settings");
	}
}
