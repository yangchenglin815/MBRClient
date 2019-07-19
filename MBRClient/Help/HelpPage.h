#ifndef HELPPAGE_H
#define HELPPAGE_H

#include <QWidget>
#include "ui_HelpPage.h"

class HelpPage : public QWidget
{
	Q_OBJECT

public:
	HelpPage(QWidget *parent = 0);
	~HelpPage();


private:
	Ui::HelpPage ui;
};

#endif // HELPPAGE_H
