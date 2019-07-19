#ifndef SYSTEMSETTINGSPAGE_H
#define SYSTEMSETTINGSPAGE_H

#include <QWidget>
#include "BaseDialog.h"
#include "ui_SystemSettingsPage.h"

class SystemSettingsPage : public BaseDialog
{
	Q_OBJECT

public:
	SystemSettingsPage(QWidget *parent = 0);
	~SystemSettingsPage();

private:
	Ui::SystemSettingsPage ui;
};

#endif // SYSTEMSETTINGSPAGE_H
