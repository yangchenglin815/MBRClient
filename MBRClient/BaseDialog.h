#ifndef __AEYEBASEWIDGET_H__
#define __AEYEBASEWIDGET_H__

#include <QDialog>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

class BaseDialog : public QDialog 
{
    Q_OBJECT

public:
    explicit BaseDialog(QWidget* parent = 0);
    ~BaseDialog();

    virtual void showWidget();
    virtual void showExec();
	virtual void hideWidget();

protected:
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);

private:
	bool m_mousePressed;
    QPoint m_moveStartPoint;

public:    
	bool m_bForBid;
};

#endif // !__AEYEBASEWIDGET_H__
