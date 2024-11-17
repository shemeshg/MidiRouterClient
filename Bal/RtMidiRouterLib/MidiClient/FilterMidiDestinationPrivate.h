#pragma once

#include "MidiRoutersFilter.h"
#include <QObject>
#include <QObjectComputedProperty>
#include <QQmlEngine>

/*[[[cog
import cog
from FilterMidiDestinationPrivate import classFilterMidiDestinationPrivate


cog.outl(classFilterMidiDestinationPrivate.getClassHeader(),
        dedent=True, trimblanklines=True)

]]] */
class FilterMidiDestinationPrivate : public MidiRoutersFilter
{
    Q_OBJECT
    Q_PROPERTY(QString baseMidiRouteInput READ baseMidiRouteInput WRITE setBaseMidiRouteInput NOTIFY baseMidiRouteInputChanged )
    Q_PROPERTY(FilterType filterType READ filterType WRITE setFilterType NOTIFY filterTypeChanged )
    
    QML_ELEMENT
public:
    FilterMidiDestinationPrivate(QObject *parent = nullptr);
    virtual ~FilterMidiDestinationPrivate() = default;

    
    
    QString baseMidiRouteInput() const{return m_baseMidiRouteInput;} 
    
void setBaseMidiRouteInput(const QString &newBaseMidiRouteInput)
    {
        if (m_baseMidiRouteInput == newBaseMidiRouteInput)
            return;
        m_baseMidiRouteInput = newBaseMidiRouteInput;
        emit baseMidiRouteInputChanged();
    }


    
    FilterType filterType() const{return m_filterType;} 
    
void setFilterType(const FilterType &newFilterType)
    {
        if (m_filterType == newFilterType)
            return;
        m_filterType = newFilterType;
        emit filterTypeChanged();
    }



signals:
    void baseMidiRouteInputChanged();
    void filterTypeChanged();
    

protected:
    

private:
    QString m_baseMidiRouteInput;
    FilterType m_filterType;
    
    void ctorClass();
};

//[[[end]]]
