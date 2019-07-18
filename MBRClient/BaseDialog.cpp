#include "BaseDialog.h"
//#include "AEyeWidgetDef.h"
#include "LoadingWidget.h"
#include <QDesktopWidget>
#include <QApplication>

const QString CLIENT_NAME = QStringLiteral("人力资源和社会保障业务经办身份认证客户端");

BaseDialog::BaseDialog(QWidget* parent/* = 0*/)
    : QDialog(parent) 
{
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint | Qt::Dialog);

	m_mousePressed = false;
	m_bForBid = true;
}

BaseDialog::~BaseDialog() 
{

}

void BaseDialog::mousePressEvent(QMouseEvent* mouseEvent) 
{
	if(!m_bForBid)
	{
		return;
	}

    switch(mouseEvent->button()) 
	{
    case Qt::LeftButton:
        m_mousePressed = true;
        break;
    default:
        break;
    }

    m_moveStartPoint = mouseEvent->globalPos() - pos();
}

void BaseDialog::mouseReleaseEvent(QMouseEvent* mouseEvent)
{
    m_mousePressed = false;
}

void BaseDialog::mouseMoveEvent(QMouseEvent* mouseEvent) 
{
    if(m_mousePressed) 
	{
        QPoint currentPoint = mouseEvent->globalPos();
        move(currentPoint - m_moveStartPoint);
    }
}

void BaseDialog::showWidget() 
{
    LOADINGWIDGET->endLoading(this);
    setWindowTitle(CLIENT_NAME);

    showNormal();
    raise();
    activateWindow();
}

void BaseDialog::hideWidget() 
{
	LOADINGWIDGET->endLoading(this);
	setWindowTitle(CLIENT_NAME);

	hide();
	raise();
	activateWindow();
}

void BaseDialog::showExec() 
{
    LOADINGWIDGET->endLoading(this);
    setWindowTitle(CLIENT_NAME);
    setModal(true);

    raise();
    activateWindow(); 
    exec();
}
