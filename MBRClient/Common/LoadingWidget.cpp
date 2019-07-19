#include "LoadingWidget.h"
#include <QSplashScreen>
#include <QDateTime>
#include <QTimer>

LoadingWidget* LoadingWidget::getInstance() 
{
	static LoadingWidget instance;
	return &instance;
}

LoadingWidget::LoadingWidget() 
{
	m_splashScreen = new(std::nothrow) QSplashScreen;
}

LoadingWidget::~LoadingWidget() 
{
}

void LoadingWidget::setLoadingSurf(int iType) 
{
	switch(iType) { 
    case AEyeSplash_Starting:
        m_strPixmap = "../Resources/img/loading/L1";
        break;
	case AEyeSplash_MBRLoding:
		m_strPixmap = "../Resources/img/loading/L2";
		break;		
	case AEyeSplash_ReadCard:
		m_strPixmap = "AEyeSplash_ReadCard.gif";
		break;
	case AEyeSplash_Update:
		m_strPixmap = "../Resources/img/loading/loadding_update.gif";
		break;
	case AEyeSplash_UpLoadData:
		m_strPixmap = "../Resources/img/loading/L3";
		break;
	case AEyeSplash_CheckDevice:
		m_strPixmap = "../Resources/img/loading/L4";
		break;
	default:
		m_strPixmap = "AEyeSplash_default.gif";
		break;
	}

    m_splashScreen->setPixmap(QPixmap::fromImage(QImage(m_strPixmap)));
    m_splashScreen->show();
	m_splashScreen->repaint();
}

void LoadingWidget::showLoadingMessage(QString message, QColor color, Qt::Alignment alignment)
{
	m_splashScreen->showMessage(message, alignment, color); 
}

void LoadingWidget::endLoading(QWidget* widget, int iSecond) 
{
	QDateTime nTimeBegin = QDateTime::currentDateTime();
	QDateTime nTimeNow;
	do 
	{
		nTimeNow = QDateTime::currentDateTime();
		m_splashScreen->repaint();
	} 
	while(nTimeBegin.secsTo(nTimeNow) <= iSecond);
	
	m_splashScreen->finish(widget);
}
