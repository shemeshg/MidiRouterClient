#pragma once

#include <QObject>
#include <QObjectComputedProperty>
#include <QQmlEngine>


/*[[[cog
import cog
from MonitorPrivate import classMonitorPrivate


cog.outl(classMonitorPrivate.getClassHeader(),
        dedent=True, trimblanklines=True)

]]] */
class MonitorPrivate : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isMonitored READ isMonitored WRITE setIsMonitored NOTIFY isMonitoredChanged )
    
    QML_ELEMENT
public:
    MonitorPrivate(QObject *parent = nullptr);
    virtual ~MonitorPrivate() = default;

    
    
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
    
    void ctorClass();
};

//[[[end]]]
