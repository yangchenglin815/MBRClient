#ifndef VEINBUSINESSPAGE_H
#define VEINBUSINESSPAGE_H

#include <QWidget>
#include "ui_VeinBusinessPage.h"

class VeinBusinessPage : public QWidget
{
	Q_OBJECT

public:
	VeinBusinessPage(QWidget *parent = 0);
	~VeinBusinessPage();

private:
	Ui::VeinBusinessPage ui;
};

#endif // VEINBUSINESSPAGE_H
