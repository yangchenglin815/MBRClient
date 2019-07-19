#include "InfoQueryPage.h"

InfoQueryPage::InfoQueryPage(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.wgt_right->setCurrentIndex(2);
}

InfoQueryPage::~InfoQueryPage()
{

}
