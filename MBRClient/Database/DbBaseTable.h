#ifndef DBBASETABLE_H
#define DBBASETABLE_H

#include <QObject>
#include <QReadWriteLock>
#include <QMutex>
#include <QSqlDatabase>

class DbBaseTable : public QObject
{
	Q_OBJECT

public:
	explicit DbBaseTable(QObject *parent = 0);
	~DbBaseTable();

private:
	void initLock();

protected:
	static QReadWriteLock *m_pReadWriteLock;

private:
	QMutex m_pMutex;
};

#endif // DBBASETABLE_H
