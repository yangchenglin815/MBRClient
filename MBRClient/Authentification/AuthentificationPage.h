#ifndef AUTHENTIFICATIONPAGE_H
#define AUTHENTIFICATIONPAGE_H

#include <QWidget>
#include "ui_AuthentificationPage.h"

class AuthentificationPage : public QWidget
{
	Q_OBJECT

public:
	AuthentificationPage(QWidget *parent = 0);
	~AuthentificationPage();

private:
	Ui::AuthentificationPage ui;
};

#endif // AUTHENTIFICATIONPAGE_H
