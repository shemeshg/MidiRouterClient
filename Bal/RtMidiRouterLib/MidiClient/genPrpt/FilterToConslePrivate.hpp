//-define-file header genPrpt/FilterToConslePrivate.h
//-only-file header //-
#pragma once

#include <QObject>
#include <QObjectComputedProperty>
#include <QQmlEngine>

//- {include-header}
#include "MidiRoutersFilter.hpp" //- #include "MidiRoutersFilter.h"

//-only-file null
/*[[[cog
import cog
from FilterToConslePrivate import prptClass


cog.outl(prptClass.getClassHeader(),
        dedent=True, trimblanklines=True)

]]] */
//-only-file header
class FilterToConslePrivate : public MidiRoutersFilter
{
    Q_OBJECT
    Q_PROPERTY(LogTo logTo READ logTo WRITE setLogTo NOTIFY logToChanged )
    Q_PROPERTY(QString userdata READ userdata WRITE setUserdata NOTIFY userdataChanged )
    
    QML_ELEMENT
public:
    
    FilterToConslePrivate(QObject *parent):MidiRoutersFilter(parent){}

    virtual ~FilterToConslePrivate() {
        
    }

    
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
    LogTo m_logTo = LogTo::CLIENT;
    QString m_userdata ;
    
};
//-only-file null

//[[[end]]]
