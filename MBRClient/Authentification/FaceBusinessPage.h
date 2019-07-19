#ifndef FACEBUSINESSPAGE_H
#define FACEBUSINESSPAGE_H

#include <QWidget>
#include "ui_FaceBusinessPage.h"

class FaceBusinessPage : public QWidget
{
	Q_OBJECT

public:
	FaceBusinessPage(QWidget *parent = 0);
	~FaceBusinessPage();

private:
	Ui::FaceBusinessPage ui;
};

#endif // FACEBUSINESSPAGE_H
