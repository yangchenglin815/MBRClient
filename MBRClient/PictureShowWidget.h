#ifndef PICTURESHOWWIDGET_H
#define PICTURESHOWWIDGET_H

#include <QWidget>
#include "ui_PictureShowWidget.h"

class PictureShowWidget : public QWidget
{
	Q_OBJECT

public:
	PictureShowWidget(QWidget *parent = 0);
	~PictureShowWidget();

private:
	Ui::PictureShowWidget ui;
};

#endif // PICTURESHOWWIDGET_H
