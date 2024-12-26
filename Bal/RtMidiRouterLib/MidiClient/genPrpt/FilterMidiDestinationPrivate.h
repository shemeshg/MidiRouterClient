#pragma once

#include "MidiRoutersFilter.h"
#include <QObject>
#include <QObjectComputedProperty>
#include <QQmlEngine>

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
        FilterMidiDestinationPrivate(QObject *parent = nullptr);

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
    void ctorClass(); 
QString m_baseMidiRouteInput;
    
};
//-only-file null

//[[[end]]]
