#include "RegisterDataTable.h"
#include "DataModel.h"
#include "DefineData.h"
#include "EnumData.h"

RegisterDataTable::RegisterDataTable(QObject *parent)
	: DbBaseTable(parent)
	, m_sTableName("T_MBRRegister")
{

}

RegisterDataTable::~RegisterDataTable()
{

}

bool RegisterDataTable::UpdateRegisterData( int state )
{
	m_pReadWriteLock->lockForWrite();

	bool bRet = false;
	QString strSql = QString("update %1 set REGISTERFLAG = %2 where ID = 1")
		.arg(m_sTableName)
		.arg(state); 

	if(DBHELPER->doSql(strSql))
	{
		bRet = true;
	}

	m_pReadWriteLock->unlock();
	return bRet;
}

int RegisterDataTable::getRegisterFlag( QString mac )
{
	m_pReadWriteLock->lockForRead();

	int iFlag = 0;
	QString strSql = QString("select RegisterFlag from %1 where MachineCode = '%2';")
		.arg(m_sTableName)
		.arg(mac); 

	DBRows tempDataList;

	DBHELPER->doSql(strSql, &tempDataList);
	DBRows::iterator marIter = tempDataList.begin();
	for(;marIter != tempDataList.end(); marIter++) 
	{
		DBRow* pTemp = *marIter;
		DBHELPER->getInt(*pTemp, 1, iFlag);
		delete pTemp;
		pTemp = NULL;
	}

	switch(iFlag) 
	{
	case Register_NotRegistered:
		LOG_SQL(QStringLiteral("未注册"));
		break;        
	case Register_Registered:

		LOG_SQL(QStringLiteral("已注册"));
		break;
	case  Register_Forbidden:
		LOG_SQL(QStringLiteral("注册码已禁用"));
		break;
	case  Register_TimeOut:
		LOG_SQL(QStringLiteral("过期"));
		break;
	case  Register_WillTimeOut:
		LOG_SQL(QStringLiteral("即将过期"));
		break;
	default:
		LOG_SQL(QStringLiteral("未知注册标识"));
		break;
	}

	m_pReadWriteLock->unlock();
	return iFlag;
}

bool RegisterDataTable::insertData( QString machineCode, int registerStatus )
{
	m_pReadWriteLock->lockForWrite();

	QString sqlStatement = QString("insert into %1 (ID, MACHINECODE, REGISTERFLAG)VALUES (1, '%2', '%3');")
		.arg(m_sTableName)
		.arg(machineCode)
		.arg(registerStatus); 

	m_pReadWriteLock->unlock();
	return DBHELPER->doSql(sqlStatement);
}

bool RegisterDataTable::deleteData()
{
	m_pReadWriteLock->lockForWrite();

	QString sqlStatement = QString("delete from %1;").arg(m_sTableName); 

	m_pReadWriteLock->unlock();
	return DBHELPER->doSql(sqlStatement);
}
