#ifndef MODIFYPASSWDPAGE_H
#define MODIFYPASSWDPAGE_H

#include <QWidget>
#include "ui_ModifyPasswdPage.h"

class ModifyPasswdPage : public QWidget
{
	Q_OBJECT

public:
	ModifyPasswdPage(QWidget *parent = 0);
	~ModifyPasswdPage();

private:
	Ui::ModifyPasswdPage ui;
};

#endif // MODIFYPASSWDPAGE_H
