#include "DbBaseTable.h"
#include <QMutexLocker>

QReadWriteLock *DbBaseTable::m_pReadWriteLock = NULL;

DbBaseTable::DbBaseTable(QObject *parent)
	: QObject(parent)
{
	initLock();
}

DbBaseTable::~DbBaseTable()
{

}

void DbBaseTable::initLock()
{
	QMutexLocker locker(&m_pMutex);
	if (m_pReadWriteLock == NULL)
	{
		m_pReadWriteLock = new QReadWriteLock;
	}
}
