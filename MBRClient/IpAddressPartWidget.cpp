#include "IpAddressPartWidget.h" 
#include <QIntValidator> 
#include <QKeyEvent> 

IpAddressPartWidget::IpAddressPartWidget(QWidget *parent/* = 0*/) : QLineEdit(parent) { 
    next_tab_ = NULL; 

    this->setMaxLength(3); 
    this->setFrame(false); 
    this->setAlignment(Qt::AlignCenter); 

    QValidator *validator = new QIntValidator(0, 255, this); 
    this->setValidator(validator); 

    connect(this, SIGNAL(textEdited(const QString&)), this, SLOT(text_edited(const QString&))); 
} 

IpAddressPartWidget::~IpAddressPartWidget(void) {

} 

void IpAddressPartWidget::focusInEvent(QFocusEvent *e) { 
    this->selectAll(); 
    QLineEdit::focusInEvent(e); 
} 

void IpAddressPartWidget::keyPressEvent(QKeyEvent *event) { 
    if (event->key() == Qt::Key_Period) { 
        if (next_tab_) { 
            next_tab_->setFocus(); 
            next_tab_->selectAll(); 
        } 
    } 

    QLineEdit::keyPressEvent(event); 
} 

void IpAddressPartWidget::text_edited(const QString& text) { 
    QIntValidator v(0, 255, this); 
    QString ipaddr = text; 
    int pos = 0; 
    QValidator::State state = v.validate(ipaddr, pos);  
    if (state == QValidator::Acceptable) { 
        if (ipaddr.size() > 1) { 
            if (ipaddr.size() == 2) { 
                int ipnum = ipaddr.toInt(); 

                if (ipnum > 25) { 
                    if (next_tab_) { 
                        next_tab_->setFocus(); 
                        next_tab_->selectAll(); 
                    }     
                } 
            } else { 
                if (next_tab_) { 
                    next_tab_->setFocus(); 
                    next_tab_->selectAll(); 
                }     
            } 
        } 
    } 
}
