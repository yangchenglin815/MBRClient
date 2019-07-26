#ifndef REGISTERDATATABLE_H
#define REGISTERDATATABLE_H

#include <QObject>
#include "DbBaseTable.h"
#include "ibpp.h"

class RegisterDataTable : public DbBaseTable
{
	Q_OBJECT

public:
	RegisterDataTable(QObject *parent = 0);
	~RegisterDataTable();

public:
	bool UpdateRegisterData(int state);
	int getRegisterFlag(QString mac);
	bool insertData(QString machineCode, int registerStatus);
	bool deleteData();

private:
	QString m_sTableName;
};

#endif // REGISTERDATATABLE_H
