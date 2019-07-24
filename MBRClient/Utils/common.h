#pragma once
#include <QString>

class common
{
public:
	static QString getUserDir(const QString& strName = "\\AthenaEye");

	static bool runAppInSingleInstanceMode(const QString& appName = "AthenaEye");
};

