#pragma once

#include <QObject>
#include <QObjectComputedProperty>
#include <QQmlEngine>
#include "EasyConfig.h"
#include "MidiRouteInput.h"
#include "PresetMidiControl.h"
#include "UserControl.h"

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
    Q_PROPERTY(bool isEnabled READ isEnabled WRITE setIsEnabled NOTIFY isEnabledChanged )
    Q_PROPERTY(PresetMidiControl * midiControlOn READ midiControlOn  NOTIFY midiControlOnChanged )
    Q_PROPERTY(PresetMidiControl * midiControlOff READ midiControlOff  NOTIFY midiControlOffChanged )
    Q_PROPERTY(QList<EasyConfig *> easyConfig READ easyConfig  NOTIFY easyConfigChanged )
    Q_PROPERTY(QList<UserControl *> userControls READ userControls  NOTIFY userControlsChanged )
    Q_PROPERTY(QList<MidiRouteInput *> midiRouteInputs READ midiRouteInputs  NOTIFY midiRouteInputsChanged )
    
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


    
    bool isEnabled() const{return m_isEnabled;} 
    
void setIsEnabled(const bool newIsEnabled)
    {
        if (m_isEnabled == newIsEnabled)
            return;
        m_isEnabled = newIsEnabled;
        emit isEnabledChanged();
    }


    
    PresetMidiControl * midiControlOn() const{return m_midiControlOn;} 
    

    
    PresetMidiControl * midiControlOff() const{return m_midiControlOff;} 
    

    
    QList<EasyConfig *> easyConfig() const{return m_easyConfig;} 
    

    
    QList<UserControl *> userControls() const{return m_userControls;} 
    

    
    QList<MidiRouteInput *> midiRouteInputs() const{return m_midiRouteInputs;} 
    


signals:
    void nameChanged();
    void uuidChanged();
    void computerUuidChanged();
    void isSendAllUserControlsChanged();
    void isEnabledChanged();
    void midiControlOnChanged();
    void midiControlOffChanged();
    void easyConfigChanged();
    void userControlsChanged();
    void midiRouteInputsChanged();
    

protected:
    PresetMidiControl * m_midiControlOn;
    PresetMidiControl * m_midiControlOff;
    QList<EasyConfig *> m_easyConfig;
    QList<UserControl *> m_userControls;
    QList<MidiRouteInput *> m_midiRouteInputs;
    

private:
    QString m_name;
    QString m_uuid;
    QString m_computerUuid;
    bool m_isSendAllUserControls;
    bool m_isEnabled;
    
    void ctorClass();
};

//[[[end]]]
