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
    Q_PROPERTY(QString computerUuid READ computerUuid WRITE setComputerUuid NOTIFY computerUuidChanged )
    Q_PROPERTY(bool isSendAllUserControls READ isSendAllUserControls WRITE setIsSendAllUserControls NOTIFY isSendAllUserControlsChanged )
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
    

    
    QList<UserControl *> userControls() const{return m_userControls;} 
    

    
    QList<MidiRouteInput *> midiRouteInputs() const{return m_midiRouteInputs;} 
    


    template<typename T>
    void clearList();
    
    template<typename T>
    void delListItem(int id);
    
    template<typename T>
    const QList<T> listItems();
    
    
        template<>
        void delListItem<UserControl *>(int id){
            if (id < m_userControls.size())
            {
                delete m_userControls.at(id);
                m_userControls.removeAt(id);
                emit userControlsChanged();
            }
        }
        
        void addListItem(UserControl * item)
        {
            m_userControls.push_back(item);
            emit userControlsChanged();
        }
        
        template<>
        void clearList<UserControl *>(){
            qDeleteAll(m_userControls);
            m_userControls.clear();
            emit userControlsChanged();
        }   

        template<>
        const QList<UserControl *> listItems<UserControl *>(){
            return m_userControls;
        }

        
        template<>
        void delListItem<MidiRouteInput *>(int id){
            if (id < m_midiRouteInputs.size())
            {
                delete m_midiRouteInputs.at(id);
                m_midiRouteInputs.removeAt(id);
                emit midiRouteInputsChanged();
            }
        }
        
        void addListItem(MidiRouteInput * item)
        {
            m_midiRouteInputs.push_back(item);
            emit midiRouteInputsChanged();
        }
        
        template<>
        void clearList<MidiRouteInput *>(){
            qDeleteAll(m_midiRouteInputs);
            m_midiRouteInputs.clear();
            emit midiRouteInputsChanged();
        }   

        template<>
        const QList<MidiRouteInput *> listItems<MidiRouteInput *>(){
            return m_midiRouteInputs;
        }

        
    
signals:
    void nameChanged();
    void uuidChanged();
    void computerUuidChanged();
    void isSendAllUserControlsChanged();
    void isEnabledChanged();
    void midiControlOnChanged();
    void midiControlOffChanged();
    void userControlsChanged();
    void midiRouteInputsChanged();
    

protected:
    PresetMidiControl * m_midiControlOn;
    PresetMidiControl * m_midiControlOff;
    QList<UserControl *> m_userControls;
    QList<MidiRouteInput *> m_midiRouteInputs;
    

private:
    QString m_name;
    QString m_uuid;
    QString m_computerUuid;
    bool m_isSendAllUserControls;
    bool m_isEnabled;
    
};
//-only-file null

//[[[end]]]
