#ifndef MODELINFOQUERYPAGE_H
#define MODELINFOQUERYPAGE_H

#include <QWidget>
#include "ui_ModelInfoQueryPage.h"

class ModelInfoQueryPage : public QWidget
{
	Q_OBJECT

public:
	ModelInfoQueryPage(QWidget *parent = 0);
	~ModelInfoQueryPage();

private:
	Ui::ModelInfoQueryPage ui;
};

#endif // MODELINFOQUERYPAGE_H
