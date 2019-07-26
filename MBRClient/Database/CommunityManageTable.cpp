#include "CommunityManageTable.h"
#include "DataModel.h"
#include "DefineData.h"
#include "EnumData.h"

CommunityManageTable::CommunityManageTable(QObject *parent)
	: DbBaseTable(parent)
	, m_sTableName("T_MBRADDINFOR")
{

}

CommunityManageTable::~CommunityManageTable()
{

}

bool CommunityManageTable::getCommunityManage( QString& json, int key, int type )
{
    m_pReadWriteLock->lockForRead();
	bool bRet = false;

	//全民参保
	QString strSql = QString("SELECT ADDINFOR FROM %1  where  MBRUSERCODE = %2 and ADDTYPE = %3;")
		.arg(m_sTableName)
		.arg(key)
		.arg(type);

	DBRows tempDataList;
	DBHELPER->doSql(strSql, &tempDataList);
	DBRows::iterator marIter = tempDataList.begin();
	for(;marIter != tempDataList.end(); marIter++) 
	{
		DBRow* pTemp = *marIter;
		DBHELPER->getString(*pTemp, 1, json);
		delete pTemp;
		pTemp = NULL;
		bRet = true;
	}

	m_pReadWriteLock->unlock();
	return bRet;
}

bool CommunityManageTable::getCommunityManage( QString& json, QString userName, QString userIdentify , int type )
{
	m_pReadWriteLock->lockForRead();
	bool bRet = false;

	//全民参保
	QString strSql = QString("SELECT ADDINFOR FROM %1  where  USERNAME = '%2' and USERIDENTIFY = '%3' and ADDTYPE = %4;")
		.arg(m_sTableName)
		.arg(userName)
		.arg(userIdentify)
		.arg(type);

	DBRows tempDataList;
	DBHELPER->doSql(strSql, &tempDataList);
	DBRows::iterator marIter = tempDataList.begin();
	for(;marIter != tempDataList.end(); marIter++) 
	{
		DBRow* pTemp = *marIter;
		DBHELPER->getString(*pTemp, 1, json);
		delete pTemp;
		pTemp = NULL;
		bRet = true;
	}

	m_pReadWriteLock->unlock();
	return bRet;
}
