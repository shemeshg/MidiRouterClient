#pragma once

#include <QObject>
#include <QObjectComputedProperty>
#include <QQmlEngine>
#include "PresetMidiControl.h"

/*[[[cog
import cog
from MidiRoutePresetPrivate import classMidiRoutePresetPrivate


cog.outl(classMidiRoutePresetPrivate.getClassHeader(),
        dedent=True, trimblanklines=True)

]]] */
class MidiRoutePresetPrivate : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged )
    Q_PROPERTY(QString uuid READ uuid WRITE setUuid NOTIFY uuidChanged )
    Q_PROPERTY(QString computerUuid READ computerUuid WRITE setComputerUuid NOTIFY computerUuidChanged )
    Q_PROPERTY(bool isSendAllUserControls READ isSendAllUserControls WRITE setIsSendAllUserControls NOTIFY isSendAllUserControlsChanged )
    Q_PROPERTY(PresetMidiControl * midiControlOn READ midiControlOn  NOTIFY midiControlOnChanged )
    Q_PROPERTY(PresetMidiControl * midiControlOff READ midiControlOff  NOTIFY midiControlOffChanged )
    
    QML_ELEMENT
public:
    MidiRoutePresetPrivate(QObject *parent = nullptr);
    virtual ~MidiRoutePresetPrivate() = default;

    
    
    QString name() const{return m_name;} 
    
void setName(const QString &newName)
    {
        if (m_name == newName)
            return;
        m_name = newName;
        emit nameChanged();
    }


    
    QString uuid() const{return m_uuid;} 
    
void setUuid(const QString &newUuid)
    {
        if (m_uuid == newUuid)
            return;
        m_uuid = newUuid;
        emit uuidChanged();
    }


    
    QString computerUuid() const{return m_computerUuid;} 
    
void setComputerUuid(const QString &newComputerUuid)
    {
        if (m_computerUuid == newComputerUuid)
            return;
        m_computerUuid = newComputerUuid;
        emit computerUuidChanged();
    }


    
    bool isSendAllUserControls() const{return m_isSendAllUserControls;} 
    
void setIsSendAllUserControls(const bool newIsSendAllUserControls)
    {
        if (m_isSendAllUserControls == newIsSendAllUserControls)
            return;
        m_isSendAllUserControls = newIsSendAllUserControls;
        emit isSendAllUserControlsChanged();
    }


    
    PresetMidiControl * midiControlOn() const{return m_midiControlOn;} 
    

    
    PresetMidiControl * midiControlOff() const{return m_midiControlOff;} 
    


signals:
    void nameChanged();
    void uuidChanged();
    void computerUuidChanged();
    void isSendAllUserControlsChanged();
    void midiControlOnChanged();
    void midiControlOffChanged();
    

protected:
    PresetMidiControl * m_midiControlOn;
    PresetMidiControl * m_midiControlOff;
    

private:
    QString m_name;
    QString m_uuid;
    QString m_computerUuid;
    bool m_isSendAllUserControls;
    
    void ctorClass();
};

//[[[end]]]
