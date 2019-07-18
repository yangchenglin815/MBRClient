#include <QLabel>
#include <QPainter>
#include <QFrame>
#include <QVBoxLayout>
#include <QLabel>
#include <QTimer>

#include "ProgressIndicator.h"
#include "LoadingWindow.h"

LoadingWindow::LoadingWindow(int width, int height, QWidget *parent) : QWidget(parent), m_timeMesc(0)
{
	if(width <= 0)
	{
		width = 1024;
	}
	if(height <= 0)
	{
		height = 768;
	}

	//置顶 透明显示(半透明)
	m_screenWidth = width;
	m_screenheight = height;

	QPalette pal = palette();
	pal.setColor(QPalette::Background, QColor(0xff,0xff,0xff,0xff));
	setPalette(pal);
	setAutoFillBackground(false);
	createUI();
	raise();
}

void LoadingWindow::setLoadingText(QString text)
{
	m_loadingTextLabel->setText(text);
}

void LoadingWindow::createUI()
{
	setFixedWidth(m_screenWidth);
	setFixedHeight(m_screenheight);

	m_timer = new QTimer(this);
	connect(m_timer, SIGNAL(timeout()), this, SLOT(updateHint()));

	m_proIndicator = new QProgressIndicator(60, 60, this);
	m_proIndicator->startAnimation();
	m_proIndicator->setAnimationDelay(80);

	QVBoxLayout* vbProIndicator = new QVBoxLayout();
	vbProIndicator->addWidget(m_proIndicator);
	vbProIndicator->setAlignment(Qt::AlignCenter);

	QFont font;
	font.setFamily("微软雅黑");
	font.setPixelSize(20);

	m_loadingTextLabel = new QLabel(this);
	//loadingText->setText(tr("正在导入，请稍后..."));
	m_loadingTextLabel->setFont(font);
	m_loadingTextLabel->setAlignment(Qt::AlignCenter);
	m_loadingTextLabel->setStyleSheet("color: white;background-color: transparent;");

	QVBoxLayout* vbLoadingText = new QVBoxLayout();
	vbLoadingText->addWidget(m_loadingTextLabel);
	vbLoadingText->setAlignment(Qt::AlignCenter);

	QVBoxLayout* vbLayout = new QVBoxLayout(this);
	vbLayout->addLayout(vbProIndicator);
	vbLayout->addLayout(vbLoadingText);
	vbLayout->setAlignment(Qt::AlignCenter);
	vbLayout->setSpacing(m_screenheight*0.01);

	QFrame* hintFrame = new QFrame(this);
	hintFrame->setLayout(vbLayout);
	hintFrame->setFixedWidth(m_screenWidth*0.15);
	hintFrame->setFixedHeight(m_screenWidth*0.15);
	hintFrame->setStyleSheet("border-radius:2px;color:#0090ff;font:bold 15px;background-color:#00439A;"); //rgba(96,96,96,230)

	QVBoxLayout* vbTotalLayout = new QVBoxLayout();
	vbTotalLayout->addWidget(hintFrame);
	vbTotalLayout->setAlignment(Qt::AlignCenter);
	this->setLayout(vbTotalLayout);
}

void LoadingWindow::start(int mesc)
{
	if(mesc != 0)
	{
		m_timeMesc = mesc;
	}

	m_timer->start(m_timeMesc);
}

void LoadingWindow::stop()
{
	if(m_timer == NULL) 
	{
		return;
	}
	m_timer->stop();
}

void LoadingWindow::setTimeOut(int mesc)
{
	m_timeMesc = mesc;
}

void LoadingWindow::paintEvent(QPaintEvent *)
{
	/*Paint事件中使用Clear模式绘图,局部透明显示*/
	QPainter p(this);
	p.fillRect(rect(), QColor(0x2f,0x2f,0x2f,0x00));
}

void LoadingWindow::updateHint()
{
	emit timeOut();
}

LoadingWindow::~LoadingWindow()
{

}
