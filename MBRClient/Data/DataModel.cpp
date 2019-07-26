#include "DataModel.h"

DataModel* DataModel::m_pInstance = NULL;

DataModel::DataModel(QObject *parent)
	: QObject(parent)
{

}

DataModel::~DataModel()
{

}

DataModel* DataModel::instance()
{
	if (m_pInstance == NULL)
	{
		m_pInstance = new DataModel;
	}
	return m_pInstance;
}

void DataModel::setConfigData( stDbData dbData )
{
	m_stConfigData = dbData;
}

stDbData DataModel::getCongfigData() const
{
	return m_stConfigData;
}
