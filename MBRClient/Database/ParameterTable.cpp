#include "ParameterTable.h"
#include "DataModel.h"
#include "DefineData.h"
#include "EnumData.h"
#include "ParamManager.h"

ParameterTable::ParameterTable(QObject *parent)
	: DbBaseTable(parent)
	, m_sTableName("T_MBRRegister")
{

}

ParameterTable::~ParameterTable()
{

}

bool ParameterTable::updateParam( int version, const QVector<ParameterData>& params )
{
	m_pReadWriteLock->lockForWrite();

	QSet<QString> paramKeys;
	PARAMMANAGER->getNecessaryParamKeys(paramKeys);

	for (int i = 0; i < params.size(); i++) {
		if (!paramKeys.contains(params.at(i).paramName))
			continue;

		QString sqlStatement = QString("update or insert into %1 (PARAMNAME,  PARAMVALUE,  PARAMDESC, PARAMTYPE, SYSCODE) values ('%2', '%3', '%4', '%5', '%6') matching (PARAMNAME, SYSCODE);")
			.arg(m_sTableName)
			.arg(params.at(i).paramName)
			.arg(params.at(i).paramValue)
			.arg(params.at(i).paramDesc)
			.arg(params.at(i).paramType)
			.arg(params.at(i).sysCode);

		if(!DBHELPER->doSql(sqlStatement)) 
			return false;
	}
	m_pReadWriteLock->unlock();

	return DBHELPER->m_pCacheVerTable->updateCacheVersion(CacheCode_Param, version);
}

bool ParameterTable::getParam( QString key, QMap<int, QString>& valuesBySysCode )
{
	m_pReadWriteLock->lockForRead();

	bool successed = false;
	QString sqlStatement = QString("select PARAMVALUE, SYSCODE from %1 where PARAMNAME='%2';")
		.arg(m_sTableName)
		.arg(key);

	DBRows dbRows;
	if (!DBHELPER->doSql(sqlStatement, &dbRows))
		return false;

	DBRows::iterator it = dbRows.begin();
	for(;it != dbRows.end(); it++) {
		DBRow* dbRow = *it;

		QString paramValue;
		int sysCode = -1;

		DBHELPER->getString(*dbRow, 1, paramValue);
		DBHELPER->getInt(*dbRow, 2, sysCode);

		if (sysCode != -1)
			valuesBySysCode[sysCode] = paramValue;

		delete dbRow;
		successed = true;
	}

	m_pReadWriteLock->unlock();
	return successed;
}
