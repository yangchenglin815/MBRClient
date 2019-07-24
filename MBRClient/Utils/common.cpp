#include "common.h"
#include <QStandardPaths>
#include <QDir>
#include <Windows.h>
#include "AEyeLog.h"

QString common::getUserDir( const QString& strName /*= "\\AthenaEye"*/ )
{
	QString strDirPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
	strDirPath += strName;

	QDir dir;
	if (!dir.exists(strDirPath))
	{
		dir.mkpath(strDirPath);
	}

	return strDirPath;
}

bool common::runAppInSingleInstanceMode( const QString& appName /*= "AthenaEye"*/ )
{
	QString strMutexName = "CLIENT_NAME";
	HANDLE singleInstanceHandle = CreateMutexA(NULL, FALSE, strMutexName.toLocal8Bit().data());
	DWORD dwError = GetLastError();
	AEyeLog::instance()->writeDebugLog(QString("[MutexName:%1 Code:%2]").arg(strMutexName).arg(dwError));


	return true;
}
