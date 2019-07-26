#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QObject>
#include "StructData.h"

class DataModel : public QObject
{
	Q_OBJECT

public:
	static DataModel* instance();

public:
	void setConfigData(stDbData dbData);
	stDbData getCongfigData() const;

private:
	DataModel(QObject *parent = 0);
	~DataModel();

private:
	static DataModel* m_pInstance;
	stDbData m_stConfigData;
};

#endif // DATAMODEL_H
