//-define-file header genPrpt/UserControlPrivate.h
//-only-file header //-
#pragma once

#include <QObject>
#include <QObjectComputedProperty>
#include <QQmlEngine>

//-only-file null
/*[[[cog
import cog
from UserControlPrivate import prptClass


cog.outl(prptClass.getClassHeader(),
        dedent=True, trimblanklines=True)

]]] */
//-only-file header
class UserControlPrivate : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString uuid READ uuid WRITE setUuid NOTIFY uuidChanged )
    Q_PROPERTY(bool isSendOnPresetChange READ isSendOnPresetChange WRITE setIsSendOnPresetChange NOTIFY isSendOnPresetChangeChanged )
    Q_PROPERTY(EventType eventType READ eventType WRITE setEventType NOTIFY eventTypeChanged )
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged )
    Q_PROPERTY(int inputVal READ inputVal WRITE setInputVal NOTIFY inputValChanged )
    Q_PROPERTY(int minVal READ minVal WRITE setMinVal NOTIFY minValChanged )
    Q_PROPERTY(int maxVal READ maxVal WRITE setMaxVal NOTIFY maxValChanged )
    Q_PROPERTY(bool is64Mode READ is64Mode WRITE setIs64Mode NOTIFY is64ModeChanged )
    Q_PROPERTY(int channelId READ channelId WRITE setChannelId NOTIFY channelIdChanged )
    Q_PROPERTY(int ccId READ ccId WRITE setCcId NOTIFY ccIdChanged )
    Q_PROPERTY(int nrpnControl READ nrpnControl WRITE setNrpnControl NOTIFY nrpnControlChanged )
    Q_PROPERTY(QString outputPortnName READ outputPortnName WRITE setOutputPortnName NOTIFY outputPortnNameChanged )
    Q_PROPERTY(bool isShowDropdown READ isShowDropdown WRITE setIsShowDropdown NOTIFY isShowDropdownChanged )
    Q_PROPERTY(int dropdownListId READ dropdownListId WRITE setDropdownListId NOTIFY dropdownListIdChanged )
    
    QML_ELEMENT
public:
    
    UserControlPrivate(QObject *parent = nullptr):QObject(parent){}

    virtual ~UserControlPrivate() {
        
    }

    
enum class EventType {
        CC, PROGRAM_CHANGE, NRPN
    };
Q_ENUM(EventType)

    
    QString uuid() const{return m_uuid;} 
    
void setUuid(const QString &newUuid)
    {
        if (m_uuid == newUuid)
            return;
        m_uuid = newUuid;
        emit uuidChanged();
    }


    
    bool isSendOnPresetChange() const{return m_isSendOnPresetChange;} 
    
void setIsSendOnPresetChange(const bool newIsSendOnPresetChange)
    {
        if (m_isSendOnPresetChange == newIsSendOnPresetChange)
            return;
        m_isSendOnPresetChange = newIsSendOnPresetChange;
        emit isSendOnPresetChangeChanged();
    }


    
    EventType eventType() const{return m_eventType;} 
    
void setEventType(const EventType &newEventType)
    {
        if (m_eventType == newEventType)
            return;
        m_eventType = newEventType;
        emit eventTypeChanged();
    }


    
    QString description() const{return m_description;} 
    
void setDescription(const QString &newDescription)
    {
        if (m_description == newDescription)
            return;
        m_description = newDescription;
        emit descriptionChanged();
    }


    
    int inputVal() const{return m_inputVal;} 
    
void setInputVal(const int newInputVal)
    {
        if (m_inputVal == newInputVal)
            return;
        m_inputVal = newInputVal;
        emit inputValChanged();
    }


    
    int minVal() const{return m_minVal;} 
    
void setMinVal(const int newMinVal)
    {
        if (m_minVal == newMinVal)
            return;
        m_minVal = newMinVal;
        emit minValChanged();
    }


    
    int maxVal() const{return m_maxVal;} 
    
void setMaxVal(const int newMaxVal)
    {
        if (m_maxVal == newMaxVal)
            return;
        m_maxVal = newMaxVal;
        emit maxValChanged();
    }


    
    bool is64Mode() const{return m_is64Mode;} 
    
void setIs64Mode(const bool newIs64Mode)
    {
        if (m_is64Mode == newIs64Mode)
            return;
        m_is64Mode = newIs64Mode;
        emit is64ModeChanged();
    }


    
    int channelId() const{return m_channelId;} 
    
void setChannelId(const int newChannelId)
    {
        if (m_channelId == newChannelId)
            return;
        m_channelId = newChannelId;
        emit channelIdChanged();
    }


    
    int ccId() const{return m_ccId;} 
    
void setCcId(const int newCcId)
    {
        if (m_ccId == newCcId)
            return;
        m_ccId = newCcId;
        emit ccIdChanged();
    }


    
    int nrpnControl() const{return m_nrpnControl;} 
    
void setNrpnControl(const int newNrpnControl)
    {
        if (m_nrpnControl == newNrpnControl)
            return;
        m_nrpnControl = newNrpnControl;
        emit nrpnControlChanged();
    }


    
    QString outputPortnName() const{return m_outputPortnName;} 
    
void setOutputPortnName(const QString &newOutputPortnName)
    {
        if (m_outputPortnName == newOutputPortnName)
            return;
        m_outputPortnName = newOutputPortnName;
        emit outputPortnNameChanged();
    }


    
    bool isShowDropdown() const{return m_isShowDropdown;} 
    
void setIsShowDropdown(const bool newIsShowDropdown)
    {
        if (m_isShowDropdown == newIsShowDropdown)
            return;
        m_isShowDropdown = newIsShowDropdown;
        emit isShowDropdownChanged();
    }


    
    int dropdownListId() const{return m_dropdownListId;} 
    
void setDropdownListId(const int newDropdownListId)
    {
        if (m_dropdownListId == newDropdownListId)
            return;
        m_dropdownListId = newDropdownListId;
        emit dropdownListIdChanged();
    }


    
    
    
signals:
    void uuidChanged();
    void isSendOnPresetChangeChanged();
    void eventTypeChanged();
    void descriptionChanged();
    void inputValChanged();
    void minValChanged();
    void maxValChanged();
    void is64ModeChanged();
    void channelIdChanged();
    void ccIdChanged();
    void nrpnControlChanged();
    void outputPortnNameChanged();
    void isShowDropdownChanged();
    void dropdownListIdChanged();
    

protected:
    

private:
    QString m_uuid;
    bool m_isSendOnPresetChange;
    EventType m_eventType;
    QString m_description;
    int m_inputVal;
    int m_minVal;
    int m_maxVal;
    bool m_is64Mode;
    int m_channelId;
    int m_ccId;
    int m_nrpnControl;
    QString m_outputPortnName;
    bool m_isShowDropdown;
    int m_dropdownListId;
    
};
//-only-file null

//[[[end]]]
