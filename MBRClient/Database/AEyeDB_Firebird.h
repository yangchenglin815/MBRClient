#ifndef AEYEDB_FIREBIRD_H
#define AEYEDB_FIREBIRD_H

#include "ibpp.h"
#include "AEyeDB.h"
#include <QString>
#include <QMutex>
#include <QDateTime>
#include <vector>
#include <string>

typedef IBPP::Row DBRow;
typedef std::vector<DBRow*> DBRows;

class AEyeDB_Firebird :public AEyeDB
{
public:
	static AEyeDB_Firebird* instance();

private:
	AEyeDB_Firebird();
	~AEyeDB_Firebird();

public:
	bool openDatabase(const QString& dbName = "Resources/db/MBRClientSB.fdb"
		, const QString& userName = "SYSDBA", const QString& userPassword = "masterkey");
	bool closeDatabase();

	bool ddoSql(const QString& sqlStatement);           
	bool doSql(const QString& sqlStatement, DBRows* rows = NULL);

	bool writeBlob(const QString& sqlStatement, const char* blobBuf, int blobSize);
	bool getBlob(const DBRow& row, int index, char** blobBuf, int& blobSize);

	bool getInt(const DBRow& row, int index, int& result);
	bool getString(const DBRow& row, int index, QString& result);
	bool getBlobString(const DBRow& row, int index, QString& result);
	bool getLong(const DBRow& row, int index, long& result);
	bool getDouble(const DBRow& row, int index, double& result);

private:
	void startTransaction(void); 
	bool isTransactionStarted(void);
	void performTransaction();
	void commitTransaction(void); 
	void rollBack(void);
	bool isDataValid(int datalen);
	bool isDatabaseConnected();
	void initDatabase();

private:
	static AEyeDB_Firebird* m_pInstance;

	IBPP::Database m_database;          // 数据库      
	IBPP::Transaction m_transaction;      // 事物

	bool m_connectSuccessed;            // 连接成功

	QMutex m_mutex;                    // 互斥量
};

#endif