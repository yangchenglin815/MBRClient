#include "AppManager.h"
#include "SingleProcessHelper.h"
#include "MBRClient.h"

#include <QtWidgets/QApplication>
#include <QTextCodec>
#include <QTranslator>
#include <QStyleFactory>
#include <QWidget>
#include <QMessageBox>

extern const QString SERVERNAME_MBR = "MBR_CLIENT";

class MySPH : public SingleProcessHelper {
	QWidget *m_Win;
public:
	MySPH(const QString &strName, QObject *parent = 0) : SingleProcessHelper(strName, "MBRClient", parent) {
		m_Win = NULL;
	}

	void setWin(QWidget *w) {
		m_Win = w;
	}

	void handleQuitRequest() {
		if (NULL != m_Win) {
			m_Win->close();
		}
	}
};

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QApplication::setStyle(QStyleFactory::create("fusion"));
	QApplication::setFont(QFont("Microsoft YaHei")); 

	QTextCodec *codec = QTextCodec::codecForName("GB2312");
	QTextCodec::setCodecForLocale(codec);

	QTranslator translator;
	translator.load(":/qm/qt_zh_CN.qm");
	app.installTranslator(&translator);

	MySPH single(SERVERNAME_MBR);
	QString holder;
	if (single.hasRemote(holder)) {
		QMessageBox::information(NULL, "Hint", QString("%1 is running, close it before using %2").arg(holder).arg("MBRClient"));
		single.activateRemote();
		return 0;
	}
	single.takeLock();

	bool switchSystem = false;
	QString command;
	if (argc >1) 
	{
		switchSystem = true;
		command = QString::fromStdString(argv[1]);
	}

	AppManager appManager(switchSystem);
	int retCode = appManager.startup(command);
	if (0 != retCode)
	{
		return retCode;
	}

	MBRClient w;
	w.hide();

	single.setWin(&w);
	single.setActivationWindow(&w);

	return app.exec();
}
