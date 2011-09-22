/**
	SDE PicView
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

#include <PicView.hh>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QScrollArea>
#include <QLabel>
#include <QDir>
#include <QFileDialog>

PicView::PicView(QWidget *parent)
	: QWidget(parent) {

	createWidgets();
	_currPath = QDir::currentPath();
}

void PicView::open() {
	QString fileName = QFileDialog::getOpenFileName(this,
													tr("Select image"),
													_currPath);
	if (!fileName.isEmpty()) {
		//_currPath = QDir::filePath(fileName);
		QPixmap pix(fileName);
		if (!pix.isNull()) {
			_imageLabel->setPixmap(pix);
			_imageLabel->resize(pix.size());
		}
	}
}

void PicView::zoomIn() {}

void PicView::zoomOut() {}

void PicView::normalSize() {}

void PicView::createWidgets() {
	QLayout* l = new QVBoxLayout(this);
	l->setAlignment(Qt::AlignCenter);

	_scrollArea = new QScrollArea(this);
	l->addWidget(_scrollArea);

	_imageLabel = new QLabel(_scrollArea);
	_scrollArea->setWidget(_imageLabel);

	QWidget* buttons = new QWidget(this);
	{
		buttons->setLayout(new QHBoxLayout);

		QPushButton* btn = new QPushButton(buttons);
		btn->setText(tr("Open"));
		btn->setFixedHeight(64);
		connect(btn, SIGNAL(clicked()), this, SLOT(open()));
		buttons->layout()->addWidget(btn);

		btn = new QPushButton(buttons);
		btn->setText(tr("Next"));
		btn->setFixedHeight(64);
		//connect(btn, SIGNAL(clicked()), this,
		buttons->layout()->addWidget(btn);

		btn = new QPushButton(buttons);
		btn->setText(tr("Prev"));
		btn->setFixedHeight(64);
		//connect(btn, SIGNAL(clicked()), this,
		buttons->layout()->addWidget(btn);

		btn = new QPushButton(buttons);
		btn->setText(tr("Quit"));
		btn->setFixedHeight(64);
		connect(btn, SIGNAL(clicked()), this, SLOT(close()));
		buttons->layout()->addWidget(btn);
	}
	l->addWidget(buttons);
}

void PicView::scaleImageBy(float factor) {
#if 0
	if (!_imageLabel->pixmap())
		return;

	_scaleFactor *= factor;
	_imageLabel->resize(_scaleFactor * _imageLabel->pixmap()->size());

#endif
}
