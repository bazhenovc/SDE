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

#include <DesktopMenu/ConfigureAppletsWidget.hh>
#include "ui_ConfigureAppletsWidget.h"

#include <WidgetPushButton.hh>
#include <Applet.hh>
#include <QLayout>

#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QListWidgetItem>

ConfigureAppletsWidget::ConfigureAppletsWidget(QWidget *parent,
											   QDBusInterface *aiface)
	: QWidget(parent),
	ui(new Ui::ConfigureAppletsWidget),
	  iface(aiface) {
	ui->setupUi(this);

	WidgetPushButton* back = new WidgetPushButton(tr("Back"), this, parent);
	layout()->addWidget(back);

	QString appletsFile = getenv("HOME");
	appletsFile += "/.sde/desktop-applets";

	// Fill applets lists
	QDir dir("/usr/share/sde/applets/");

	if (!dir.exists()) {
		// Lookup another possible directory
		dir = QDir("/usr/local/share/sde/applets/");
	}

	QStringList nameFilters;
	nameFilters.push_back("*.so");
	QStringList list = dir.entryList(nameFilters);

	for (QStringList::const_iterator itr = list.begin();
		 itr != list.end(); ++itr) {

		Applet applet(dir.absoluteFilePath(*itr));
		if (!applet.broken()) {
			QListWidgetItem* item = new QListWidgetItem;
			item->setText(applet.name());
			item->setData(Qt::UserRole, applet.fileName());
			ui->avaibleApplets->addItem(item);
		}
	}

	// List currently used applets
	QFile file(appletsFile);
	file.open(QFile::ReadOnly);

	if (!file.isOpen())
		return;

	QTextStream stream(&file);

	while (!stream.atEnd()) {
		QString applet;
		stream >> applet;
		if (applet != "") // Filter '\n' & co
		{
			Applet applet_(applet);
			if (!applet_.broken()) {
				QListWidgetItem* item = new QListWidgetItem;
				item->setText(applet_.name());
				item->setData(Qt::UserRole, applet_.fileName());
				ui->addedApplets->addItem(item);
			}
		}
	}

	file.close();
}

ConfigureAppletsWidget::~ConfigureAppletsWidget() {
	delete ui;
}

void ConfigureAppletsWidget::on_add_clicked() {
	if (ui->avaibleApplets->currentItem()) {
		QString path = ui->avaibleApplets->currentItem()->data(Qt::UserRole).toString();
		QListWidgetItem* item = ui->avaibleApplets->currentItem()->clone();
		ui->addedApplets->addItem(item);
		iface->call("addApplet", path);
		iface->call("dumpApplets");
	}
}

void ConfigureAppletsWidget::on_remove_clicked() {
	if (ui->addedApplets->currentItem()) {
		QString path = ui->addedApplets->currentItem()->data(Qt::UserRole).toString();
		delete ui->addedApplets->currentItem();
		iface->call("removeApplet", path);
		iface->call("dumpApplets");
	}
}
