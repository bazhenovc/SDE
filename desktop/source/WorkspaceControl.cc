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

#include <WorkspaceControl.hh>
#include <Workspace.hh>

#include <QtDBus/QDBusConnection>

#include <stdio.h>

WorkspaceControl::WorkspaceControl(QObject *parent)
	: QObject(parent) {
	if (!QDBusConnection::sessionBus().isConnected()) {
		fprintf(stderr, "Cannot connect to the D-Bus session");
		return;
	}

	if (!QDBusConnection::sessionBus().registerService("org.sde.WorkspaceControl")) {
		fprintf(stderr, "Cannot register service");
		return;
	}

	QDBusConnection::sessionBus().registerObject("/", this,
												 QDBusConnection::ExportAllSlots);
}

void WorkspaceControl::setWallpaper(const QString &arg) {
	_workspace->setWallpaperOpt(arg);
}

void WorkspaceControl::addApplet(const QString &arg) {
	_workspace->loadApplet(arg);
}

void WorkspaceControl::removeApplet(const QString &arg) {
	_workspace->removeApplet(arg);
}

void WorkspaceControl::dumpApplets() {
	_workspace->dumpApplets();
}
