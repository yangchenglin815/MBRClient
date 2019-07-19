#ifndef __AEYEIPADDRESSCONTROL_H__
#define __AEYEIPADDRESSCONTROL_H__

#include <QWidget> 

class QLabel; 
class QLineEdit; 
class QRegExpValidator;
class IpAddressPartWidget; 
class IpAddressWidget : public QWidget { 
    Q_OBJECT 
public: 
    IpAddressWidget(/*int iWidth, int iHeight, */QWidget* pParent = 0); 
    ~IpAddressWidget(); 
     
    QString text(); 
    void setStyleSheet(const QString &styleSheet); 
    void setPartFocus(int iIndex);
    int filled();

    public slots:
        void setText(const QString &text); 

signals: 
        void textChanged(const QString& text); 
        void textEdited(const QString &text); 

protected:
    virtual void paintEvent(QPaintEvent *event);

    private slots: 
        void textChangedslot(const QString& text); 
        void textEditedslot(const QString &text); 

private: 
    IpAddressPartWidget* m_part1Widget; 
    IpAddressPartWidget* m_part2Widget; 
    IpAddressPartWidget* m_part3Widget; 
    QLineEdit* m_part4Widget; 

    QLabel* m_dot1Label; 
    QLabel* m_dot2Label;     
    QLabel* m_dot3Label; 
    QRegExpValidator* m_validator;
};

#endif // !__AEYEIPADDRESSCONTROL_H__
