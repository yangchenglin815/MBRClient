#ifndef FINGERBUSINESSPAGE_H
#define FINGERBUSINESSPAGE_H

#include <QWidget>
#include "ui_FingerBusinessPage.h"

class FingerBusinessPage : public QWidget
{
	Q_OBJECT

public:
	FingerBusinessPage(QWidget *parent = 0);
	~FingerBusinessPage();

private:
	Ui::FingerBusinessPage ui;
};

#endif // FINGERBUSINESSPAGE_H
