#include "AEyeLog.h"
#include <QDir>
#include <QDateTime>
#include <QTextStream>
#include <QIODevice>
#include <QMutexLocker>
#include "common.h"

AEyeLog* AEyeLog::m_pInstance = NULL;

AEyeLog::AEyeLog(QObject *parent)
	: QObject(parent)
{
	m_sCurDate = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");

	m_pDebugMutex = new QMutex;
	m_pErrorMutex = new QMutex;
	m_pSqlMutex = new QMutex;
}

AEyeLog::~AEyeLog()
{

}

AEyeLog* AEyeLog::instance()
{
	if (m_pInstance == NULL)
	{
		m_pInstance = new AEyeLog;
	}
	return m_pInstance;
}

void AEyeLog::writeDebugLog( QString sDebugLog )
{
	QMutexLocker locker(m_pDebugMutex);
	writeMessage(sDebugLog, m_sCurDate + "_debug_log.txt");
}

void AEyeLog::writeErrorLog( QString sErrorLog )
{
	QMutexLocker locker(m_pErrorMutex);
	writeMessage(sErrorLog, m_sCurDate + "_error_log.txt");
}

void AEyeLog::writeMessage( QString sContent, QString sFileName )
{
	QString logPath = Common::getUserDir() + "//log";
	QDir logDir;
	if (!logDir.exists(logPath))
	{
		logDir.mkpath(logPath);
	}

	QFile file(logPath + "//" + sFileName);
	QString current_datetime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
	QString message = QString("%1: %2").arg(current_datetime).arg(sContent);

	if (file.open(QIODevice::WriteOnly | QIODevice::Append))
	{
		QTextStream text_stream(&file);
		text_stream << message << "\r\n\r\n";
		file.flush();
	}
	file.close();
}

void AEyeLog::writeSqlLog( QString sSqlLog )
{
	QMutexLocker locker(m_pSqlMutex);
	writeMessage(sSqlLog, m_sCurDate + "_sql_log.txt");
}
