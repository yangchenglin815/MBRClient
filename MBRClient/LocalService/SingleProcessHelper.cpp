#include "SingleProcessHelper.h"
#include "LocalServer.h"
#include "LocalClient.h"
#include "DefineData.h"

#include <QByteArray>
#include <QThread>

#ifndef NO_GUI
#include <QApplication>
#include <QWidget>
#else
#include <QCoreApplication>
#endif

#ifdef _WIN32
#include <cstdlib>
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#else
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#endif

class SleeperThead : public QThread
{
public:
	static void msleep(unsigned long msecs)
	{
		QThread::msleep(msecs);
	}
};

SingleProcessHelper::SingleProcessHelper( const QString &serverName, const QString &holder /*= ""*/, QObject *parent /*= 0*/ )
	: QObject(parent)
	, m_server(NULL)
	, m_serverName(serverName)
	, m_holder(holder)
	, m_actWin(NULL)
{
	m_server = new LocalServer(m_serverName, this);
	connect(m_server, SIGNAL(newConnection()), this, SLOT(slotOnNewConnection()));

#ifdef _WIN32
	m_processId = QString::number(GetCurrentProcessId());
#else
	m_processId = QString::number(getPid());
#endif
	LOG_INFO(QString("Get current process id=<%1>, holder=<%2>").arg(m_processId).arg(m_holder));
}

SingleProcessHelper::~SingleProcessHelper()
{

}

void SingleProcessHelper::handleQuitRequest()
{
	qApp->quit();
}

bool SingleProcessHelper::takeLock()
{
	return (0 == m_server->listen()) ? true : false;
}

void SingleProcessHelper::sendArguments( const QString &strName )
{
	LocalClient client(strName);
	do 
	{
		if (0 != client.connect()) {
			break;
		}

		QStringList argList = qApp->arguments();
		QString dataStr = "ARGUMENTS";
		foreach (QString var, argList) {
			dataStr.append(",").append(var);
		}
		LOG_INFO(QString("Send arguments=<%1>").arg(dataStr));

		if (!client.write(dataStr.toLocal8Bit())) {
			break;
		}
	} while (0);
}

#ifndef NO_GUI
void SingleProcessHelper::setActivationWindow( QWidget *aw )
{
	m_actWin = aw;
}
#endif

bool SingleProcessHelper::hasRemote()
{
	QString holder;
	return hasRemote(m_serverName, holder);
}

bool SingleProcessHelper::hasRemote( QString &holder )
{
	return hasRemote(m_serverName, holder);
}

bool SingleProcessHelper::hasRemote( const QString &strName, QString &holder )
{
	LocalClient client(strName);
	do 
	{
		if (0 != client.connect()) {
		   break;
		}
		if (!client.write(QString("CHECK").toLocal8Bit())) {
		   break;
		}

		QByteArray ba;
		if (client.read(ba) && QString(ba).startsWith("CHECK_OK")) {
			QStringList lst = QString::fromLocal8Bit(ba).split(',');
			if (lst.size() == 2) {
				holder = lst[1];
			}
			return true;
		}
	} while (0);

	return false;
}

bool SingleProcessHelper::activateRemote()
{
	return activateRemote(m_serverName);
}

bool SingleProcessHelper::activateRemote( const QString &strName )
{
	LocalClient client(strName);
	do 
	{
		if (0 != client.connect()) {
			break;
		}
		if (!client.write(QString("ACTIVATE").toLocal8Bit())) {
			break;
		}

		QByteArray ba;
		if (client.read(ba) && QString(ba) == "ACTIVATE_OK") {
			return true;
		}
	} while (0);

	return false;
}

bool SingleProcessHelper::killRemote()
{
	return killRemote(m_serverName);
}

bool SingleProcessHelper::killRemote( const QString &strName )
{
	LocalClient client(strName);
	do 
	{
		if (0 != client.connect()) {
			break;
		}
		if (!client.write(QString("QUIT").toLocal8Bit())) {
			break;
		}

		QByteArray ba;
		QString holder;
		if (client.read(ba) && QString(ba) == "QUIT_OK") {
			for (int i = 0; i < 15; ++i) {
				SleeperThead::msleep(1000);
				if (!hasRemote(strName, holder)) {
					LOG_INFO(QString("Kill %1 success").arg(strName));
					return true;
				}
			}
		}
	} while (0);

	// force quit
	do 
	{
		if (0 != client.connect()) {
			break;
		}
		if (!client.write(QString("FORCEQUIT").toLocal8Bit())) {
			break;
		}

		QByteArray ba;
		QString holder;
		if (client.read(ba) && QString(ba) == "FORCEQUIT_OK") {
			for (int i = 0; i < 3; i++) {
				SleeperThead::msleep(1000);
				if (!hasRemote(strName, holder)) {
					LOG_INFO(QString("Kill %1 success").arg(strName));
					return true;
				}
			}
		}
	} while (0);

	LOG_INFO(QString("Kill %1 failure").arg(strName));
	return false;
}

void SingleProcessHelper::slotOnNewConnection()
{
	LocalServer *server = qobject_cast<LocalServer *>(sender());
	if (NULL == server) {
		return;
	}

	QByteArray out;
	if (server->read(out)) {
		LOG_INFO("Server read: " + QString::fromLocal8Bit(out));
		if (QString::fromLocal8Bit(out) == "CHECK") {
			QByteArray resp = "CHECK_OK,";
			if (!m_holder.isEmpty()) {
				resp.append(m_holder.toLocal8Bit());
			}
			else {
				resp.append(m_processId.toLocal8Bit());
			}
			server->write(resp);
		}
		else if (QString::fromLocal8Bit(out) == "ACTIVATE") {
			server->write(QString("ACTIVATE_OK").toLocal8Bit());
			activateWindow();
		}
		else if (QString::fromLocal8Bit(out) == "QUIT") {
			server->write(QString("QUIT_OK").toLocal8Bit());
			handleQuitRequest();
		}
		else if (QString::fromLocal8Bit(out) == "FORCEQUIT") {
			server->write(QString("FORCEQUIT_OK").toLocal8Bit());
			forceQuit();
		}
		else if (QString::fromLocal8Bit(out) == "ARGUMENTS") {
			QStringList list = QString::fromLocal8Bit(out).remove(0, QString("ARGUMENTS,").size()).split(",");
			emit sigOnArguments(list);
		}
	}
}

#ifndef NO_GUI
void SingleProcessHelper::activateWindow()
{
	LOG_INFO("There is already a instance running, raising it up.");
	if (m_actWin) {
		m_actWin->setWindowState(m_actWin->windowState() & ~Qt::WindowMinimized);
		m_actWin->raise();
		m_actWin->activateWindow();
	}
}
#endif

void SingleProcessHelper::forceQuit()
{
	LOG_INFO("Force quit the program.");
	ulong currentPid;

#ifdef _WIN32
	currentPid = GetCurrentProcessId();
	HANDLE currentHandle = OpenProcess(PROCESS_TERMINATE, FALSE, ulong(currentPid));
	if (currentHandle != NULL) {
		TerminateProcess(currentHandle, 0);
	}
#else
	currentPid = getpid();
	kill(currentPid, SIGKILL);
#endif
}
