#ifndef PARAMETERTABLE_H
#define PARAMETERTABLE_H

#include <QObject>
#include "DbBaseTable.h"
#include "ibpp.h"
#include "StructData.h"

class ParameterTable : public DbBaseTable
{
	Q_OBJECT

public:
	ParameterTable(QObject *parent = 0);
	~ParameterTable();

public:
	bool updateParam(int version, const QVector<ParameterData>& params);
	bool getParam(QString key, QMap<int, QString>& valuesBySysCode);

private:
	QString m_sTableName;
};

#endif // PARAMETERTABLE_H
