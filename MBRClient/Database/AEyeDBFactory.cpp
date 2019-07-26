#include "AEyeDBFactory.h"
#include "AEyeDB_Firebird.h"

AEyeDB* AEyeDBFactory::m_pAEyeDB = NULL;

AEyeDB * AEyeDBFactory::getAEyeDB( int type /*= e_firebird*/ )
{
	if (type == e_firebird)
	{
		if (m_pAEyeDB == NULL)
		{
			m_pAEyeDB = AEyeDB_Firebird::instance();
		}
	}

	return m_pAEyeDB;
}

void AEyeDBFactory::release()
{
	if (m_pAEyeDB != NULL)
	{
		delete m_pAEyeDB;
		m_pAEyeDB = NULL;
	}
}

