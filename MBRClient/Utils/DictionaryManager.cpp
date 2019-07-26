#include "DictionaryManager.h"
#include "DefineData.h"

DictionaryManager* DictionaryManager::m_instance = NULL;
DictionaryManager::DictionaryManager()
{
	initNecessaryDictKeys();
}

DictionaryManager::~DictionaryManager()
{
  
}

void DictionaryManager::initNecessaryDictKeys()
{
	m_necessaryDictNames.insert("AAC058");
}

void DictionaryManager::getNecessaryDictKeys(QSet<QString>& dictKeys )
{
	dictKeys = m_necessaryDictNames;
}

void DictionaryManager::getDictionaryItem(QString name, QMap<QString, QString>& dictItem)
{
	if(m_dictItemsByName.contains(name)) {
		dictItem = m_dictItemsByName[name];
	}
}

QString DictionaryManager::getDictionaryNote(QString name, QString value)
{
	if(m_dictItemsByName.contains(name)) {
		if(m_dictItemsByName[name].contains(value)) {
			return m_dictItemsByName[name][value];
		}
	}

	return "";
}

QString DictionaryManager::getDictionaryValue(QString name, QString note)
{
	if(m_dictItemsByName.contains(name)) {
		return m_dictItemsByName[name].key(note);
	}

	return "";
}

void DictionaryManager::loadFromDB()
{
	if(!m_dictItemsByName.isEmpty()) {
		return;
	}

	QSet<QString>::iterator it = m_necessaryDictNames.begin();
	for(; it != m_necessaryDictNames.end(); it++) {
		QMap<QString, QString> dictItem;
		if(DBHELPER->m_pDictionaryTable->getDict(*it, dictItem)) {
			m_dictItemsByName.insert(*it, dictItem);
		}
	}

	if(m_dictItemsByName.isEmpty()) {
		QMap<QString, QString> dictItem;
		dictItem["0"] = "身份证";
		dictItem["0"] = "身份证";
		dictItem["1"] = "护照";
		dictItem["2"] = "港澳台居民往来内地通行证";
		dictItem["3"] = "户口簿";
		dictItem["4"] = "其他";
		dictItem["5"] = "社保卡";
		dictItem["6"] = "二代国内居民身份证";
		dictItem["7"] = "香港特区护照或通行证";
		dictItem["8"] = "澳门特区护照或通行证";
		dictItem["9"] = "台湾特区护照或通行证";
		dictItem["10"] = "外国人护照";
		dictItem["11"] = "朝鲜族特殊证件";

		m_dictItemsByName.insert("AAC058", dictItem);
	}
}