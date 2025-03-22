//-define-file header genPrpt/MidiRoutePresetPrivate.h
//-only-file header //-
#pragma once

#include <QObject>
#include <QObjectComputedProperty>
#include <QQmlEngine>


//- {include-header}
#include "../hpp/MidiRouteInput.hpp" //- #include "../GenHpp/MidiRouteInput.h"
//- {include-header}
#include "../hpp/PresetMidiControl.hpp" //- #include "../GenHpp/PresetMidiControl.h"
//- {include-header}
#include "../hpp/UserControl.hpp" //- #include "../GenHpp/UserControl.h"


//-only-file null
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
    Q_PROPERTY(QString uuidPrivate READ uuidPrivate WRITE setUuidPrivate NOTIFY uuidPrivateChanged )
    Q_PROPERTY(bool isEnabled READ isEnabled WRITE setIsEnabled NOTIFY isEnabledChanged )
    Q_PROPERTY(PresetMidiControl * midiControlOn READ midiControlOn  NOTIFY midiControlOnChanged )
    Q_PROPERTY(PresetMidiControl * midiControlOff READ midiControlOff  NOTIFY midiControlOffChanged )
    Q_PROPERTY(PresetMidiControl * midiControlToggle READ midiControlToggle  NOTIFY midiControlToggleChanged )
    Q_PROPERTY(PresetMidiControl * midiControlSelect READ midiControlSelect  NOTIFY midiControlSelectChanged )
    Q_PROPERTY(QList<UserControl *> userControls READ userControls  NOTIFY userControlsChanged )
    Q_PROPERTY(QList<MidiRouteInput *> midiRouteInputs READ midiRouteInputs  NOTIFY midiRouteInputsChanged )
    
    QML_ELEMENT
public:
    
    MidiRoutePresetPrivate(QObject *parent):QObject(parent){}

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


    
    QString uuidPrivate() const{return m_uuidPrivate;} 
    
void setUuidPrivate(const QString &newUuidPrivate)
    {
        if (m_uuidPrivate == newUuidPrivate)
            return;
        m_uuidPrivate = newUuidPrivate;
        emit uuidPrivateChanged();
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
    

    
    PresetMidiControl * midiControlToggle() const{return m_midiControlToggle;} 
    

    
    PresetMidiControl * midiControlSelect() const{return m_midiControlSelect;} 
    

    
    QList<UserControl *> userControls() const{return *m_userControls;} 
    

    
    QList<MidiRouteInput *> midiRouteInputs() const{return *m_midiRouteInputs;} 
    

    
    
        template<typename T = UserControl *>
        std::enable_if_t<std::is_same_v<T, UserControl *>, void>
        delListItem(int id){
            if (id < m_userControls->size())
            {
                delete m_userControls->at(id);
                m_userControls->removeAt(id);
                emit userControlsChanged();
            }
        }

        UserControl * addListItem(UserControl * item)
        {
            m_userControls->push_back(item);
            emit userControlsChanged();
            return item;
        }

        template<typename T = UserControl * >
        std::enable_if_t<std::is_same_v<T, UserControl * >, UserControl * >
        addNewListItem()
        {
            auto item = new UserControl (this);
            m_userControls->push_back(item);
            emit userControlsChanged();
            return item;
        }

        template<typename T = UserControl * >
        std::enable_if_t<std::is_same_v<T, UserControl * >, void>
        clearList(){
            qDeleteAll(*m_userControls);
            m_userControls->clear();
            emit userControlsChanged();
        }

        template<typename T = UserControl *>
        std::enable_if_t<std::is_same_v<T, UserControl *>, const QList<UserControl *>>
        listItems(){
            return *m_userControls;
        }

        
        template<typename T = MidiRouteInput *>
        std::enable_if_t<std::is_same_v<T, MidiRouteInput *>, void>
        delListItem(int id){
            if (id < m_midiRouteInputs->size())
            {
                delete m_midiRouteInputs->at(id);
                m_midiRouteInputs->removeAt(id);
                emit midiRouteInputsChanged();
            }
        }

        MidiRouteInput * addListItem(MidiRouteInput * item)
        {
            m_midiRouteInputs->push_back(item);
            emit midiRouteInputsChanged();
            return item;
        }

        template<typename T = MidiRouteInput * >
        std::enable_if_t<std::is_same_v<T, MidiRouteInput * >, MidiRouteInput * >
        addNewListItem()
        {
            auto item = new MidiRouteInput (this);
            m_midiRouteInputs->push_back(item);
            emit midiRouteInputsChanged();
            return item;
        }

        template<typename T = MidiRouteInput * >
        std::enable_if_t<std::is_same_v<T, MidiRouteInput * >, void>
        clearList(){
            qDeleteAll(*m_midiRouteInputs);
            m_midiRouteInputs->clear();
            emit midiRouteInputsChanged();
        }

        template<typename T = MidiRouteInput *>
        std::enable_if_t<std::is_same_v<T, MidiRouteInput *>, const QList<MidiRouteInput *>>
        listItems(){
            return *m_midiRouteInputs;
        }

        
    
signals:
    void nameChanged();
    void uuidPrivateChanged();
    void isEnabledChanged();
    void midiControlOnChanged();
    void midiControlOffChanged();
    void midiControlToggleChanged();
    void midiControlSelectChanged();
    void userControlsChanged();
    void midiRouteInputsChanged();
    

protected:
    PresetMidiControl * m_midiControlOn = new PresetMidiControl(PresetMidiControl::PresetMidiType::PRESET_ON,this);
    PresetMidiControl * m_midiControlOff = new PresetMidiControl(PresetMidiControl::PresetMidiType::PRESET_OFF,this);
    PresetMidiControl * m_midiControlToggle = new PresetMidiControl(PresetMidiControl::PresetMidiType::PRESET_TOGGLE,this);
    PresetMidiControl * m_midiControlSelect = new PresetMidiControl(PresetMidiControl::PresetMidiType::PRESET_SELECT,this);
    QList<UserControl *> *m_userControls = new QList<UserControl *>();
    QList<MidiRouteInput *> *m_midiRouteInputs = new QList<MidiRouteInput *>();
    

private:
    QString m_name ;
    QString m_uuidPrivate ;
    bool m_isEnabled = false;
    
};
//-only-file null

//[[[end]]]
