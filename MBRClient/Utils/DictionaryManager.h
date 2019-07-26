#pragma once

#include <QString>
#include <QSet>
#include <QMap>

enum DictType
{
	Dict_CertificateType, //证件类型
};

#define DICTIONARYMANAGER DictionaryManager::getInstance()
class DictionaryManager
{
public:
	static DictionaryManager* getInstance()
	{
		if (m_instance == NULL)
		{
			m_instance = new DictionaryManager;
		}
		return m_instance;
	}

	static void releaseInstance()
	{
		if (m_instance != NULL)
		{
			delete m_instance;
			m_instance = NULL;
		}
	}

	enum DictTypa
	{
		AAC058, //
	};

	void getNecessaryDictKeys(QSet<QString>& dictKeys);
	void getDictionaryItem(QString name, QMap<QString, QString>& dictItem);
	QString getDictionaryNote(QString name, QString value);
	QString getDictionaryValue(QString name, QString note);
	void loadFromDB();

private:
	static DictionaryManager* m_instance;
	DictionaryManager();
	~DictionaryManager();

	void initNecessaryDictKeys();

private:
	QSet<QString> m_necessaryDictNames;
	QMap<QString, QMap<QString, QString> > m_dictItemsByName;
};

