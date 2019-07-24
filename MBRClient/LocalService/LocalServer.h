#ifndef LOCALSERVER_H
#define LOCALSERVER_H

#include <QObject>

class QLocalServer;
class QLocalSocket;
class QByteArray;
class LocalServer : public QObject
{
	Q_OBJECT

public:
	explicit LocalServer(const QString &strName, QObject *parent = 0);
	~LocalServer();

	int listen();
	bool write(const QByteArray &data);
	bool read(QByteArray &out);

signals:
	void onNewConnection();

private:
	QLocalServer *m_server;
	QString m_serverName;
	QLocalSocket *m_client;
};

#endif // LOCALSERVER_H
