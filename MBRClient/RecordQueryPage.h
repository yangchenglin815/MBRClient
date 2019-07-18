#ifndef RECORDQUERYPAGE_H
#define RECORDQUERYPAGE_H

#include <QWidget>
#include "ui_RecordQueryPage.h"

class RecordQueryPage : public QWidget
{
	Q_OBJECT

public:
	RecordQueryPage(QWidget *parent = 0);
	~RecordQueryPage();

private:
	Ui::RecordQueryPage ui;
};

#endif // RECORDQUERYPAGE_H
