#ifndef SYETEMCONFIGTABEL_H
#define SYETEMCONFIGTABEL_H

#include <QObject>
#include "DbBaseTable.h"
#include "ibpp.h"

class SyetemConfigTable : public DbBaseTable
{
	Q_OBJECT

public:
	SyetemConfigTable(QObject *parent = 0);
	~SyetemConfigTable();

public:
	bool setServerConfig(QString sUrl, QString sUpdateIP);
	bool getUpdateServerData(QString &sData);
	bool getLocalContral();
	bool isSysConfigExist();

private:
	QString m_sTableName;
};

#endif // SYETEMCONFIGTABEL_H
