#ifndef CREATEPERSONINFOPAGE_H
#define CREATEPERSONINFOPAGE_H

#include <QWidget>
#include "ui_CreatePersonInfoPage.h"

class CreatePersonInfoPage : public QWidget
{
	Q_OBJECT

public:
	CreatePersonInfoPage(QWidget *parent = 0);
	~CreatePersonInfoPage();

private:
	Ui::CreatePersonInfoPage ui;
};

#endif // CREATEPERSONINFOPAGE_H
