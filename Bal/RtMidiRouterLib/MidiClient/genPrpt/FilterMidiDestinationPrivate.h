#pragma once

#include "MidiRoutersFilter.h"
#include <QObject>
#include <QObjectComputedProperty>
#include <QQmlEngine>

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


    
    
signals:
    void baseMidiRouteInputChanged();
    

protected:
    

private:
    QString m_baseMidiRouteInput;
    
};
