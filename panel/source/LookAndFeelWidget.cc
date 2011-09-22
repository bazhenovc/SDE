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
#include <LookAndFeelWidget.hh>
#include "ui_LookAndFeelWidget.h"

#include <QtGui/QFileDialog>
#include <QtGui/QMessageBox>

#include <QtCore/QString>
#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QtCore/QTextStream>

#include <Panel.hh>
#include <Applet.hh>

#include <unistd.h>

LookAndFeelWidget::LookAndFeelWidget(Panel* panel, QWidget *parent) :
	QTabWidget(parent),
	ui(new Ui::dialog),
	_panel(panel) {
	ui->setupUi(this);

	// List all possible applets
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

	// Add applets to the list
	for (QLinkedList<Applet*>::const_iterator itr = _panel->applets().begin();
		 itr != _panel->applets().end(); ++itr) {
		addApplet(*itr);
	}
}

LookAndFeelWidget::~LookAndFeelWidget() {
	delete ui;
}

void LookAndFeelWidget::on_panel_size_valueChanged(int value) {
	_panel->setHeightOpt(value);
}

void LookAndFeelWidget::on_selectBackgroundBtn_clicked() {
	QString path = QFileDialog::getOpenFileName(this, tr("Open image"),
												getenv("HOME"),
												tr("Image files (*.jpg *.png *.tiff *.xpm)"));
	if (path != "")
		_panel->setBackgroundImageOpt(path);
}


void LookAndFeelWidget::on_removeAppletBtn_clicked() {
	if (ui->appletList->currentItem()) {
		_panel->removeApplet(ui->appletList->currentItem()->text());
		_panel->dumpApplets();
		//ui->appletList->removeItemWidget(ui->appletList->currentItem());
		delete ui->appletList->currentItem();
	}
}

void LookAndFeelWidget::on_addAppletBtn_clicked() {
	if (ui->avaibleApplets->currentItem()) {
		QString path = ui->avaibleApplets->currentItem()->data(Qt::UserRole).toString();
		if (path != "") {
			Applet* applet = _panel->loadApplet(path);
			if (applet->broken() || (applet->caps() != AC_Panel)) {

				// Ugly nested if
				if (applet->broken())
					QMessageBox::information(this, tr("Broken applet"),
											 tr("The applet you tried to load is broken"),
											 QMessageBox::Ok);
				else
					QMessageBox::information(this, tr("Invalid applet"),
											 tr("This applet cannot be placed here"),
											 QMessageBox::Ok);
			} else {
				addApplet(applet);

				// Append to the file
				QString path(getenv("HOME"));
				path += "/.sde/panel-applets";

				QFile file(path);
				file.open(QFile::Append);
				if (file.isOpen()) {
					QTextStream stream(&file);
					stream << applet->fileName() << " ";
					file.close();
				}
			}
		}
	}
}

void LookAndFeelWidget::addApplet(Applet *applet) {
	QListWidgetItem* item = new QListWidgetItem;
	item->setText(applet->name());
	item->setData(Qt::UserRole, applet->fileName());
	ui->appletList->addItem(item);
}

void LookAndFeelWidget::on_up_clicked() {
	if (ui->appletList->currentItem()) {
		QModelIndex index = ui->appletList->currentIndex();
		if (index.row() == 0) {
			return;
		}

		QListWidgetItem* current = ui->appletList->currentItem();
		QListWidgetItem* newItem = new QListWidgetItem();
		newItem->setText(current->text());
		newItem->setData(Qt::UserRole, current->data(Qt::UserRole));
		ui->appletList->insertItem(index.row() - 1, newItem);
		delete current;

		_panel->removeAll();

		QListWidgetItem *item;
		int row = 0;
		while ((item = ui->appletList->item(row))) {
			++row;
			_panel->loadApplet(item->data(Qt::UserRole).toString());
		}

		_panel->dumpApplets();

		ui->appletList->setCurrentRow(index.row() - 1);
	}
}

void LookAndFeelWidget::on_down_clicked() {
	if (ui->appletList->currentItem()) {
		QModelIndex index = ui->appletList->currentIndex();
		if (index.row() == ui->appletList->count())
			return;

		QListWidgetItem* current = ui->appletList->currentItem();
		QListWidgetItem* newItem = new QListWidgetItem();
		newItem->setText(current->text());
		newItem->setData(Qt::UserRole, current->data(Qt::UserRole));
		ui->appletList->insertItem(index.row() + 2, newItem);
		delete current;

		_panel->removeAll();

		QListWidgetItem *item;
		int row = 0;
		while ((item = ui->appletList->item(row))) {
			++row;
			_panel->loadApplet(item->data(Qt::UserRole).toString());
		}

		_panel->dumpApplets();

		ui->appletList->setCurrentRow(index.row() + 1);
	}
}
