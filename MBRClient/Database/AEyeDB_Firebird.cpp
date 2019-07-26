#include "AEyeDB_Firebird.h"
#include <cassert>
#include "GlobalSignal.h"
#include "DefineData.h"

AEyeDB_Firebird* AEyeDB_Firebird::m_pInstance = NULL;

AEyeDB_Firebird::AEyeDB_Firebird() : m_connectSuccessed(false)
	, m_database(NULL)
{
	m_pBusinessRecordTable = new BusinessRecordTable;
	m_pSystemConfigTable = new SyetemConfigTable;
	m_pCacheVerTable = new CacheVersionTable;
	m_pCommunityManageTable = new CommunityManageTable;
	m_pParameterTable = new ParameterTable;
	m_pRegisterDataTable = new RegisterDataTable;
	m_pDictionaryTable = new DictionaryTable;
	initDatabase();
}

AEyeDB_Firebird::~AEyeDB_Firebird()
{
	closeDatabase();
}

bool AEyeDB_Firebird::openDatabase( const QString& dbName /*= "MBRClient.fdb" */, const QString& userName /*= "SYSDBA"*/, const QString& userPassword /*= "masterkey"*/ )
{
	if (m_connectSuccessed)
	{
		return true;
	}

	bool successed = false;
	try
	{
		m_database = IBPP::DatabaseFactory("", dbName.toStdString(), userName.toStdString(), userPassword.toStdString());
		if (m_database != NULL)
		{
			m_database->Connect();

			m_transaction = IBPP::TransactionFactory(m_database);
			m_transaction->Start();

			LOG_SQL(QStringLiteral("连接本地数据库成功。"));
			successed = true;
			m_connectSuccessed = true;
		}
	}
	catch (IBPP::SQLException& ex)
	{
		LOG_SQL(QString(ex.what()));
		closeDatabase();
	}
	catch (IBPP::LogicException& ex2)
	{
		LOG_SQL(QString(ex2.what()));
	}
	catch (...)
	{
		LOG_SQL("catch ...");
	}

	return successed;
}

bool AEyeDB_Firebird::closeDatabase()
{
	bool successed = false;
	try
	{
		if (m_database != nullptr)
		{
			m_database->Disconnect();
			m_database = NULL;

			LOG_SQL(QStringLiteral("关闭本地数据库成功。"));
			successed = true;
			m_connectSuccessed = false;
		}
	}
	catch (IBPP::SQLException& ex)
	{
		LOG_SQL(QString(ex.what()));
		if (m_transaction != nullptr)
		{
			rollBack();
		}
	}
	catch (IBPP::LogicException& ex2)
	{
		LOG_SQL(QString(ex2.what()));
	}
	catch (...)
	{
		LOG_SQL("catch ...");
	}

	return successed;
}

bool AEyeDB_Firebird::ddoSql( const QString& sqlStatement )
{
	if (!isDatabaseConnected())
	{
		return false;
	}

	bool successed = true;
	LOG_SQL(sqlStatement);

	try
	{
		performTransaction();

		IBPP::Statement statement = IBPP::StatementFactory(m_database, m_transaction);
		statement->Prepare(sqlStatement.toStdString());
		statement->Execute();

		commitTransaction();
	}
	catch (IBPP::SQLException& ex)
	{
		LOG_SQL(QString(ex.what()));
		rollBack();
		successed = false;
	}
	catch (IBPP::LogicException& ex2)
	{
		LOG_SQL(QString(ex2.what()));
		rollBack();
	}
	catch (...)
	{
		LOG_SQL("catch ...");
		rollBack();
	}

	return successed;
}

bool AEyeDB_Firebird::doSql( const QString& sqlStatement, DBRows* rows /*= NULL*/ )
{
	if(!isDatabaseConnected()) 
	{
		return false;
	}

	QMutexLocker locker(&m_mutex);	
	if(NULL == rows)
	{
		return ddoSql(sqlStatement);
	}

	bool successed = true;

	try 
	{
		performTransaction();

		IBPP::Statement statement = IBPP::StatementFactory(m_database, m_transaction);
		statement->Prepare(sqlStatement.toStdString());
		statement->Execute(sqlStatement.toStdString());

		DBRow row;
		while(statement->Fetch(row)) 
		{
			DBRow* tempRow = new DBRow();
			tempRow->operator = (row);
			rows->push_back(tempRow);
		}
	} 
	catch (IBPP::SQLException& ex) 
	{
		successed = false;
		LOG_SQL(QString(ex.what()));
	}
	catch (IBPP::LogicException& ex2)
	{
		LOG_SQL(QString(ex2.what()));
	} 
	catch(...) 
	{
		LOG_SQL("catch ...");
	}

	return successed;
}

bool AEyeDB_Firebird::writeBlob( const QString& sqlStatement, const char* blobBuf, int blobSize )
{
	if(!isDatabaseConnected() || !isDataValid(blobSize)) 
	{
		return false;
	}

	QMutexLocker locker(&m_mutex);
	bool successed = true;
	LOG_SQL(sqlStatement);

	try 
	{
		performTransaction();

		IBPP::Statement statement = IBPP::StatementFactory(m_database, m_transaction);

		statement->Prepare(sqlStatement.toStdString());
		assert(1 == statement->Parameters());

		IBPP::Blob blob = IBPP::BlobFactory(m_database, m_transaction);
		blob->Create();
		blob->Write(blobBuf, blobSize);
		blob->Close();

		statement->Set(1, blob);
		statement->Execute();

		commitTransaction();
	} 
	catch (IBPP::SQLException& ex) 
	{
		successed = false;
		LOG_SQL(QString(ex.what()));
	} 
	catch (IBPP::LogicException& ex2) 
	{
		LOG_SQL(QString(ex2.what()));
	} 
	catch(...) 
	{
		LOG_SQL("catch ...");
	}

	return successed;

}

