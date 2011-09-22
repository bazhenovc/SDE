/**
	SDE AppView
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

#include <AppView.hh>
#include <AppWidget.hh>

#include <QScrollArea>
#include <QVBoxLayout>
#include <QPushButton>

#include <QDir>
#include <QSettings>

AppView::AppView(QWidget *parent)
	: QWidget(parent) {

	createWidgets();
}

void AppView::createWidgets() {
	QLayout* vbox = new QVBoxLayout;
	vbox->setSpacing(2);
	vbox->setAlignment(Qt::AlignTop);
	setLayout(vbox);

	{
		QScrollArea* sa = new QScrollArea(this);
		vbox->addWidget(sa);

		QWidget* w = new QWidget;
		QGridLayout* layout = new QGridLayout(w);
		w->setLayout(layout);

		sa->setBackgroundRole(QPalette::Dark);
		sa->setWidget(w);
		sa->setWidgetResizable(true);
		sa->setAlignment(Qt::AlignCenter);
		w->show();

		QDir dir("/usr/share/applications");
		dir.setNameFilters(QStringList("*.desktop"));

		int row = 0;
		int column = -1; //

		if (dir.exists()) {
			QStringList lst = dir.entryList(QDir::Files, QDir::NoSort);

			for (int i = 0; i < lst.size(); ++i) {
				QSettings desktopFile(dir.absoluteFilePath(lst[i]),
									  QSettings::NativeFormat);

				column ++;
				if (column == 3) {
					column = 0;
					row ++;
				}

				QString appName = desktopFile.value("Desktop Entry/Name", "NameErr").toString();
				QString iconName = desktopFile.value("Desktop Entry/Icon", "IconErr").toString();
				QString execName = desktopFile.value("Desktop Entry/Exec", "ExecErr").toString();


				appName.truncate(15);

				QPixmap pix("/usr/share/pixmaps/" + iconName);
				if (pix.isNull())
					pix = QPixmap("/usr/share/sde/data/system.png");

				AppWidget* widget = new AppWidget(w, appName,
												  pix.scaled(80, 80),
												  execName);

				connect(widget, SIGNAL(clicked()), this, SLOT(close()));
				layout->addWidget(widget, row, column);
				widget->show();
			}
		} else close();
	}

	QPushButton* btn = new QPushButton(this);
	btn->setText("Ok");
	btn->setFixedHeight(64);
	connect(btn, SIGNAL(clicked()), this, SLOT(close()));
	vbox->addWidget(btn);
}
