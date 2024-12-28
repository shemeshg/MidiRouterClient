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


    
    
signals:
    void isMonitoredChanged();
    

protected:
    

private:
    bool m_isMonitored;
    
};
//-only-file null

//[[[end]]]
