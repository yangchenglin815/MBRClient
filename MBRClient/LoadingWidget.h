#ifndef __AEYESPLASH_H__
#define __AEYESPLASH_H__

#include <QObject>
#include <QColor>

#define LOADINGWIDGET LoadingWidget::getInstance()

enum {
    AEyeSplash_Starting = 0,
	AEyeSplash_MBRLoding,
	AEyeSplash_ReadCard,
	AEyeSplash_Update,
	AEyeSplash_UpLoadData,
	AEyeSplash_CheckDevice,
};

class QTimer;
class QSplashScreen;
class LoadingWidget : public QObject {
	Q_OBJECT
	
public:
	static LoadingWidget* getInstance();
	~LoadingWidget();
	
	void setLoadingSurf(int iType);
	void showLoadingMessage(QString strMessage, QColor color = Qt::white, Qt::Alignment alignment = Qt::AlignRight | Qt::AlignTop);
	void endLoading(QWidget*, int iSecond = 0);
	
private:
	LoadingWidget();
	LoadingWidget(const LoadingWidget&);
	LoadingWidget& operator= (const LoadingWidget&);
	
private:
	QSplashScreen* m_splashScreen;
	QString m_strPixmap;
};

#endif // !__AEYESPLASH_H__
