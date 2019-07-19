#ifndef RECOGINFOQUERYPAGE_H
#define RECOGINFOQUERYPAGE_H

#include <QWidget>
#include "ui_RecogInfoQueryPage.h"

class RecogInfoQueryPage : public QWidget
{
	Q_OBJECT

public:
	RecogInfoQueryPage(QWidget *parent = 0);
	~RecogInfoQueryPage();

private:
	Ui::RecogInfoQueryPage ui;
};

#endif // RECOGINFOQUERYPAGE_H
