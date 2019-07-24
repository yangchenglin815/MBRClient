#ifndef SINGLEPROCESSHELPER_H
#define SINGLEPROCESSHELPER_H

#include <QObject>

class LocalServer;
class LocalClient;
class QWidget;
class SingleProcessHelper : public QObject
{
	Q_OBJECT

public:
	explicit SingleProcessHelper(const QString &serverName, const QString &holder = "", QObject *parent = 0);
	~SingleProcessHelper();

	virtual void handleQuitRequest();
	bool takeLock();
	void sendArguments(const QString &strName);

#ifndef NO_GUI
	void setActivationWindow(QWidget *aw);
#endif

	bool hasRemote();
	bool hasRemote(QString &holder);
	static bool hasRemote(const QString &strName, QString &holder);

	bool activateRemote();
	static bool activateRemote(const QString &strName);

	bool killRemote();
	static bool killRemote(const QString &strName);

signals:
	void sigOnArguments(const QStringList &args);

public slots:
    void slotOnNewConnection();

private:
	void activateWindow();
	void forceQuit();

private:
	LocalServer *m_server;
	QString m_serverName;
	QString m_holder;
	QWidget *m_actWin;
	QString m_processId;
};

#endif // SINGLEPROCESSHELPER_H
