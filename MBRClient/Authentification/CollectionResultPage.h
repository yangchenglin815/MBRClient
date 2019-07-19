#ifndef COLLECTIONRESULTPAGE_H
#define COLLECTIONRESULTPAGE_H

#include <QWidget>
#include "ui_CollectionResultPage.h"

class CollectionResultPage : public QWidget
{
	Q_OBJECT

public:
	CollectionResultPage(QWidget *parent = 0);
	~CollectionResultPage();

private:
	Ui::CollectionResultPage ui;
};

#endif // COLLECTIONRESULTPAGE_H
