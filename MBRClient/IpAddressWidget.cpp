#include "IpAddressWidget.h" 
#include "IpAddressPartWidget.h" 
#include <QRegExpValidator> 
#include <QLabel> 
#include <QPainter>

IpAddressWidget::IpAddressWidget(QWidget* pParent /* = 0 */) 
    : QWidget(pParent)
{
	int width = 160;
	int height = 33;
	setFixedSize(width, height);

	QRegExp regExp("^((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)$"); 
	m_validator = new QRegExpValidator(regExp, this); 

	int iTmp = width/4;

	m_part1Widget = new IpAddressPartWidget(this); 
	m_part1Widget->setGeometry(QRect(0, 0, iTmp, height)); 

	m_part2Widget = new IpAddressPartWidget(this); 
	m_part2Widget->setGeometry(QRect(iTmp, 0, iTmp, height)); 

	m_part3Widget = new IpAddressPartWidget(this); 
	m_part3Widget->setGeometry(QRect(2*iTmp, 0, iTmp, height)); 

	m_part4Widget = new IpAddressPartWidget(this); 
	m_part4Widget->setGeometry(QRect(3*iTmp, 0, iTmp, height)); 

	m_dot1Label = new QLabel(this); 
	m_dot1Label->setText(" ."); 
	m_dot1Label->setGeometry(QRect(iTmp - 1, 1, 6, 18)); 
	m_dot1Label->setAlignment(Qt::AlignCenter); 

	m_dot2Label = new QLabel(this); 
	m_dot2Label->setText(" ."); 
	m_dot2Label->setGeometry(QRect(2*iTmp - 1, 1, 6, 18)); 
	m_dot2Label->setAlignment(Qt::AlignCenter); 

	m_dot3Label = new QLabel(this);	
	m_dot3Label->setText(" ."); 
	m_dot3Label->setGeometry(QRect(3*iTmp - 1, 1, 6, 18)); 
	m_dot3Label->setAlignment(Qt::AlignCenter); 

	QWidget::setTabOrder(m_part1Widget, m_part2Widget); 
	QWidget::setTabOrder(m_part2Widget, m_part3Widget); 
	QWidget::setTabOrder(m_part3Widget, m_part4Widget); 

	m_part1Widget->set_nexttab_edit(m_part2Widget); 
	m_part2Widget->set_nexttab_edit(m_part3Widget); 
	m_part3Widget->set_nexttab_edit(m_part4Widget); 

	connect(m_part1Widget, SIGNAL(textChanged(const QString&)), this, SLOT(textChangedslot(const QString&))); 
	connect(m_part1Widget, SIGNAL(textEdited(const QString&)), this, SLOT(textEditedslot(const QString&))); 

	connect(m_part2Widget, SIGNAL(textChanged(const QString&)), this, SLOT(textChangedslot(const QString&))); 
	connect(m_part2Widget, SIGNAL(textEdited(const QString&)), this, SLOT(textEditedslot(const QString&))); 

	connect(m_part3Widget, SIGNAL(textChanged(const QString&)), this, SLOT(textChangedslot(const QString&))); 
	connect(m_part3Widget, SIGNAL(textEdited(const QString&)), this, SLOT(textEditedslot(const QString&)));

	connect(m_part4Widget, SIGNAL(textChanged(const QString&)), this, SLOT(textChangedslot(const QString&))); 	 
	connect(m_part4Widget, SIGNAL(textEdited (const QString&)), this, SLOT(textEditedslot(const QString&))); 
} 

IpAddressWidget::~IpAddressWidget()
{ 

} 

void IpAddressWidget::textChangedslot(const QString& /*text*/) 
{ 
    QString ippart1, ippart2, ippart3, ippart4; 
    ippart1 = m_part1Widget->text(); 
    ippart2 = m_part2Widget->text(); 
    ippart3 = m_part3Widget->text(); 
    ippart4 = m_part4Widget->text(); 

    QString ipaddr = QString("%1.%2.%3.%4") 
        .arg(ippart1) 
        .arg(ippart2) 
        .arg(ippart3) 
        .arg(ippart4); 

    emit textChanged(ipaddr); 
} 

void IpAddressWidget::textEditedslot(const QString &/*text*/)
{ 
    QString ippart1, ippart2, ippart3, ippart4; 
    ippart1 = m_part1Widget->text(); 
    ippart2 = m_part2Widget->text(); 
    ippart3 = m_part3Widget->text(); 
    ippart4 = m_part4Widget->text(); 

    QString ipaddr = QString("%1.%2.%3.%4") 
        .arg(ippart1) 
        .arg(ippart2) 
        .arg(ippart3) 
        .arg(ippart4); 

    emit textEdited(ipaddr); 
} 

void IpAddressWidget::setText(const QString &text)
{ 
    QString ippart1, ippart2, ippart3, ippart4; 
    QString strValidate = text; 

    int nPos = 0; 
    QValidator::State state = m_validator->validate(strValidate, nPos); 
    QStringList ippartlist = text.split("."); 

    int strcount = ippartlist.size(); 
    int index = 0; 
    if (index < strcount)
	{ 
        ippart1 = ippartlist.at(index); 
    } 

    if (++index < strcount)
	{ 
        ippart2 = ippartlist.at(index); 
    }

    if (++index < strcount) 
	{ 
        ippart3 = ippartlist.at(index); 
    }

    if (++index < strcount) 
	{ 
        ippart4 = ippartlist.at(index); 
    } 

    m_part1Widget->setText(ippart1); 
    m_part2Widget->setText(ippart2); 
    m_part3Widget->setText(ippart3); 
    m_part4Widget->setText(ippart4); 
} 

QString IpAddressWidget::text() 
{ 
    QString ippart1, ippart2, ippart3, ippart4; 
    ippart1 = m_part1Widget->text(); 
    ippart2 = m_part2Widget->text(); 
    ippart3 = m_part3Widget->text(); 
    ippart4 = m_part4Widget->text(); 

    return QString("%1.%2.%3.%4") 
        .arg(ippart1) 
        .arg(ippart2) 
        .arg(ippart3) 
        .arg(ippart4); 
} 

void IpAddressWidget::setStyleSheet(const QString &styleSheet) 
{ 
    m_part1Widget->setStyleSheet(styleSheet); 
    m_part2Widget->setStyleSheet(styleSheet); 
    m_part3Widget->setStyleSheet(styleSheet); 
    m_part4Widget->setStyleSheet(styleSheet); 
}

void IpAddressWidget::paintEvent(QPaintEvent *event) 
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    QPixmap ixmap("../Resources/img/frm");
    painter.drawPixmap(ixmap.rect(), ixmap);
}

void IpAddressWidget::setPartFocus(int iIndex) 
{
    switch(iIndex) 
	{
    case 1:
        m_part1Widget->setFocus();   
        break;
    case 2:
        m_part2Widget->setFocus();   
        break;
    case 3:
        m_part3Widget->setFocus();   
        break;
    case 4:
        m_part4Widget->setFocus();   
        break;
    default:
        break;
    }
}

int IpAddressWidget::filled() 
{
    if(m_part1Widget->text().trimmed().isEmpty()) 
	{
        return 1;
    }
    if(m_part2Widget->text().trimmed().isEmpty()) 
	{
        return 2;
    }
    if(m_part3Widget->text().trimmed().isEmpty()) 
	{
        return 3;
    }
    if(m_part4Widget->text().trimmed().isEmpty())
	{
        return 4;
    }

    return 0;
}
