#ifndef TOPBARWIDGET_H
#define TOPBARWIDGET_H

#include <QWidget>
#include "ui_TopBarWidget.h"

class TopBarWidget : public QWidget
{
	Q_OBJECT

public:
	TopBarWidget(QWidget *parent = 0);
	~TopBarWidget();

private:
	Ui::TopBarWidget ui;
};

#endif // TOPBARWIDGET_H
