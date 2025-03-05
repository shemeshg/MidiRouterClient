//-define-file header genPrpt/MidiRouterChainPrivate.h
//-only-file header //-
#pragma once

#include <QObject>
#include <QObjectComputedProperty>
#include <QQmlEngine>

//-only-file header 

//-only-file null
/*[[[cog
import cog
from MidiRouterChainPrivate import prptClass


cog.outl(prptClass.getClassHeader(),
        dedent=True, trimblanklines=True)

]]] */
//-only-file header
class MidiRouterChainPrivate : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged )
    Q_PROPERTY(QString uuid READ uuid WRITE setUuid NOTIFY uuidChanged )
    Q_PROPERTY(bool isEasyConfig READ isEasyConfig WRITE setIsEasyConfig NOTIFY isEasyConfigChanged )
    Q_PROPERTY(bool isRunForPresetOnAndOff READ isRunForPresetOnAndOff WRITE setIsRunForPresetOnAndOff NOTIFY isRunForPresetOnAndOffChanged )
    Q_PROPERTY(QList<QVariant> midiRoutersFilters READ midiRoutersFilters  NOTIFY midiRoutersFiltersChanged )
    
    QML_ELEMENT
public:
    
    MidiRouterChainPrivate(QObject *parent = nullptr):QObject(parent){}

    virtual ~MidiRouterChainPrivate() {
        
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


    
    bool isEasyConfig() const{return m_isEasyConfig;} 
    
void setIsEasyConfig(const bool newIsEasyConfig)
    {
        if (m_isEasyConfig == newIsEasyConfig)
            return;
        m_isEasyConfig = newIsEasyConfig;
        emit isEasyConfigChanged();
    }


    
    bool isRunForPresetOnAndOff() const{return m_isRunForPresetOnAndOff;} 
    
void setIsRunForPresetOnAndOff(const bool newIsRunForPresetOnAndOff)
    {
        if (m_isRunForPresetOnAndOff == newIsRunForPresetOnAndOff)
            return;
        m_isRunForPresetOnAndOff = newIsRunForPresetOnAndOff;
        emit isRunForPresetOnAndOffChanged();
    }


    
    QList<QVariant> midiRoutersFilters() const{return m_midiRoutersFilters;} 
    

    
    
    
signals:
    void nameChanged();
    void uuidChanged();
    void isEasyConfigChanged();
    void isRunForPresetOnAndOffChanged();
    void midiRoutersFiltersChanged();
    

protected:
    QList<QVariant> m_midiRoutersFilters ={};
    

private:
    QString m_name ;
    QString m_uuid ;
    bool m_isEasyConfig = false;
    bool m_isRunForPresetOnAndOff = false;
    
};
//-only-file null

//[[[end]]]
