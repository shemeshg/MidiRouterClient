//-define-file header genPrpt/FilterMidiDestinationPrivate.h
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
from FilterMidiDestinationPrivate import prptClass


cog.outl(prptClass.getClassHeader(),
        dedent=True, trimblanklines=True)

]]] */
//-only-file header
class FilterMidiDestinationPrivate : public MidiRoutersFilter
{
    Q_OBJECT
    Q_PROPERTY(QString baseMidiRouteInput READ baseMidiRouteInput WRITE setBaseMidiRouteInput NOTIFY baseMidiRouteInputChanged )
    
    QML_ELEMENT
public:
    
    FilterMidiDestinationPrivate(QObject *parent):MidiRoutersFilter(parent){}

    virtual ~FilterMidiDestinationPrivate() {
        
    }

    
    
    QString baseMidiRouteInput() const{return m_baseMidiRouteInput;} 
    
void setBaseMidiRouteInput(const QString &newBaseMidiRouteInput)
    {
        if (m_baseMidiRouteInput == newBaseMidiRouteInput)
            return;
        m_baseMidiRouteInput = newBaseMidiRouteInput;
        emit baseMidiRouteInputChanged();
    }


    
    
    
signals:
    void baseMidiRouteInputChanged();
    

protected:
    

private:
    QString m_baseMidiRouteInput ;
    
};
//-only-file null

//[[[end]]]
