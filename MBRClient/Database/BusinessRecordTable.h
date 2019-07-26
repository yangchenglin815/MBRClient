#ifndef BUSINESSRECORDTABLE_H
#define BUSINESSRECORDTABLE_H

#include <QObject>
#include "DbBaseTable.h"
#include "ibpp.h"
#include "StructData.h"

class BusinessRecordTable : public DbBaseTable
{
	Q_OBJECT

public:
	BusinessRecordTable(QObject *parent = 0);
	~BusinessRecordTable();

public:
	void saveRecord(const RecordInfo& recordInfo);
	bool getPersonInfoOfGreatModel(int& number);
	bool getPersonInfoOfRecogSuccessed(int& number);
	bool getRecordWithoutPics(QVector<RecordInfo>& recordInfos);
	bool clearRecord();

private:
	QString m_sTableName;
};

#endif // BUSINESSRECORDTABLE_H
