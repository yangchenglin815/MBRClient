#ifndef DICTIONARYTABLE_H
#define DICTIONARYTABLE_H

#include <QObject>
#include "DbBaseTable.h"
#include "ibpp.h"
#include "StructData.h"

class DictionaryTable : public DbBaseTable
{
	Q_OBJECT

public:
	DictionaryTable(QObject *parent = 0);
	~DictionaryTable();

public:
	bool updateDict(int version, const QVector<DictionaryData>& dicts);
	bool getDict(QString key, QMap<QString, QString>& notesByValue);

private:
	QString m_sTableName;
};

#endif // DICTIONARYTABLE_H
