#ifndef LOADINGWINDOW_H
#define LOADINGWINDOW_H

#include <QWidget>

class QLabel;
class QTimer;
class QProgressIndicator;
class LoadingWindow : public QWidget
{
	Q_OBJECT

public:
	explicit LoadingWindow(int width = 0, int height = 0, QWidget *parent = 0);
	virtual ~LoadingWindow();

public:
	void setTimeOut(int mesc);
	void start(int mesc = 0);
	void stop();
	void setLoadingText(QString strPrompt);

protected:
	void paintEvent(QPaintEvent *);

private:
	void createUI();

private slots:
	void updateHint();

signals:
	void timeOut();

private:
	QTimer* m_timer;                  /*! 超时定时器*/
	QLabel* m_loadingGifLabel;         /*! 加载gif*/
	QLabel* m_loadingTextLabel;        /*! 加载gif标签*/
	QProgressIndicator* m_proIndicator; /*! Loading图像*/

	int m_timeMesc;                    /*! 超时时间*/
	unsigned int m_screenWidth;        /*! 提示页面宽度*/
	unsigned int m_screenheight;        /*! 提示页面高度*/
};

#endif // LOADINGWINDOW_H
