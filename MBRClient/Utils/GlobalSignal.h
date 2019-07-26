#ifndef GLOBALSIGNAL_H
#define GLOBALSIGNAL_H

#include <QObject>

class GlobalSignal : public QObject
{
	Q_OBJECT

public:
	static GlobalSignal* instance();

private:
	GlobalSignal(QObject *parent = 0);
	~GlobalSignal();

signals:
	void sigOnOpenDatabaseFailed();

private:
	static GlobalSignal* m_pInstance;
};

#endif // GLOBALSIGNAL_H
