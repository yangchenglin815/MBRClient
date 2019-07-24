#include "AppManager.h"
#include "common.h"

AppManager::AppManager(bool withParam, QObject *parent)
	: QObject(parent)
	, m_withParam(withParam)
{   
	QString path = common::getUserDir();
	if (!checkRunningEnv())
	    exit(0);
}

AppManager::~AppManager()
{

}

int AppManager::startup( QString command /*= ""*/ )
{
	return 0;
}

bool AppManager::checkRunningEnv()
{
	return true;
}

int AppManager::init( bool needUpdate /*= true*/ )
{
	return 0;
}
