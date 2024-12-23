#pragma once


#include "MidiRoutersFilter.h"
#include <QObject>
#include <QObjectComputedProperty>
#include <QQmlEngine>

/*[[[cog
import cog
from FilterSchedulePrivate import classFilterSchedulePrivate


cog.outl(classFilterSchedulePrivate.getClassHeader(),
        dedent=True, trimblanklines=True)

]]] */
class FilterSchedulePrivate : public MidiRoutersFilter
{
    Q_OBJECT
    Q_PROPERTY(DefferedType defferedType READ defferedType WRITE setDefferedType NOTIFY defferedTypeChanged )
    Q_PROPERTY(int defferedTo READ defferedTo WRITE setDefferedTo NOTIFY defferedToChanged )
    
    QML_ELEMENT
public:
    FilterSchedulePrivate(QObject *parent = nullptr);
    virtual ~FilterSchedulePrivate() = default;

    
enum class DefferedType {
        IN_SPP, IN_BAR, AT_SPP_AT_BAR, QUANTIZE_SPP, QUANTIZE_BAR
    };
Q_ENUM(DefferedType)

    
    DefferedType defferedType() const{return m_defferedType;} 
    
void setDefferedType(const DefferedType &newDefferedType)
    {
        if (m_defferedType == newDefferedType)
            return;
        m_defferedType = newDefferedType;
        emit defferedTypeChanged();
    }


    
    int defferedTo() const{return m_defferedTo;} 
    
void setDefferedTo(const int newDefferedTo)
    {
        if (m_defferedTo == newDefferedTo)
            return;
        m_defferedTo = newDefferedTo;
        emit defferedToChanged();
    }


    
    
signals:
    void defferedTypeChanged();
    void defferedToChanged();
    

protected:
    

private:
    DefferedType m_defferedType;
    int m_defferedTo;
    
    void ctorClass();
};

//[[[end]]]
