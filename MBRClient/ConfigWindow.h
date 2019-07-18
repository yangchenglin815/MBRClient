#ifndef CONFIGWINDOW_H
#define CONFIGWINDOW_H

#include <QWidget>
#include "ui_ConfigWindow.h"

class ConfigWindow : public QWidget
{
	Q_OBJECT

public:
	ConfigWindow(QWidget *parent = 0);
	~ConfigWindow();

private:
	Ui::ConfigWindow ui;
};

#endif // CONFIGWINDOW_H
