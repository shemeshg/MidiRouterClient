#pragma once

#include <QObject>
#include <QObjectComputedProperty>
#include <QQmlEngine>

#include "Dropdownlist.h"
#include "MidiRoutePreset.h"
/*[[[cog
import cog
from UserDataConfigPrivate import classUserDataConfigPrivate


cog.outl(classUserDataConfigPrivate.getClassHeader(),
        dedent=True, trimblanklines=True)

]]] */
class UserDataConfigPrivate : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int activePresetID READ activePresetID WRITE setActivePresetID NOTIFY activePresetIDChanged )
    Q_PROPERTY(QString computerUuid READ computerUuid  CONSTANT )
    Q_PROPERTY(QList<Dropdownlist *> dropdownlists READ dropdownlists  NOTIFY dropdownlistsChanged )
    Q_PROPERTY(QString uniqueId READ uniqueId  NOTIFY uniqueIdChanged )
    Q_PROPERTY(QStringList virtualInPorts READ virtualInPorts  NOTIFY virtualInPortsChanged )
    Q_PROPERTY(QList<MidiRoutePreset *> midiRoutePresets READ midiRoutePresets  NOTIFY midiRoutePresetsChanged )
    Q_PROPERTY(QStringList connectedInPorts READ connectedInPorts WRITE setConnectedInPorts NOTIFY connectedInPortsChanged )
    Q_PROPERTY(QStringList connectedOutPorts READ connectedOutPorts WRITE setConnectedOutPorts NOTIFY connectedOutPortsChanged )
    Q_PROPERTY(MidiRoutePreset * activePreset READ activePreset  NOTIFY activePresetChanged )
    
    QML_ELEMENT
public:
    UserDataConfigPrivate(QObject *parent = nullptr);
    virtual ~UserDataConfigPrivate() = default;

    
    
    int activePresetID() const{return m_activePresetID;} 
    
void setActivePresetID(const int newActivePresetID)
    {
        if (m_activePresetID == newActivePresetID)
            return;
        m_activePresetID = newActivePresetID;
        emit activePresetIDChanged();
    }


    
    QString computerUuid() const{return m_computerUuid;} 
    

    
    QList<Dropdownlist *> dropdownlists() const{return m_dropdownlists;} 
    

    
    QString uniqueId() const{return m_uniqueId;} 
    

    
    QStringList virtualInPorts() const{return m_virtualInPorts;} 
    

    
    QList<MidiRoutePreset *> midiRoutePresets() const{return m_midiRoutePresets;} 
    

    
    QStringList connectedInPorts() const{return m_connectedInPorts;} 
    
void setConnectedInPorts(const QStringList &newConnectedInPorts)
    {
        if (m_connectedInPorts == newConnectedInPorts)
            return;
        m_connectedInPorts = newConnectedInPorts;
        emit connectedInPortsChanged();
    }


    
    QStringList connectedOutPorts() const{return m_connectedOutPorts;} 
    
void setConnectedOutPorts(const QStringList &newConnectedOutPorts)
    {
        if (m_connectedOutPorts == newConnectedOutPorts)
            return;
        m_connectedOutPorts = newConnectedOutPorts;
        emit connectedOutPortsChanged();
    }


    
    MidiRoutePreset * activePreset() const{return m_activePreset;} 
    


signals:
    void activePresetIDChanged();
    void dropdownlistsChanged();
    void uniqueIdChanged();
    void virtualInPortsChanged();
    void midiRoutePresetsChanged();
    void connectedInPortsChanged();
    void connectedOutPortsChanged();
    void activePresetChanged();
    

protected:
    QString m_computerUuid;
    QList<Dropdownlist *> m_dropdownlists;
    QString m_uniqueId;
    QStringList m_virtualInPorts;
    QList<MidiRoutePreset *> m_midiRoutePresets;
    MidiRoutePreset * m_activePreset;
    

private:
    int m_activePresetID;
    QStringList m_connectedInPorts;
    QStringList m_connectedOutPorts;
    
    void ctorClass();
};

//[[[end]]]
