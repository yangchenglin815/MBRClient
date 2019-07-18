#ifndef __AEYEIPADDRESSCONTROLPART_H__
#define __AEYEIPADDRESSCONTROLPART_H__

#include <QLineEdit> 

class QWidget; 
class QFocusEvent; 
class QKeyEvent; 
class IpAddressPartWidget : public QLineEdit { 
    Q_OBJECT 
public: 
    IpAddressPartWidget(QWidget *parent = 0); 
    ~IpAddressPartWidget(void); 

    void set_nexttab_edit(QLineEdit *nexttab) { 
        next_tab_ = nexttab;
    } 

protected: 
    virtual void focusInEvent(QFocusEvent *e); 
    virtual void keyPressEvent(QKeyEvent *event);   

    private slots: 
        void text_edited(const QString& text); 

private: 
    QLineEdit *next_tab_; 
}; 

#endif // !__AEYEIPADDRESSCONTROLPART_H__
