#ifndef AEYELOG_H
#define AEYELOG_H

#include <QObject>
#include <QMutex>
#include <QString>

class AEyeLog : public QObject
{
	Q_OBJECT

public:
	static AEyeLog* instance();

	void writeDebugLog(QString sDebugLog);
	void writeErrorLog(QString sErrorLog);
	void writeSqlLog(QString sSqlLog);

private:
	AEyeLog(QObject *parent = 0);
	~AEyeLog();

	void writeMessage(QString sContent, QString sFileName);

private:
	static AEyeLog* m_pInstance;
	QString m_sCurDate;
	QMutex* m_pDebugMutex;
	QMutex* m_pErrorMutex;
	QMutex* m_pSqlMutex;
};

#endif // AEYELOG_H
