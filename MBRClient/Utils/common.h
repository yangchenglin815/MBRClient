#pragma once
#include <QString>

class Common
{
public:
	static QString getUserDir(const QString& strName = "\\AthenaEye");

	static QString encryptString(QString str);

	static QString decryptString(QString str);
};

