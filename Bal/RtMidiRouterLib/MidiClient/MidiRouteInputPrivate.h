#pragma once

#include "MidiRouteInputCc14bit.h"
#include "MidiRouterChain.h"
#include "Monitor.h"
#include <QObject>
#include <QObjectComputedProperty>
#include <QQmlEngine>

/*[[[cog
import cog
from MidiRouteInputPrivate import classMidiRouteInputPrivate


cog.outl(classMidiRouteInputPrivate.getClassHeader(),
        dedent=True, trimblanklines=True)

]]] */
class MidiRouteInputPrivate : public QObject
{
    Q_OBJECT
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
    
    QML_ELEMENT
public:
    MidiRouteInputPrivate(QObject *parent = nullptr);
    virtual ~MidiRouteInputPrivate() = default;

    
    
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


    
    QList<MidiRouteInputCc14bit *> midiRouteInputCc14bit() const{return m_midiRouteInputCc14bit;} 
    

    
    QList<MidiRouterChain *> midiRouterChains() const{return m_midiRouterChains;} 
    

    
    Monitor * monitor() const{return m_monitor;} 
    


signals:
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
    

protected:
    QList<MidiRouteInputCc14bit *> m_midiRouteInputCc14bit;
    QList<MidiRouterChain *> m_midiRouterChains;
    Monitor * m_monitor;
    

private:
    QString m_midiInputName;
    bool m_ignoreTypesMidiSysex;
    bool m_ignoreTypesMidiTime;
    bool m_ignoreTypesMidiSense;
    int m_midiRouteClockTimeSig;
    int m_midiRouteClockTimeSigDivBy;
    int m_midiRouteClockFromSppPos;
    QStringList m_midiRouteClockPropegateInputs;
    
    void ctorClass();
};

//[[[end]]]
