#include "RecordQueryPage.h"
#include <QStandardItemModel>

RecordQueryPage::RecordQueryPage(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	QString strETmp = QStringLiteral("当前建模：<font color=red>%1</font>人").arg(0);
	ui.lbl_enum->setText(strETmp);

	QString strRTmp = QStringLiteral("当前认证：<font color=red>%1</font>人").arg(0);
	ui.lbl_rnum->setText(strRTmp);

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
	headList << QStringLiteral("姓名") 
		     << QStringLiteral("证件号码") 
			 << QStringLiteral("联系方式") 
			 << QStringLiteral("操作类型")  
			 << QStringLiteral("生物类型") 
			 << QStringLiteral("操作结果")
			 << QStringLiteral("操作时间") 
			 << QStringLiteral("序号");
	model->setHorizontalHeaderLabels(headList);
	ui.tableView->setModel(model);
}

RecordQueryPage::~RecordQueryPage()
{

}
