#pragma once

#include "MidiRoutersFilter.h"
#include <QObject>
#include <QObjectComputedProperty>
#include <QQmlEngine>

/*[[[cog
import cog
from FilterToConslePrivate import classFilterToConslePrivate


cog.outl(classFilterToConslePrivate.getClassHeader(),
        dedent=True, trimblanklines=True)

]]] */
class FilterToConslePrivate : public MidiRoutersFilter
{
    Q_OBJECT
    Q_PROPERTY(LogTo logTo READ logTo WRITE setLogTo NOTIFY logToChanged )
    Q_PROPERTY(QString userdata READ userdata WRITE setUserdata NOTIFY userdataChanged )
    
    QML_ELEMENT
public:
    FilterToConslePrivate(QObject *parent = nullptr);
    virtual ~FilterToConslePrivate() = default;

    
enum class LogTo {
        CLIENT, SERVER
    };
Q_ENUM(LogTo)

    
    LogTo logTo() const{return m_logTo;} 
    
void setLogTo(const LogTo &newLogTo)
    {
        if (m_logTo == newLogTo)
            return;
        m_logTo = newLogTo;
        emit logToChanged();
    }


    
    QString userdata() const{return m_userdata;} 
    
void setUserdata(const QString &newUserdata)
    {
        if (m_userdata == newUserdata)
            return;
        m_userdata = newUserdata;
        emit userdataChanged();
    }



signals:
    void logToChanged();
    void userdataChanged();
    

protected:
    

private:
    LogTo m_logTo;
    QString m_userdata;
    
    void ctorClass();
};

//[[[end]]]
