#include "LocalClient.h"
#include <QLocalSocket>
#include <QByteArray>
#include "DefineData.h"

LocalClient::LocalClient( const QString &strName, QObject *parent /*= 0*/ )
	: QObject(parent)
	, m_serverName(strName)
	, m_socket(NULL)
{
	m_socket = new QLocalSocket(this);
	QObject::connect(m_socket, SIGNAL(readyRead()), this, SIGNAL(readyRead()));
}

LocalClient::~LocalClient()
{
	m_socket->close();
}

int LocalClient::connect()
{
	m_socket->abort();
	m_socket->connectToServer(m_serverName);
	if (!m_socket->waitForConnected(500))
	{
		m_socket->abort();
		LOG_INFO("Connect to server error: " + QString::number(m_socket->error()));
		return m_socket->error();
	}

	return 0;
}

bool LocalClient::write( const QByteArray &data )
{
	if (m_socket->state() != QLocalSocket::ConnectedState)
	{
		LOG_INFO("Client write error: " + QString::number(m_socket->state()));
		return false;
	}

	m_socket->write(data);
	return m_socket->waitForBytesWritten(3000);
}

bool LocalClient::read( QByteArray &out )
{
	if (m_socket->state() != QLocalSocket::ConnectedState)
	    return false;

	if (m_socket->bytesAvailable() < (int)sizeof(quint16))
	{
		m_socket->waitForReadyRead(3000);
	}

	out = m_socket->readAll();
	return out.isEmpty() ? false : true;
}
