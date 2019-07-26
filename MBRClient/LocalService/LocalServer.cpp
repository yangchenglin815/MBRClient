#include "LocalServer.h"
#include <QLocalServer>
#include <QLocalSocket>
#include <QByteArray>
#include "DefineData.h"

LocalServer::LocalServer( const QString &strName, QObject *parent /*= 0*/ )
	: QObject(parent)
	, m_serverName(strName)
	, m_server(NULL)
	, m_client(NULL)
{
	m_server = new QLocalServer(this);
	QObject::connect(m_server, SIGNAL(newConnection()), this, SIGNAL(onNewConnection()));
}

LocalServer::~LocalServer()
{
	m_server->close();
}

int LocalServer::listen()
{
	m_server->removeServer(m_serverName);
	if (!m_server->listen(m_serverName))
	{
		LOG_INFO("Server listen error: " + m_server->errorString());
		return m_server->serverError();
	}
	return 0;
}

bool LocalServer::write( const QByteArray &data )
{
	if (m_client == NULL)
	{
		return false;
	}

	m_client->write(data);
	return m_client->waitForBytesWritten(3000);
}

bool LocalServer::read( QByteArray &out )
{
	m_client = m_server->nextPendingConnection();
	if (m_client == NULL)
	{
		return false;
	}

	if (m_client->bytesAvailable() < (int)sizeof(quint16))
	{
		m_client->waitForReadyRead(3000);
	}

	out = m_client->readAll();
	return out.isEmpty() ? false : true;
}
