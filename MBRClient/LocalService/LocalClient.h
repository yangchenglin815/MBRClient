#ifndef LOCALCLIENT_H
#define LOCALCLIENT_H

#include <QObject>

class QLocalSocket;
class QByteArray;
class LocalClient : public QObject
{
	Q_OBJECT

public:
	explicit LocalClient(const QString &strName, QObject *parent = 0);
	~LocalClient();

	int connect();
	bool write(const QByteArray &data);
	bool read(QByteArray &out);

signals:
	void readyRead();

private:
	QLocalSocket *m_socket;
	QString m_serverName;
};

#endif // LOCALCLIENT_H
