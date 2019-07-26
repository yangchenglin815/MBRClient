#include "DictionaryTable.h"
#include "DataModel.h"
#include "DefineData.h"
#include "EnumData.h"
#include "DictionaryManager.h"

DictionaryTable::DictionaryTable(QObject *parent)
	: DbBaseTable(parent)
	, m_sTableName("T_DICTIONARY")
{

}

DictionaryTable::~DictionaryTable()
{

}

bool DictionaryTable::updateDict( int version, const QVector<DictionaryData>& dicts )
{
	m_pReadWriteLock->lockForWrite();

	QString sqlStatement = QString("delete from %1;").arg(m_sTableName); 
	if(!DBHELPER->doSql(sqlStatement)) 
		return false;

	QSet<QString> dictKeys;
	DICTIONARYMANAGER->getNecessaryDictKeys(dictKeys);

	for (int i = 0; i < dicts.size(); i++) {
		if (!dictKeys.contains(dicts.at(i).fieldName))
			continue;

		sqlStatement = QString("insert into %1 (DICTNAME, FIELDNAME, FIELDNOTE, FIELDVALUE, VALUENOTE) values ('%2', '%3', '%4', '%5', '%6');")
			.arg(m_sTableName)
			.arg(dicts.at(i).dictName)
			.arg(dicts.at(i).fieldName)
			.arg(dicts.at(i).fieldNote)
			.arg(dicts.at(i).fieldValue)
			.arg(dicts.at(i).valueNote);

		if(!DBHELPER->doSql(sqlStatement)) 
			return false;
	}

	m_pReadWriteLock->unlock();
	return DBHELPER->m_pCacheVerTable->updateCacheVersion(CacheCode_Dict, version);
}

bool DictionaryTable::getDict( QString key, QMap<QString, QString>& notesByValue )
{
	m_pReadWriteLock->lockForRead();

	bool successed = false;
	QString sqlStatement = QString("select FIELDVALUE, VALUENOTE from %1 where FIELDNAME='%2';")
		.arg(m_sTableName)
		.arg(key);

	DBRows dbRows;
	if (!DBHELPER->doSql(sqlStatement, &dbRows))
		return false;

	DBRows::iterator it = dbRows.begin();
	for(;it != dbRows.end(); it++) {
		DBRow* dbRow = *it;

		QString fieldValue;
		QString valueNote;

		DBHELPER->getString(*dbRow, 1, fieldValue);
		DBHELPER->getString(*dbRow, 2, valueNote);

		if (!fieldValue.isEmpty())
			notesByValue[fieldValue] = valueNote;

		delete dbRow;
		successed = true;
	}

	m_pReadWriteLock->unlock();
	return successed;
}
