#include "CacheVersionTable.h"
#include "DataModel.h"
#include "DefineData.h"
#include "EnumData.h"

CacheVersionTable::CacheVersionTable(QObject *parent)
	: DbBaseTable(parent)
	, m_sTableName("T_CACHEVERSION")
{

}

CacheVersionTable::~CacheVersionTable()
{

}

bool CacheVersionTable::getCacheVersions( QMap<int, int>& versionsByCode )
{
	m_pReadWriteLock->lockForRead();

	bool successed = false;
	QString sqlStatement = QString("select CACHECODE, CACHEVERSION from %1;")
		.arg(m_sTableName);

	DBRows dbRows;
	if (!DBHELPER->doSql(sqlStatement, &dbRows))
		return false;

	DBRows::iterator it = dbRows.begin();
	for(;it != dbRows.end(); it++) {
		DBRow* dbRow = *it;

		int cacheCode = -1;
		int cacheVersion = -1;

		DBHELPER->getInt(*dbRow, 1, cacheCode);
		DBHELPER->getInt(*dbRow, 2, cacheVersion);

		if (cacheCode != -1)
			versionsByCode[cacheCode] = cacheVersion;

		delete dbRow;
		successed = true;
	}

	m_pReadWriteLock->unlock();
	return successed;
}

bool CacheVersionTable::updateCacheVersion( int cacheCode, int version )
{
	m_pReadWriteLock->lockForWrite();

	QString sqlStatement = QString("UPDATE OR INSERT INTO %1 (CACHECODE, CACHEVERSION) VALUES ('%2', '%3') MATCHING (CACHECODE);")
		.arg(m_sTableName)
		.arg(cacheCode)
		.arg(version);

	bool ret = DBHELPER->doSql(sqlStatement);

	m_pReadWriteLock->unlock();
	return ret;
}
