//-define-file header genPrpt/MidiRoutePresetPrivate.h
//-only-file header //-
#pragma once

#include <QObject>
#include <QObjectComputedProperty>
#include <QQmlEngine>

//- #include "../GenHpp/EasyConfig.h"
//- #include "../GenHpp/MidiRouteInput.h"
//- #include "../GenHpp/PresetMidiControl.h"
//- #include "../GenHpp/UserControl.h"
//-only-file null
#include "../hpp/EasyConfig.hpp"
#include "../hpp/MidiRouteInput.hpp"
#include "../hpp/PresetMidiControl.hpp"
#include "../hpp/UserControl.hpp"


/*[[[cog
import cog
from MidiRoutePresetPrivate import prptClass


cog.outl(prptClass.getClassHeader(),
        dedent=True, trimblanklines=True)

]]] */
//-only-file header
class MidiRoutePresetPrivate : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged )
    Q_PROPERTY(QString uuid READ uuid WRITE setUuid NOTIFY uuidChanged )
    Q_PROPERTY(bool isEnabled READ isEnabled WRITE setIsEnabled NOTIFY isEnabledChanged )
    Q_PROPERTY(PresetMidiControl * midiControlOn READ midiControlOn  NOTIFY midiControlOnChanged )
    Q_PROPERTY(PresetMidiControl * midiControlOff READ midiControlOff  NOTIFY midiControlOffChanged )
    Q_PROPERTY(QList<UserControl *> userControls READ userControls  NOTIFY userControlsChanged )
    Q_PROPERTY(QList<MidiRouteInput *> midiRouteInputs READ midiRouteInputs  NOTIFY midiRouteInputsChanged )
    
    QML_ELEMENT
public:
    
    MidiRoutePresetPrivate(QObject *parent = nullptr):QObject(parent){}

    virtual ~MidiRoutePresetPrivate() {
        clearList<UserControl *>();
    clearList<MidiRouteInput *>();
    
    }

    
    
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
    

    
    QList<UserControl *> userControls() const{return m_userControls;} 
    

    
    QList<MidiRouteInput *> midiRouteInputs() const{return m_midiRouteInputs;} 
    

    
    
        template<typename T = UserControl *>
        std::enable_if_t<std::is_same_v<T, UserControl *>, void>
        delListItem(int id){
            if (id < m_userControls.size())
            {
                delete m_userControls.at(id);
                m_userControls.removeAt(id);
                emit userControlsChanged();
            }
        }

        UserControl * addListItem(UserControl * item)
        {
            m_userControls.push_back(item);
            emit userControlsChanged();
            return item;
        }

        template<typename T = UserControl * >
        std::enable_if_t<std::is_same_v<T, UserControl * >, void>
        clearList(){
            qDeleteAll(m_userControls);
            m_userControls.clear();
            emit userControlsChanged();
        }

        template<typename T = UserControl *>
        std::enable_if_t<std::is_same_v<T, UserControl *>, const QList<UserControl *>>
        listItems(){
            return m_userControls;
        }

        
        template<typename T = MidiRouteInput *>
        std::enable_if_t<std::is_same_v<T, MidiRouteInput *>, void>
        delListItem(int id){
            if (id < m_midiRouteInputs.size())
            {
                delete m_midiRouteInputs.at(id);
                m_midiRouteInputs.removeAt(id);
                emit midiRouteInputsChanged();
            }
        }

        MidiRouteInput * addListItem(MidiRouteInput * item)
        {
            m_midiRouteInputs.push_back(item);
            emit midiRouteInputsChanged();
            return item;
        }

        template<typename T = MidiRouteInput * >
        std::enable_if_t<std::is_same_v<T, MidiRouteInput * >, void>
        clearList(){
            qDeleteAll(m_midiRouteInputs);
            m_midiRouteInputs.clear();
            emit midiRouteInputsChanged();
        }

        template<typename T = MidiRouteInput *>
        std::enable_if_t<std::is_same_v<T, MidiRouteInput *>, const QList<MidiRouteInput *>>
        listItems(){
            return m_midiRouteInputs;
        }

        
    
signals:
    void nameChanged();
    void uuidChanged();
    void isEnabledChanged();
    void midiControlOnChanged();
    void midiControlOffChanged();
    void userControlsChanged();
    void midiRouteInputsChanged();
    

protected:
    PresetMidiControl * m_midiControlOn = new PresetMidiControl(PresetMidiControl::PresetMidiType::PRESET_ON,this);
    PresetMidiControl * m_midiControlOff = new PresetMidiControl(PresetMidiControl::PresetMidiType::PRESET_OFF,this);
    QList<UserControl *> m_userControls = {};
    QList<MidiRouteInput *> m_midiRouteInputs = {};
    

private:
    QString m_name ;
    QString m_uuid ;
    bool m_isEnabled = false;
    
};
//-only-file null

//[[[end]]]