bool AEyeDB_Firebird::getBlob( const DBRow& row, int index, char** blobBuf, int& blobSize )
{
	assert(isDatabaseConnected());
	bool successed = false;

	try 
	{
		IBPP::Blob blob = IBPP::BlobFactory(m_database, m_transaction);
		successed = row->Get(index, blob);
		blob->Open();
		blob->Info(&blobSize, NULL, NULL);

		if(blobSize > 0)
		{
			char* buf = new char[blobSize + 1];
			memset(buf, 0, blobSize + 1);

			blob->Read(buf, blobSize);
			blob->Close();
			if(!successed) 
			{
				successed = true;
				*blobBuf = buf;
			}
		}
		else
		{
			successed = true;
		}		
	} 
	catch(IBPP::SQLException& e) 
	{
		LOG_SQL(QString(e.what()));
	} 
	catch (IBPP::LogicException& ex2) 
	{
		LOG_SQL(QString(ex2.what()));
	} 
	catch(...) 
	{
		LOG_SQL("catch ...");
	}

	return successed;
}

bool AEyeDB_Firebird::getInt( const DBRow& row, int index, int& result )
{
	assert(isDatabaseConnected());

	QMutexLocker locker(&m_mutex);
	bool successed = false;

	try 
	{
		successed = row->Get(index, result);
	} 
	catch(IBPP::SQLException& e) 
	{
		successed = false;
		LOG_SQL(QString(e.what()));
	} 
	catch (IBPP::LogicException& ex2) 
	{
		LOG_SQL(QString(ex2.what()));
	} 
	catch(...) 
	{
		LOG_SQL("catch ...");
	}

	return successed;
}

bool AEyeDB_Firebird::getString( const DBRow& row, int index, QString& result )
{
	assert(isDatabaseConnected());

	QMutexLocker locker(&m_mutex);
	bool successed = true;

	try
	{
		std::string temp;
		row->Get(index, temp);
		result = temp.c_str();
	} 
	catch(IBPP::SQLException& e)
	{
		successed = false;
		LOG_SQL(QString(e.what()));
		rollBack();
	} 
	catch (IBPP::LogicException& ex2)
	{
		LOG_SQL(QString(ex2.what()));
		rollBack();
	} 
	catch(...) 
	{
		LOG_SQL("catch ...");
		rollBack();
	}

	return successed;
}

bool AEyeDB_Firebird::getBlobString( const DBRow& row, int index, QString& result )
{
	assert(isDatabaseConnected());

	QMutexLocker locker(&m_mutex);
	bool successed = false;

	char* buf;    
	int bufSize;
	if(getBlob(row, index, &buf, bufSize)) 
	{
		if(bufSize > 0)
		{
			result = buf;
			delete[] buf;
		}
		successed = true;
	}

	return successed;
}

bool AEyeDB_Firebird::getLong( const DBRow& row, int index, long& result )
{
	assert(isDatabaseConnected());

	QMutexLocker locker(&m_mutex);
	bool successed = false;

	int temp = 0;
	try {
		successed = row->Get(index, temp);
		result = temp;
	} 
	catch(IBPP::SQLException& e) 
	{
		successed = false;
		LOG_SQL(QString(e.what()));
	} 
	catch (IBPP::LogicException& ex2) 
	{
		LOG_SQL(QString(ex2.what()));
	} 
	catch(...) 
	{
		LOG_SQL("catch ...");
	}

	return successed;
}

bool AEyeDB_Firebird::getDouble( const DBRow& row, int index, double& result )
{
	assert(isDatabaseConnected());

	QMutexLocker locker(&m_mutex);
	bool successed = false;

	float temp;
	try 
	{
		successed = row->Get(index, temp);
		result = temp;
	} 
	catch(IBPP::SQLException& e)
	{
		successed = false;
		LOG_SQL(QString(e.what()));
	} 
	catch (IBPP::LogicException& ex2) 
	{
		LOG_SQL(QString(ex2.what()));
	} 
	catch(...) 
	{
		LOG_SQL("catch ...");
	}

	return successed;
}

void AEyeDB_Firebird::startTransaction( void )
{
    m_transaction->Start();
}

bool AEyeDB_Firebird::isTransactionStarted( void )
{
	return m_transaction->Started();
}

void AEyeDB_Firebird::performTransaction()
{
	if(isTransactionStarted()) 
	{
		commitTransaction();
		startTransaction();
	}
	else 
	{
		startTransaction();
	}
}

void AEyeDB_Firebird::commitTransaction( void )
{
	m_transaction->Commit();
}

void AEyeDB_Firebird::rollBack( void )
{
	m_transaction->RollbackRetain();
}

bool AEyeDB_Firebird::isDataValid( int datalen )
{
	bool isValid = datalen > DATA_MAXLENGTH;
	if(!isValid)
	{
		LOG_SQL(QStringLiteral("字段长度：%1 超过最大限制：%2").arg(datalen).arg(DATA_MAXLENGTH));
	}

	return isValid;
}

bool AEyeDB_Firebird::isDatabaseConnected()
{
	if (!m_connectSuccessed) 
	{
		LOG_SQL(QStringLiteral("数据库文件未打开"));
	}

	return m_connectSuccessed;
}

void AEyeDB_Firebird::initDatabase()
{
	if (!openDatabase())
	{
		emit GlobalSignal::instance()->sigOnOpenDatabaseFailed();
	}
}

AEyeDB_Firebird* AEyeDB_Firebird::instance()
{
	if (m_pInstance == NULL)
	{
		m_pInstance = new AEyeDB_Firebird;
	}
	return m_pInstance;
}

