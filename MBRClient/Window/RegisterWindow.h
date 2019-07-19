#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QWidget>
#include "BaseDialog.h"
#include "ui_RegisterWindow.h"

class RegisterWindow : public BaseDialog
{
	Q_OBJECT

public:
	RegisterWindow(QWidget *parent = 0);
	~RegisterWindow();

private:
	Ui::RegisterWindow ui;
};

#endif // REGISTERWINDOW_H
