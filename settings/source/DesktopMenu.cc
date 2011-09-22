/**
	SDE configuration tool
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

#include <DesktopMenu.hh>

#include <QPushButton>
#include <QVBoxLayout>
#include <WidgetPushButton.hh>
#include <QFileDialog>
#include <QSettings>
#include <QLabel>

#include <DesktopMenu/ConfigureAppletsWidget.hh>

#include <unistd.h>

DesktopMenu::DesktopMenu(QWidget *parent, QWidget *backMenu)
	: QWidget(parent) {
	// Create DBus interface
	iface = new QDBusInterface("org.sde.WorkspaceControl", "/", "",
							   QDBusConnection::sessionBus());
	if (!iface->isValid()) {
		return;
	}

	// Create subwidgets
	configureApplets = new ConfigureAppletsWidget(this, iface);
	configureApplets->hide();

	// Add nested widgets
	QLayout* l = new QVBoxLayout(this);
	l->setAlignment(Qt::AlignTop);

	WidgetPushButton* back = new WidgetPushButton(tr("Back"), this, backMenu);
	l->addWidget(back);

	QPushButton* wallpaper = new QPushButton(tr("Select wallpaper"), this);
	wallpaper->setFixedHeight(64);
	connect(wallpaper, SIGNAL(clicked()), this, SLOT(onSelectWallpaperClick()));
	l->addWidget(wallpaper);

	WidgetPushButton* applets = new WidgetPushButton(tr("Configure applets"), this, configureApplets);
	l->addWidget(applets);

	QPushButton* panel = new QPushButton(tr("Configure panel"), this);
	connect(panel, SIGNAL(clicked()), this, SLOT(onConfigurePanelClick()));
	l->addWidget(panel);

#if 0
	QPushButton* save = new QPushButton(tr("Save settings"), this);
	l->addWidget(save);
#endif
	// Hide
	hide();
}

DesktopMenu::~DesktopMenu() {}

void DesktopMenu::onSelectWallpaperClick() {
	QString path = QFileDialog::getOpenFileName(this, tr("Open image"),
												getenv("HOME"),
												tr("Image files (*.jpg *.png *.tiff *.xpm)"));
	if (path != "") {
		iface->call("setWallpaper", path);
	}
}

void DesktopMenu::onConfigureAppletsClick() {}

void DesktopMenu::onConfigurePanelClick() {}
