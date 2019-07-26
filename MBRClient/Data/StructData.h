#ifndef STRUCTDATA_H
#define STRUCTDATA_H

#include <QVariant>
#include "ConstData.h"

struct RecordInfo
{
	QString name;
	QString idCard;
	QString idCardPic;
	QString contact;
	int businessType;
	int bioType;
	int successed;
	QString finishDate;
	QString businessPic;
	int recordId;
};

typedef struct _stDbData 
{
	bool      registered;
	bool      faceSupported;
	bool      fveinSupported;
	bool      fprintSupported;
	QString serverUrl;

	_stDbData() 
	{
		registered               = true;
		faceSupported                = false;
		fveinSupported                = false;
		fprintSupported                = false;
		serverUrl            = WSURL;
	}

	_stDbData& operator =(const _stDbData& ptr) 
	{
		if (this != &ptr)
		{
			this->registered = ptr.registered;
			this->faceSupported = ptr.faceSupported;
			this->fveinSupported = ptr.fveinSupported;
			this->fprintSupported = ptr.fprintSupported;
			this->serverUrl = ptr.serverUrl;
		}
		return *this;
	}
} stDbData;

struct ParameterData
{
	QString paramName;
	QString paramValue;
	QString paramDesc;
	int paramType;
	int sysCode;

	ParameterData()
	{
		sysCode = -1;
	}
};

struct DictionaryData
{
	QString fieldName;
	QString fieldNote;
	QString fieldValue;
	QString valueNote;
	QString dictName;
};

#endif