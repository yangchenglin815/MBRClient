#include "ModelInfoQueryPage.h"
#include <QStandardItemModel>

ModelInfoQueryPage::ModelInfoQueryPage(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	QString strText = QStringLiteral("共有 <font color=green>");
	strText += QStringLiteral("%1</font> 条记录，分 <font color=green>%2/%3</font> 页显示，每页显示 <font color=green>%4</font> 条").arg(0).arg(0).arg(0).arg(0);
	ui.lbl_ct->setText(strText);

	QFont font;
	font.setPixelSize(12);
	ui.tableView->horizontalHeader()->setSectionsMovable(false);
	ui.tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.tableView->setFont(font);

	font.setPixelSize(14);
	font.setBold(true);
	QHeaderView *headerView = ui.tableView->horizontalHeader();
	headerView->setSortIndicatorShown(true);
	headerView->setStyleSheet("QHeaderView::section { padding-left: 1px; border: 1px solid #B0B0B0; }");
	headerView->setFont(font);

	QStandardItemModel *model = new QStandardItemModel(this);

	QStringList headList;
	headList << QStringLiteral("设备类型") 
		<< QStringLiteral("生物类型") 
		<< QStringLiteral("模板类型") 
		<< QStringLiteral("采集时间")  
		<< QStringLiteral("采集经办人") 
		<< QStringLiteral("序号");
	model->setHorizontalHeaderLabels(headList);
	ui.tableView->setModel(model);
}

ModelInfoQueryPage::~ModelInfoQueryPage()
{

}
