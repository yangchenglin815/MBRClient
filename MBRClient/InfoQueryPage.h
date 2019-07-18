#ifndef INFOQUERYPAGE_H
#define INFOQUERYPAGE_H

#include <QWidget>
#include "ui_InfoQueryPage.h"

class InfoQueryPage : public QWidget
{
	Q_OBJECT

public:
	InfoQueryPage(QWidget *parent = 0);
	~InfoQueryPage();

private:
	Ui::InfoQueryPage ui;
};

#endif // INFOQUERYPAGE_H
