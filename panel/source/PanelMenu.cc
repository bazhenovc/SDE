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
#include <PanelMenu.hh>

#include <QMouseEvent>
#include <IconWidget.hh>

#include <QHBoxLayout>

#include <QPushButton>

const int kMenuSize = 100;

PanelMenu::PanelMenu(Panel *panel)
	: QWidget(0, Qt::FramelessWindowHint), _panel(panel) {
	resize(panel->width(), kMenuSize);
	//move(panel->pos());
	move(panel->pos().x(), panel->height());
	setPalette(panel->palette());
	connect(this, SIGNAL(clicked()), this, SLOT(hide()));

	QHBoxLayout* l = new QHBoxLayout(this);
#if 0
	l->setSpacing(4);
	l->setContentsMargins(1, 1, 1, 1);
#endif
	l->setAlignment(Qt::AlignCenter);
	// Create widgets
	{
		IconWidget* settings = new IconWidget("/usr/share/sde/data/settings.png",
											  tr("Settings"),
											  this);
		connect(settings, SIGNAL(clicked()), _panel, SLOT(showSettings()));
		connect(settings, SIGNAL(clicked()), this, SLOT(hide()));
		l->addWidget(settings);

		IconWidget* keyboard = new IconWidget("/usr/share/sde/data/keyboard.png",
											  tr("Keyboard"),
											  this);
		connect(keyboard, SIGNAL(clicked()), this, SLOT(hide()));
		l->addWidget(keyboard);

		IconWidget* windows = new IconWidget("/usr/share/sde/data/winlist.png",
											 tr("Window list"),
											 this);
		connect(windows, SIGNAL(clicked()), this, SLOT(hide()));
		l->addWidget(windows);

		IconWidget* quit = new IconWidget("/usr/share/sde/data/close.png",
										   tr("Quit"),
										   this);
		connect(quit, SIGNAL(clicked()), _panel, SLOT(doQuit()));
		l->addWidget(quit);
	}
	setLayout(l);
}

PanelMenu::~PanelMenu() {}

void PanelMenu::mouseReleaseEvent(QMouseEvent *e) {
	if (e->button() == Qt::LeftButton)
		emit clicked();
}
