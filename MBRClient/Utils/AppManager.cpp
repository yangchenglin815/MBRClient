#include "AppManager.h"
#include "common.h"
#include "AEyeDBFactory.h"
#include "GlobalSignal.h"
#include "DefineData.h"

AppManager::AppManager(bool withParam, QObject *parent)
	: QObject(parent)
	, m_withParam(withParam)
{   
	QString path = Common::getUserDir();
	connect(GlobalSignal::instance(), SIGNAL(sigOnOpenDatabaseFailed()), this, SLOT(onOpenDatabaseFailed()));
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
	AEyeDBFactory::getAEyeDB()->m_pSystemConfigTable->getLocalContral();
	return true;
}

int AppManager::init( bool needUpdate /*= true*/ )
{
	return 0;
}

void AppManager::onOpenDatabaseFailed()
{
	LOG_INFO(QStringLiteral("数据库文件打开失败."));
	_MSGBOX_ERROR(QStringLiteral("数据库文件打开失败"));
	exit(0);
}
