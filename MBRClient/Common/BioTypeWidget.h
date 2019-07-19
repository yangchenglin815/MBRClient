#ifndef BIOTYPEWIDGET_H
#define BIOTYPEWIDGET_H

#include <QWidget>
#include "ui_BioTypeWidget.h"

class BioTypeWidget : public QWidget
{
	Q_OBJECT

public:
	BioTypeWidget(QWidget *parent = 0);
	~BioTypeWidget();

private:
	Ui::BioTypeWidget ui;
};

#endif // BIOTYPEWIDGET_H
