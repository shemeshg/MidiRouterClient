//-define-file header genPrpt/FilterMidiDestinationPrivate.h
//-only-file header //-
#pragma once

//- #include "MidiRoutersFilter.h"
#include <QObject>
#include <QObjectComputedProperty>
#include <QQmlEngine>

//-only-file null
#include "MidiRoutersFilter.hpp"

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
    
    FilterMidiDestinationPrivate(QObject *parent = nullptr):MidiRoutersFilter(parent){}

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



    template<typename T>
    void clearList();
    
    template<typename T>
    void delListItem(int id);
    
    template<typename T>
    const QList<T> listItems();
    
    
    
signals:
    void baseMidiRouteInputChanged();
    

protected:
    

private:
    QString m_baseMidiRouteInput;
    
};
//-only-file null

//[[[end]]]
