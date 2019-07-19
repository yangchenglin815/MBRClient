#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include "BaseDialog.h"
#include "ui_LoginWindow.h"

class LoginWindow : public BaseDialog
{
	Q_OBJECT

public:
	LoginWindow(QWidget *parent = 0);
	~LoginWindow();

private:
	Ui::LoginWindow ui;
};

#endif // LOGINWINDOW_H
