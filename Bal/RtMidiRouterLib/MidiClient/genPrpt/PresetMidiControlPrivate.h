#pragma once

#include <QObject>
#include <QObjectComputedProperty>
#include <QQmlEngine>

/*[[[cog
import cog
from PresetMidiControlPrivate import prptClass


cog.outl(prptClass.getClassHeader(),
        dedent=True, trimblanklines=True)

]]] */
//-only-file header
class PresetMidiControlPrivate : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString portName READ portName WRITE setPortName NOTIFY portNameChanged )
    Q_PROPERTY(PresetMidiType presetMidiType READ presetMidiType WRITE setPresetMidiType NOTIFY presetMidiTypeChanged )
    Q_PROPERTY(QString presetUuid READ presetUuid WRITE setPresetUuid NOTIFY presetUuidChanged )
    Q_PROPERTY(int eventTypeId READ eventTypeId WRITE setEventTypeId NOTIFY eventTypeIdChanged )
    Q_PROPERTY(int channel READ channel WRITE setChannel NOTIFY channelChanged )
    Q_PROPERTY(int data1 READ data1 WRITE setData1 NOTIFY data1Changed )
    Q_PROPERTY(int data2 READ data2 WRITE setData2 NOTIFY data2Changed )
    
    QML_ELEMENT
public:
        PresetMidiControlPrivate(QObject *parent = nullptr);

    virtual ~PresetMidiControlPrivate() {
        
    }

    
enum class PresetMidiType {
        PRESET_OFF, PRESET_ON
    };
Q_ENUM(PresetMidiType)

    
    QString portName() const{return m_portName;} 
    
void setPortName(const QString &newPortName)
    {
        if (m_portName == newPortName)
            return;
        m_portName = newPortName;
        emit portNameChanged();
    }


    
    PresetMidiType presetMidiType() const{return m_presetMidiType;} 
    
void setPresetMidiType(const PresetMidiType &newPresetMidiType)
    {
        if (m_presetMidiType == newPresetMidiType)
            return;
        m_presetMidiType = newPresetMidiType;
        emit presetMidiTypeChanged();
    }


    
    QString presetUuid() const{return m_presetUuid;} 
    
void setPresetUuid(const QString &newPresetUuid)
    {
        if (m_presetUuid == newPresetUuid)
            return;
        m_presetUuid = newPresetUuid;
        emit presetUuidChanged();
    }


    
    int eventTypeId() const{return m_eventTypeId;} 
    
void setEventTypeId(const int newEventTypeId)
    {
        if (m_eventTypeId == newEventTypeId)
            return;
        m_eventTypeId = newEventTypeId;
        emit eventTypeIdChanged();
    }


    
    int channel() const{return m_channel;} 
    
void setChannel(const int newChannel)
    {
        if (m_channel == newChannel)
            return;
        m_channel = newChannel;
        emit channelChanged();
    }


    
    int data1() const{return m_data1;} 
    
void setData1(const int newData1)
    {
        if (m_data1 == newData1)
            return;
        m_data1 = newData1;
        emit data1Changed();
    }


    
    int data2() const{return m_data2;} 
    
void setData2(const int newData2)
    {
        if (m_data2 == newData2)
            return;
        m_data2 = newData2;
        emit data2Changed();
    }


    
    
signals:
    void portNameChanged();
    void presetMidiTypeChanged();
    void presetUuidChanged();
    void eventTypeIdChanged();
    void channelChanged();
    void data1Changed();
    void data2Changed();
    

protected:
    

private:
    void ctorClass(); 
QString m_portName;
    PresetMidiType m_presetMidiType;
    QString m_presetUuid;
    int m_eventTypeId;
    int m_channel;
    int m_data1;
    int m_data2;
    
};
//-only-file null

//[[[end]]]
