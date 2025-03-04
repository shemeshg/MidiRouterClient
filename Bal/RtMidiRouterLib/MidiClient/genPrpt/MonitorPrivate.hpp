//-define-file header genPrpt/MonitorPrivate.h
//-only-file header //-
#pragma once

#include <QObject>
#include <QObjectComputedProperty>
#include <QQmlEngine>

//-only-file header 

//-only-file null
/*[[[cog
import cog
from MonitorPrivate import prptClass


cog.outl(prptClass.getClassHeader(),
        dedent=True, trimblanklines=True)

]]] */
//-only-file header
class MonitorPrivate : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isMonitored READ isMonitored WRITE setIsMonitored NOTIFY isMonitoredChanged )
    Q_PROPERTY(QStringList logItems READ logItems WRITE setLogItems NOTIFY logItemsChanged )
    Q_PROPERTY(int logLen READ logLen WRITE setLogLen NOTIFY logLenChanged )
    
    QML_ELEMENT
public:
    
    MonitorPrivate(QObject *parent = nullptr):QObject(parent){}

    virtual ~MonitorPrivate() {
        
    }

    
    
    bool isMonitored() const{return m_isMonitored;} 
    
void setIsMonitored(const bool newIsMonitored)
    {
        if (m_isMonitored == newIsMonitored)
            return;
        m_isMonitored = newIsMonitored;
        emit isMonitoredChanged();
    }


    
    QStringList logItems() const{return m_logItems;} 
    
void setLogItems(const QStringList &newLogItems)
    {
        if (m_logItems == newLogItems)
            return;
        m_logItems = newLogItems;
        emit logItemsChanged();
    }


    
    int logLen() const{return m_logLen;} 
    
void setLogLen(const int newLogLen)
    {
        if (m_logLen == newLogLen)
            return;
        m_logLen = newLogLen;
        emit logLenChanged();
    }


    
    
    
signals:
    void isMonitoredChanged();
    void logItemsChanged();
    void logLenChanged();
    

protected:
    

private:
    bool m_isMonitored;
    QStringList m_logItems;
    int m_logLen;
    
};
//-only-file null

//[[[end]]]
