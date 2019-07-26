#ifndef COMMUNITYMANAGETABLE_H
#define COMMUNITYMANAGETABLE_H

#include <QObject>
#include "DbBaseTable.h"
#include "ibpp.h"

class CommunityManageTable : public DbBaseTable
{
	Q_OBJECT

public:
	CommunityManageTable(QObject *parent = 0);
	~CommunityManageTable();

public:
	bool getCommunityManage(QString& json, int key, int type);
	bool getCommunityManage(QString& json, QString userName, QString userIdentify , int type);

private:
	QString m_sTableName;
};

#endif // COMMUNITYMANAGETABLE_H
