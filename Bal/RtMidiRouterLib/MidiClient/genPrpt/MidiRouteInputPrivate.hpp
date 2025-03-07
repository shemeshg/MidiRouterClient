//-define-file header genPrpt/MidiRouteInputPrivate.h
//-only-file header //-
#pragma once

#include <QObject>
#include <QObjectComputedProperty>
#include <QQmlEngine>

//- {include-header}
#include "MidiRouteInputCc14bit.hpp" //- #include "MidiRouteInputCc14bit.h"
//- {include-header}
#include "../hpp/MidiRouterChain.hpp" //- #include "../GenHpp/MidiRouterChain.h"
//- {include-header}
#include "../hpp/Monitor.hpp" //- #include "../GenHpp/Monitor.h"

//-only-file null
/*[[[cog
import cog
from MidiRouteInputPrivate import prptClass


cog.outl(prptClass.getClassHeader(),
        dedent=True, trimblanklines=True)

]]] */
//-only-file header
class MidiRouteInputPrivate : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString uuid READ uuid WRITE setUuid NOTIFY uuidChanged )
    Q_PROPERTY(QString midiInputName READ midiInputName WRITE setMidiInputName NOTIFY midiInputNameChanged )
    Q_PROPERTY(bool ignoreTypesMidiSysex READ ignoreTypesMidiSysex WRITE setIgnoreTypesMidiSysex NOTIFY ignoreTypesMidiSysexChanged )
    Q_PROPERTY(bool ignoreTypesMidiTime READ ignoreTypesMidiTime WRITE setIgnoreTypesMidiTime NOTIFY ignoreTypesMidiTimeChanged )
    Q_PROPERTY(bool ignoreTypesMidiSense READ ignoreTypesMidiSense WRITE setIgnoreTypesMidiSense NOTIFY ignoreTypesMidiSenseChanged )
    Q_PROPERTY(int midiRouteClockTimeSig READ midiRouteClockTimeSig WRITE setMidiRouteClockTimeSig NOTIFY midiRouteClockTimeSigChanged )
    Q_PROPERTY(int midiRouteClockTimeSigDivBy READ midiRouteClockTimeSigDivBy WRITE setMidiRouteClockTimeSigDivBy NOTIFY midiRouteClockTimeSigDivByChanged )
    Q_PROPERTY(int midiRouteClockFromSppPos READ midiRouteClockFromSppPos WRITE setMidiRouteClockFromSppPos NOTIFY midiRouteClockFromSppPosChanged )
    Q_PROPERTY(QStringList midiRouteClockPropegateInputs READ midiRouteClockPropegateInputs WRITE setMidiRouteClockPropegateInputs NOTIFY midiRouteClockPropegateInputsChanged )
    Q_PROPERTY(QList<MidiRouteInputCc14bit *> midiRouteInputCc14bit READ midiRouteInputCc14bit  NOTIFY midiRouteInputCc14bitChanged )
    Q_PROPERTY(QList<MidiRouterChain *> midiRouterChains READ midiRouterChains  NOTIFY midiRouterChainsChanged )
    Q_PROPERTY(Monitor * monitor READ monitor  NOTIFY monitorChanged )
    Q_PROPERTY(EasyConfig * easyConfig READ easyConfig  NOTIFY easyConfigChanged )
    
    QML_ELEMENT
public:
    
    MidiRouteInputPrivate(QObject *parent = nullptr):QObject(parent){}

    virtual ~MidiRouteInputPrivate() {
        clearList<MidiRouteInputCc14bit *>();
    clearList<MidiRouterChain *>();
    
    }

    
    
    QString uuid() const{return m_uuid;} 
    
void setUuid(const QString &newUuid)
    {
        if (m_uuid == newUuid)
            return;
        m_uuid = newUuid;
        emit uuidChanged();
    }


    
    QString midiInputName() const{return m_midiInputName;} 
    
void setMidiInputName(const QString &newMidiInputName)
    {
        if (m_midiInputName == newMidiInputName)
            return;
        m_midiInputName = newMidiInputName;
        emit midiInputNameChanged();
    }


    
    bool ignoreTypesMidiSysex() const{return m_ignoreTypesMidiSysex;} 
    
void setIgnoreTypesMidiSysex(const bool newIgnoreTypesMidiSysex)
    {
        if (m_ignoreTypesMidiSysex == newIgnoreTypesMidiSysex)
            return;
        m_ignoreTypesMidiSysex = newIgnoreTypesMidiSysex;
        emit ignoreTypesMidiSysexChanged();
    }


    
    bool ignoreTypesMidiTime() const{return m_ignoreTypesMidiTime;} 
    
void setIgnoreTypesMidiTime(const bool newIgnoreTypesMidiTime)
    {
        if (m_ignoreTypesMidiTime == newIgnoreTypesMidiTime)
            return;
        m_ignoreTypesMidiTime = newIgnoreTypesMidiTime;
        emit ignoreTypesMidiTimeChanged();
    }


    
    bool ignoreTypesMidiSense() const{return m_ignoreTypesMidiSense;} 
    
void setIgnoreTypesMidiSense(const bool newIgnoreTypesMidiSense)
    {
        if (m_ignoreTypesMidiSense == newIgnoreTypesMidiSense)
            return;
        m_ignoreTypesMidiSense = newIgnoreTypesMidiSense;
        emit ignoreTypesMidiSenseChanged();
    }


    
    int midiRouteClockTimeSig() const{return m_midiRouteClockTimeSig;} 
    
void setMidiRouteClockTimeSig(const int newMidiRouteClockTimeSig)
    {
        if (m_midiRouteClockTimeSig == newMidiRouteClockTimeSig)
            return;
        m_midiRouteClockTimeSig = newMidiRouteClockTimeSig;
        emit midiRouteClockTimeSigChanged();
    }


    
    int midiRouteClockTimeSigDivBy() const{return m_midiRouteClockTimeSigDivBy;} 
    
