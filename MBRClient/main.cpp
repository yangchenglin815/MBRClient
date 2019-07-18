#include "MBRClient.h"
#include <QtWidgets/QApplication>
#include <QTextCodec>
#include <QTranslator>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QApplication::setStyle(QStyleFactory::create("fusion"));
	QApplication::setFont(QFont("Microsoft YaHei")); 

	QTextCodec *codec = QTextCodec::codecForName("GB2312");
	QTextCodec::setCodecForLocale(codec);

	MBRClient w;
	w.show();
	return app.exec();
}
