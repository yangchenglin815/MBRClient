#include "HelpPage.h"
#include <QNetworkProxyFactory>
#include <QDir>

HelpPage::HelpPage(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	QNetworkProxyFactory::setUseSystemConfiguration(true);
	
	QString appPath = QDir::currentPath();
	QString htmlUrl = appPath + "\\Resources\\manual\\index.html";
	ui.webView->load(QUrl::fromLocalFile(htmlUrl));
}

HelpPage::~HelpPage()
{

}