void setMidiRouteClockTimeSigDivBy(const int newMidiRouteClockTimeSigDivBy)
    {
        if (m_midiRouteClockTimeSigDivBy == newMidiRouteClockTimeSigDivBy)
            return;
        m_midiRouteClockTimeSigDivBy = newMidiRouteClockTimeSigDivBy;
        emit midiRouteClockTimeSigDivByChanged();
    }


    
    int midiRouteClockFromSppPos() const{return m_midiRouteClockFromSppPos;} 
    
void setMidiRouteClockFromSppPos(const int newMidiRouteClockFromSppPos)
    {
        if (m_midiRouteClockFromSppPos == newMidiRouteClockFromSppPos)
            return;
        m_midiRouteClockFromSppPos = newMidiRouteClockFromSppPos;
        emit midiRouteClockFromSppPosChanged();
    }


    
    QStringList midiRouteClockPropegateInputs() const{return m_midiRouteClockPropegateInputs;} 
    
void setMidiRouteClockPropegateInputs(const QStringList &newMidiRouteClockPropegateInputs)
    {
        if (m_midiRouteClockPropegateInputs == newMidiRouteClockPropegateInputs)
            return;
        m_midiRouteClockPropegateInputs = newMidiRouteClockPropegateInputs;
        emit midiRouteClockPropegateInputsChanged();
    }


    
    QList<MidiRouteInputCc14bit *> midiRouteInputCc14bit() const{return *m_midiRouteInputCc14bit;} 
    

    
    QList<MidiRouterChain *> midiRouterChains() const{return *m_midiRouterChains;} 
    

    
    Monitor * monitor() const{return m_monitor;} 
    

    
    EasyConfig * easyConfig() const{return m_easyConfig;} 
    

    
    
        template<typename T = MidiRouteInputCc14bit *>
        std::enable_if_t<std::is_same_v<T, MidiRouteInputCc14bit *>, void>
        delListItem(int id){
            if (id < m_midiRouteInputCc14bit->size())
            {
                delete m_midiRouteInputCc14bit->at(id);
                m_midiRouteInputCc14bit->removeAt(id);
                emit midiRouteInputCc14bitChanged();
            }
        }

        MidiRouteInputCc14bit * addListItem(MidiRouteInputCc14bit * item)
        {
            m_midiRouteInputCc14bit->push_back(item);
            emit midiRouteInputCc14bitChanged();
            return item;
        }

        template<typename T = MidiRouteInputCc14bit * >
        std::enable_if_t<std::is_same_v<T, MidiRouteInputCc14bit * >, void>
        clearList(){
            qDeleteAll(*m_midiRouteInputCc14bit);
            m_midiRouteInputCc14bit->clear();
            emit midiRouteInputCc14bitChanged();
        }

        template<typename T = MidiRouteInputCc14bit *>
        std::enable_if_t<std::is_same_v<T, MidiRouteInputCc14bit *>, const QList<MidiRouteInputCc14bit *>>
        listItems(){
            return *m_midiRouteInputCc14bit;
        }

        
        template<typename T = MidiRouterChain *>
        std::enable_if_t<std::is_same_v<T, MidiRouterChain *>, void>
        delListItem(int id){
            if (id < m_midiRouterChains->size())
            {
                delete m_midiRouterChains->at(id);
                m_midiRouterChains->removeAt(id);
                emit midiRouterChainsChanged();
            }
        }

        MidiRouterChain * addListItem(MidiRouterChain * item)
        {
            m_midiRouterChains->push_back(item);
            emit midiRouterChainsChanged();
            return item;
        }

        template<typename T = MidiRouterChain * >
        std::enable_if_t<std::is_same_v<T, MidiRouterChain * >, void>
        clearList(){
            qDeleteAll(*m_midiRouterChains);
            m_midiRouterChains->clear();
            emit midiRouterChainsChanged();
        }

        template<typename T = MidiRouterChain *>
        std::enable_if_t<std::is_same_v<T, MidiRouterChain *>, const QList<MidiRouterChain *>>
        listItems(){
            return *m_midiRouterChains;
        }

        
    
signals:
    void uuidChanged();
    void midiInputNameChanged();
    void ignoreTypesMidiSysexChanged();
    void ignoreTypesMidiTimeChanged();
    void ignoreTypesMidiSenseChanged();
    void midiRouteClockTimeSigChanged();
    void midiRouteClockTimeSigDivByChanged();
    void midiRouteClockFromSppPosChanged();
    void midiRouteClockPropegateInputsChanged();
    void midiRouteInputCc14bitChanged();
    void midiRouterChainsChanged();
    void monitorChanged();
    void easyConfigChanged();
    

protected:
    QList<MidiRouteInputCc14bit *> *m_midiRouteInputCc14bit = new QList<MidiRouteInputCc14bit *>();
    QList<MidiRouterChain *> *m_midiRouterChains = new QList<MidiRouterChain *>();
    Monitor * m_monitor = new Monitor(this);
    EasyConfig * m_easyConfig = new EasyConfig(this);
    

private:
    QString m_uuid ;
    QString m_midiInputName ;
    bool m_ignoreTypesMidiSysex = false;
    bool m_ignoreTypesMidiTime = false;
    bool m_ignoreTypesMidiSense = false;
    int m_midiRouteClockTimeSig = 0;
    int m_midiRouteClockTimeSigDivBy = 0;
    int m_midiRouteClockFromSppPos = 0;
    QStringList m_midiRouteClockPropegateInputs = {};
    
};
//-only-file null

//[[[end]]]
