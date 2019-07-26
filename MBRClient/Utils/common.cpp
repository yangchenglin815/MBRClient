#include "common.h"
#include <QStandardPaths>
#include <QDir>
#include <Windows.h>

#include "Base64.h"
#include "AES.h"
#include "DefineData.h"

QString Common::getUserDir( const QString& strName /*= "\\AthenaEye"*/ )
{
	QString strDirPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
	strDirPath += strName;

	QDir dir;
	if (!dir.exists(strDirPath))
	{
		dir.mkpath(strDirPath);
	}

	return strDirPath;
}

QString Common::encryptString( QString str )
{
	if(str.length()==0)
		return "";
	int iOutFlag = -1;
	char output[255] = {0};
	char input[255] = {0};

	strcpy(input, str.toStdString().c_str());

	char key[128] = { 0 };
	strcpy(key, "123456789012345678901234567890123456789012345678");

	AES aes;
	aes.Crypt3Des(0,input,strlen(input),key,output,iOutFlag);

  /*sjy 2016-12-15
    解决output数组中间有“\0”结束符的情况。
	导致数据长度和内容与原始数据不一致
	导致解密数据不对的情况
	测试数据：身份证号340304193708150623 加密后，数据中间有"\0",导致数据不全*/
	int posEnd = iOutFlag;

	char* szRet = new char[3*posEnd];
	memset(szRet, 0, 3*posEnd);  
	int iRet = Base64::encode(szRet, output, posEnd);
	QString strRE = QString::fromStdString(szRet);
	
	safeDelete(szRet);
	return strRE;
}

QString Common::decryptString( QString str )
{
	if(str.length()==0)
		return "";

	int posEnd = str.length();
	int iOutFlag = -1;
	char output[255] = {0};
	char input[255] = {0};

	char* szRet = new char[3*posEnd];
	memset(szRet, 0, 3*posEnd);  

	int iRet = Base64::decode(szRet, str.toStdString().c_str(), posEnd);

	/*sjy 2016-12-15
    解决output数组中间有“\0”结束符的情况。
	导致数据长度和内容与原始数据不一致
	导致解密数据不对的情况
	测试数据：身份证号340304193708150623 加密后，数据中间有"\0",导致数据不全*/

	memcpy(input,szRet,iRet);
	delete[] szRet;

	char key[128] = { 0 };
	strcpy(key, "123456789012345678901234567890123456789012345678");

	AES aes;
	//sjy 2016-12-15
	aes.Crypt3Des(1,input,iRet,key,output,iOutFlag);

	QString strRE = QString::fromStdString(output);
	return strRE;
}
