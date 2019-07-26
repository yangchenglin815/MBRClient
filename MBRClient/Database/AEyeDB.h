#pragma once

#include <QObject>
#include "BusinessRecordTable.h"
#include "SyetemConfigTable.h"
#include "CacheVersionTable.h"
#include "CommunityManageTable.h"
#include "ParameterTable.h"
#include "RegisterDataTable.h"
#include "DictionaryTable.h"

class AEyeDB
{
public:
	AEyeDB(void);
	~AEyeDB(void);

public:
	BusinessRecordTable* m_pBusinessRecordTable;
	SyetemConfigTable* m_pSystemConfigTable;
	CacheVersionTable* m_pCacheVerTable;
	CommunityManageTable* m_pCommunityManageTable;
	ParameterTable* m_pParameterTable;
	RegisterDataTable* m_pRegisterDataTable;
	DictionaryTable* m_pDictionaryTable;
};

