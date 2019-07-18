#ifndef MBRCLIENT_H
#define MBRCLIENT_H

#include <QtWidgets/QMainWindow>
#include "ui_MBRClient.h"

class MBRClient : public QMainWindow
{
	Q_OBJECT

public:
	MBRClient(QWidget *parent = 0);
	~MBRClient();

private:
	Ui::MBRClientClass ui;
};

#endif // MBRCLIENT_H
