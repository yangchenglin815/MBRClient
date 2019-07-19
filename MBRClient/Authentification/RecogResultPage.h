#ifndef RECOGRESULTPAGE_H
#define RECOGRESULTPAGE_H

#include <QWidget>
#include "ui_RecogResultPage.h"

class RecogResultPage : public QWidget
{
	Q_OBJECT

public:
	RecogResultPage(QWidget *parent = 0);
	~RecogResultPage();

private:
	Ui::RecogResultPage ui;
};

#endif // RECOGRESULTPAGE_H
