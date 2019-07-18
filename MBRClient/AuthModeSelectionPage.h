#ifndef AUTHMODESELECTIONPAGE_H
#define AUTHMODESELECTIONPAGE_H

#include <QWidget>
#include "ui_AuthModeSelectionPage.h"

class AuthModeSelectionPage : public QWidget
{
	Q_OBJECT

public:
	AuthModeSelectionPage(QWidget *parent = 0);
	~AuthModeSelectionPage();

private:
	Ui::AuthModeSelectionPage ui;
};

#endif // AUTHMODESELECTIONPAGE_H
