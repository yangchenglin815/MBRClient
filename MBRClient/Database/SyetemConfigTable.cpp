#include "SyetemConfigTable.h"
#include "DataModel.h"
#include "DefineData.h"

SyetemConfigTable::SyetemConfigTable(QObject *parent)
	: DbBaseTable(parent)
	, m_sTableName("T_MBRSYSTEMCONFIG")
{

}

SyetemConfigTable::~SyetemConfigTable()
{

}

bool SyetemConfigTable::setServerConfig( QString sUrl, QString sUpdateIP )
{
	m_pReadWriteLock->lockForWrite();

	bool bRet = false;
	QString strSql;
	if (isSysConfigExist())
	{
		strSql = QString("update %1 set SERVERURL = '%2' , UPDATESERVER = '%3' where ID = 1;")
			.arg(m_sTableName)
			.arg(sUrl)
			.arg(sUpdateIP); 

		if(DBHELPER->doSql(strSql)) 
		{
			bRet = true;
		}
	}
	else
	{
		strSql = QString("insert into %1 (ID,  SERVERURL, UPDATEFLAG, UPDATESERVER)VALUES (1, '%2', 2, '%3');")
			.arg(m_sTableName)
			.arg(sUrl)
			.arg(sUpdateIP); 

		if(DBHELPER->doSql(strSql)) 
		{
			bRet = true;
		}
	}

	getLocalContral();
	m_pReadWriteLock->unlock();
	return true;
}

bool SyetemConfigTable::getUpdateServerData( QString &sData )
{
	m_pReadWriteLock->lockForRead();

	bool bRet = false;
	int iFlag = 0;
	QString strSql = QString("select  UPDATESERVER from %1 where ID = 1;")
		.arg(m_sTableName); 

	DBRows tempDataList;
	DBHELPER->doSql(strSql, &tempDataList);
	DBRows::iterator marIter = tempDataList.begin();
	for(;marIter != tempDataList.end(); marIter++) 
	{
		DBRow* pTemp = *marIter;
		DBHELPER->getString(*pTemp, 1, sData);

		bRet = true;
		delete pTemp;
		pTemp = NULL;
	}

	m_pReadWriteLock->unlock();
	return bRet;
}

bool SyetemConfigTable::getLocalContral()
{
	m_pReadWriteLock->lockForRead();

	int iFlag = -1;
	bool bRet = false;
	QString strSql = QString("select * from %1 where ID = 1;")
		.arg(m_sTableName);

	DBRows tempDataList;
	stDbData stConfigData;
	DBHELPER->doSql(strSql, &tempDataList);
	DBRows::iterator marIter = tempDataList.begin();
	for(; marIter != tempDataList.end(); marIter++) 
	{
		DBRow* pTemp = *marIter;
		DBHELPER->getInt(*pTemp, 2, iFlag);
		if(1 == iFlag) 
		{
			stConfigData.registered = true;
		} 
		else  
		{
			stConfigData.registered = false;
		}

		DBHELPER->getString(*pTemp, 6, stConfigData.serverUrl);
		delete pTemp;
		pTemp = NULL;
		bRet = true;
	}

	DataModel::instance()->setConfigData(stConfigData);
	m_pReadWriteLock->unlock();
	return bRet;
}

bool SyetemConfigTable::isSysConfigExist()
{
	m_pReadWriteLock->lockForRead();

	bool bRet = false;
	QString strSql = QString("select * from %1 where ID = 1;")
		.arg(m_sTableName);

	DBRows tempDataList;
	DBHELPER->doSql(strSql, &tempDataList);
	DBRows::iterator marIter = tempDataList.begin();
	for(;marIter != tempDataList.end(); marIter++)
	{
		DBRow* pTemp = *marIter;

		delete pTemp;
		pTemp = NULL;
		bRet = true;
	}

	m_pReadWriteLock->unlock();
	return bRet;
}
