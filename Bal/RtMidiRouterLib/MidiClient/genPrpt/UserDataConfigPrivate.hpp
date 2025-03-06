//-define-file header genPrpt/UserDataConfigPrivate.h
//-only-file header //-
#pragma once
#include <QObject>
#include <QObjectComputedProperty>
#include <QQmlEngine>
//- #include "Dropdownlist.h"
//- #include "../GenHpp/MidiRoutePreset.h"
//-only-file null
#include "../hpp/MidiRoutePreset.hpp"
#include "Dropdownlist.hpp"
//-only-file header 

//-only-file null
/*[[[cog
import cog
from UserDataConfigPrivate import prptClass


cog.outl(prptClass.getClassHeader(),
        dedent=True, trimblanklines=True)

]]] */
//-only-file header
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
    Q_PROPERTY(QString criticalErrorMsg READ criticalErrorMsg WRITE setCriticalErrorMsg NOTIFY criticalErrorMsgChanged )
    
    QML_ELEMENT
public:
    
    UserDataConfigPrivate(QObject *parent = nullptr):QObject(parent){}

    virtual ~UserDataConfigPrivate() {
        clearList<Dropdownlist *>();
    clearList<MidiRoutePreset *>();
    
    }

    
    
    int activePresetID() const{return m_activePresetID;} 
    
void setActivePresetID(const int newActivePresetID)
    {
        if (m_activePresetID == newActivePresetID)
            return;
        m_activePresetID = newActivePresetID;
        emit activePresetIDChanged();
    }


    
    QString computerUuid() const{return m_computerUuid;} 
    

    
    QList<Dropdownlist *> dropdownlists() const{return *m_dropdownlists;} 
    

    
    QString uniqueId() const{return m_uniqueId;} 
    

    
    QStringList virtualInPorts() const{return m_virtualInPorts;} 
    

    
    QList<MidiRoutePreset *> midiRoutePresets() const{return *m_midiRoutePresets;} 
    

    
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


    
    QString criticalErrorMsg() const{return m_criticalErrorMsg;} 
    
void setCriticalErrorMsg(const QString &newCriticalErrorMsg)
    {
        if (m_criticalErrorMsg == newCriticalErrorMsg)
            return;
        m_criticalErrorMsg = newCriticalErrorMsg;
        emit criticalErrorMsgChanged();
    }


    
    
        template<typename T = Dropdownlist *>
        std::enable_if_t<std::is_same_v<T, Dropdownlist *>, void>
        delListItem(int id){
            if (id < m_dropdownlists->size())
            {
                delete m_dropdownlists->at(id);
                m_dropdownlists->removeAt(id);
                emit dropdownlistsChanged();
            }
        }

        Dropdownlist * addListItem(Dropdownlist * item)
        {
            m_dropdownlists->push_back(item);
            emit dropdownlistsChanged();
            return item;
        }

        template<typename T = Dropdownlist * >
        std::enable_if_t<std::is_same_v<T, Dropdownlist * >, void>
        clearList(){
            qDeleteAll(*m_dropdownlists);
            m_dropdownlists->clear();
            emit dropdownlistsChanged();
        }

        template<typename T = Dropdownlist *>
        std::enable_if_t<std::is_same_v<T, Dropdownlist *>, const QList<Dropdownlist *>>
        listItems(){
            return *m_dropdownlists;
        }

        
        template<typename T = MidiRoutePreset *>
        std::enable_if_t<std::is_same_v<T, MidiRoutePreset *>, void>
        delListItem(int id){
            if (id < m_midiRoutePresets->size())
            {
                delete m_midiRoutePresets->at(id);
                m_midiRoutePresets->removeAt(id);
                emit midiRoutePresetsChanged();
            }
        }

        MidiRoutePreset * addListItem(MidiRoutePreset * item)
        {
            m_midiRoutePresets->push_back(item);
            emit midiRoutePresetsChanged();
            return item;
        }

        template<typename T = MidiRoutePreset * >
        std::enable_if_t<std::is_same_v<T, MidiRoutePreset * >, void>
        clearList(){
            qDeleteAll(*m_midiRoutePresets);
            m_midiRoutePresets->clear();
            emit midiRoutePresetsChanged();
        }

        template<typename T = MidiRoutePreset *>
        std::enable_if_t<std::is_same_v<T, MidiRoutePreset *>, const QList<MidiRoutePreset *>>
        listItems(){
            return *m_midiRoutePresets;
        }

        
    
signals:
    void activePresetIDChanged();
    void dropdownlistsChanged();
    void uniqueIdChanged();
    void virtualInPortsChanged();
    void midiRoutePresetsChanged();
    void connectedInPortsChanged();
    void connectedOutPortsChanged();
    void criticalErrorMsgChanged();
    

protected:
    QString m_computerUuid ;
    QList<Dropdownlist *> *m_dropdownlists = new QList<Dropdownlist *>();
    QString m_uniqueId ;
    QStringList m_virtualInPorts = {};
    QList<MidiRoutePreset *> *m_midiRoutePresets = new QList<MidiRoutePreset *>();
    

private:
    int m_activePresetID = 0;
    QStringList m_connectedInPorts = {};
    QStringList m_connectedOutPorts = {};
    QString m_criticalErrorMsg ;
    
};
//-only-file null

//[[[end]]]
