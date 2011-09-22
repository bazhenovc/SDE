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

#include <MainWindow.hh>
#include "ui_MainWindow.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QScrollArea>

#include <WidgetPushButton.hh>

#include <DesktopMenu.hh>

WidgetPushButton::WidgetPushButton(QWidget *parent, QWidget *data)
	: QPushButton(parent), _data(data) {
	connect(this, SIGNAL(clicked2(QWidget*)), MainWindow::instance, SLOT(pageSwitch(QWidget*)));
	setFixedHeight(64);
}

WidgetPushButton::WidgetPushButton(const QString &text, QWidget *parent, QWidget *data)
	: QPushButton(text, parent), _data(data) {
	connect(this, SIGNAL(clicked2(QWidget*)), MainWindow::instance, SLOT(pageSwitch(QWidget*)));
	setFixedHeight(64);
}

MainWindow* MainWindow::instance = 0;

MainWindow::MainWindow(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::MainWindow) {
	ui->setupUi(this);
	ui->okBtn->setFixedHeight(64);

	MainWindow::instance = this;
	createWidgets();
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::on_okBtn_clicked() {
	close();
}

void MainWindow::pageSwitch(QWidget *w) {
	QWidget* old = ui->scrollArea->takeWidget();
	old->setParent(this);
	old->hide();
	ui->scrollArea->setWidget(w);
	w->show();
}

void MainWindow::createWidgets() {
	// Main menu
	{
		// Create main widget
		mainMenu = new QWidget(ui->scrollArea);
		QLayout* l = new QVBoxLayout(mainMenu);
		l->setAlignment(Qt::AlignTop);
		mainMenu->setLayout(l);

		desktopMenu = new DesktopMenu(this, mainMenu);

		// Add nested widgets
		WidgetPushButton* toDesktop = new WidgetPushButton(tr("Desktop settings"), mainMenu, desktopMenu);
		l->addWidget(toDesktop);

		QPushButton* toNetwork = new QPushButton(tr("Network settings"), mainMenu);
		l->addWidget(toNetwork);

		QPushButton* toRegional = new QPushButton(tr("Language settings"), mainMenu);
		l->addWidget(toRegional);

		QPushButton* toDateTime = new QPushButton(tr("Date and time"), mainMenu);
		l->addWidget(toDateTime);
	}
	ui->scrollArea->setWidget(mainMenu);
	mainMenu->show();
}
