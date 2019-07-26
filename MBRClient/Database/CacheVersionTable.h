#ifndef CACHEVERSIONTABLE_H
#define CACHEVERSIONTABLE_H

#include <QObject>
#include "DbBaseTable.h"
#include "ibpp.h"

class CacheVersionTable : public DbBaseTable
{
	Q_OBJECT

public:
	CacheVersionTable(QObject *parent = 0);
	~CacheVersionTable();

public:
	bool getCacheVersions(QMap<int, int>& versionsByCode);
	bool updateCacheVersion(int cacheCode, int version);

private:
	QString m_sTableName;
};

#endif // CACHEVERSIONTABLE_H
