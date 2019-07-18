#include "MBRClient.h"
#include "FramelessHelper.h"

MBRClient::MBRClient(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_TranslucentBackground, true);
	setWindowFlags(Qt::FramelessWindowHint);
	ui.stackedWidget->setCurrentIndex(2);

	FramelessHelper *helper = new FramelessHelper;
	helper->activateOn(this);
	helper->setDbClickOn(false);
	helper->setWidgetResizable(false);
}

MBRClient::~MBRClient()
{

}
