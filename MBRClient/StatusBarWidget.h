#ifndef STATUSBARWIDGET_H
#define STATUSBARWIDGET_H

#include <QWidget>
#include "ui_StatusBarWidget.h"

class StatusBarWidget : public QWidget
{
	Q_OBJECT

public:
	StatusBarWidget(QWidget *parent = 0);
	~StatusBarWidget();

private slots:
	void SlotOnUpdate(const QString & linkUrl);
	void SlotOnOpenUrl(const QString & linkUrl);

private:
	void InitUI();
	void InitConnect();

private:
	Ui::StatusBarWidget ui;
};

#endif // STATUSBARWIDGET_H
