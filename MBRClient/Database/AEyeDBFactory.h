#ifndef DBFACTORY_H
#define DBFACTORY_H

#include "AEyeDB.h"
#include "EnumData.h"

class AEyeDBFactory
{
public:
	static AEyeDB *getAEyeDB(int type = e_firebird);
	static void release();

private:
	static AEyeDB* m_pAEyeDB;
};

#endif