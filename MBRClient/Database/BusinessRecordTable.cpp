#include "BusinessRecordTable.h"
#include "common.h"
#include "DefineData.h"
#include <QVector>

BusinessRecordTable::BusinessRecordTable(QObject *parent)
	: DbBaseTable(parent)
	, m_sTableName("T_BUSINESSRECORD")
{

}

BusinessRecordTable::~BusinessRecordTable()
{

}

void BusinessRecordTable::saveRecord( const RecordInfo& recordInfo )
{
	m_pReadWriteLock->lockForWrite();
	QString sqlStatement = QString("insert into %1 (NAME, IDCARD, CONTACT, BUSINESSTYPE, BIOTYPE, SUCCESSED, FINISHDATE) values ('%2', '%3', '%4', '%5', '%6', '%7', '%8');")
		.arg(m_sTableName)
		.arg(Common::encryptString(recordInfo.name))
		.arg(Common::encryptString(recordInfo.idCard))
		.arg(recordInfo.contact)
		.arg(recordInfo.businessType)
		.arg(recordInfo.bioType)
		.arg(recordInfo.successed)
		.arg(recordInfo.finishDate);

	if (DBHELPER->doSql(sqlStatement))
	{
		m_pReadWriteLock->unlock();
		m_pReadWriteLock->lockForRead();

		int recordId = -1;
		QString sqlStatement = QString("select max(ID) from %1").arg(m_sTableName);

		DBRows dbRows;
		if (DBHELPER->doSql(sqlStatement, &dbRows))
		{
			DBRows::iterator it = dbRows.begin();
			for (; it != dbRows.end(); it++)
			{
				DBRow* dbRow = *it;
				DBHELPER->getInt(*dbRow, 1, recordId);
				delete dbRow;
				break;
			}
		}
		m_pReadWriteLock->unlock();
		m_pReadWriteLock->lockForWrite();

		if(recordId >= 0) 
		{
			int idCardPicSections = 1;
			int idCardPicSize = recordInfo.idCardPic.size();
			if(idCardPicSize > MAX_BLOB_SIZE) 
			{
				if(idCardPicSize % MAX_BLOB_SIZE == 0) {
					idCardPicSections = idCardPicSize / MAX_BLOB_SIZE;
				} else {
					idCardPicSections = idCardPicSize / MAX_BLOB_SIZE + 1;
				}
			}

			for (int i = 0; i < idCardPicSections; i++) {
				QString picSection = recordInfo.idCardPic.mid(i * MAX_BLOB_SIZE , MAX_BLOB_SIZE);
				sqlStatement = QString("insert into %1 (RECORDID, IMAGETYPE, IMAGE) values ('%2', '%3', '%4');")
					.arg("T_IMAGE")
					.arg(recordId)
					.arg(0)
					.arg(picSection);

				DBHELPER->doSql(sqlStatement);
			}

			int businessPicSections = 1;
			int businessPicSize = recordInfo.businessPic.size();
			if(businessPicSize > MAX_BLOB_SIZE) {
				if(businessPicSize % MAX_BLOB_SIZE == 0) {
					businessPicSections = businessPicSize / MAX_BLOB_SIZE;
				} else {
					businessPicSections = businessPicSize / MAX_BLOB_SIZE + 1;
				}
			}

			for (int i = 0; i < businessPicSections; i++) {
				QString picSection = recordInfo.businessPic.mid(i * MAX_BLOB_SIZE , MAX_BLOB_SIZE);
				sqlStatement = QString("insert into %1 (RECORDID, IMAGETYPE, IMAGE) values ('%2', '%3', '%4');")
					.arg("T_IMAGE")
					.arg(recordId)
					.arg(1)
					.arg(picSection);

				DBHELPER->doSql(sqlStatement);
			}
		}
	}

	m_pReadWriteLock->unlock();
}

bool BusinessRecordTable::getPersonInfoOfGreatModel( int& number )
{
	m_pReadWriteLock->lockForRead();

	QString sqlStatement = QString("select NAME, IDCARD from %1 where BUSINESSTYPE='0' and SUCCESSED='1' group by NAME, IDCARD;")
		.arg(m_sTableName);

	DBRows dbRows;
	if (!DBHELPER->doSql(sqlStatement, &dbRows)) {
		m_pReadWriteLock->unlock();
		return false;
	}

	number = 0;
	DBRows::iterator it = dbRows.begin();
	for(;it != dbRows.end(); it++) 
		++number;

	m_pReadWriteLock->unlock();
	return true;
}

bool BusinessRecordTable::getPersonInfoOfRecogSuccessed( int& number )
{
	m_pReadWriteLock->lockForRead();

	QString sqlStatement = QString("select NAME, IDCARD from %1 where BUSINESSTYPE='1' and SUCCESSED='1' group by NAME, IDCARD;")
		.arg(m_sTableName);

	DBRows dbRows;
	if (!DBHELPER->doSql(sqlStatement, &dbRows)) {
		m_pReadWriteLock->unlock();
		return false;
	}

	number = 0;
	DBRows::iterator it = dbRows.begin();
	for(;it != dbRows.end(); it++) 
		++number;

	m_pReadWriteLock->unlock();
	return true;
}

bool BusinessRecordTable::getRecordWithoutPics( QVector<RecordInfo>& recordInfos )
{
	m_pReadWriteLock->lockForRead();

	bool successed = false;
	QString sqlStatement = QString("select NAME, IDCARD, CONTACT, BUSINESSTYPE, BIOTYPE, SUCCESSED, FINISHDATE, ID from %1;")
		.arg(m_sTableName);

	DBRows dbRows;
	if (!DBHELPER->doSql(sqlStatement, &dbRows)) {
		m_pReadWriteLock->unlock();
		return false;
	}

	DBRows::iterator it = dbRows.begin();
	for(;it != dbRows.end(); it++) {
		DBRow* dbRow = *it;

		QString encryptedName;
		QString encryptedIdCard;

		RecordInfo recordInfo;
		DBHELPER->getString(*dbRow, 1, encryptedName);
		DBHELPER->getString(*dbRow, 2, encryptedIdCard);

		recordInfo.name = Common::decryptString(encryptedName);
		recordInfo.idCard = Common::decryptString(encryptedIdCard);

		DBHELPER->getString(*dbRow, 3, recordInfo.contact);
		DBHELPER->getInt(*dbRow, 4, recordInfo.businessType);
		DBHELPER->getInt(*dbRow, 5, recordInfo.bioType);
		DBHELPER->getInt(*dbRow, 6, recordInfo.successed);
		DBHELPER->getString(*dbRow, 7, recordInfo.finishDate);
		DBHELPER->getInt(*dbRow, 8, recordInfo.recordId);
		recordInfos.push_back(recordInfo);

		successed = true;
		delete dbRow;
	}

	m_pReadWriteLock->unlock();
	return successed;
}

bool BusinessRecordTable::clearRecord()
{
	m_pReadWriteLock->lockForWrite();

	QString sqlStatement = QString("delete from %1;").arg(m_sTableName); 
	bool successed = DBHELPER->doSql(sqlStatement);

	sqlStatement = QString("delete from %1;").arg("T_IMAGE"); 
	successed = DBHELPER->doSql(sqlStatement);

	//emit readyUpdateOnlineCount();
	m_pReadWriteLock->unlock();
	return successed;
}

