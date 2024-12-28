//-define-file header genPrpt/EasyConfigRoutePrivate.h
//-only-file header //-
#pragma once

#include <QObject>
#include <QObjectComputedProperty>
#include <QQmlEngine>

//-only-file null
/*[[[cog
import cog
from EasyConfigRoutePrivate import prptClass


cog.outl(prptClass.getClassHeader(),
        dedent=True, trimblanklines=True)

]]] */
//-only-file header
class EasyConfigRoutePrivate : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int splitRangeId READ splitRangeId WRITE setSplitRangeId NOTIFY splitRangeIdChanged )
    Q_PROPERTY(int fromSelectedMidiEventTypeId READ fromSelectedMidiEventTypeId WRITE setFromSelectedMidiEventTypeId NOTIFY fromSelectedMidiEventTypeIdChanged )
    Q_PROPERTY(int fromChannel READ fromChannel WRITE setFromChannel NOTIFY fromChannelChanged )
    Q_PROPERTY(int fromData1 READ fromData1 WRITE setFromData1 NOTIFY fromData1Changed )
    Q_PROPERTY(int transpose READ transpose WRITE setTranspose NOTIFY transposeChanged )
    Q_PROPERTY(int fromCcOrNrpnStart READ fromCcOrNrpnStart WRITE setFromCcOrNrpnStart NOTIFY fromCcOrNrpnStartChanged )
    Q_PROPERTY(int fromCcOrNrpnEnd READ fromCcOrNrpnEnd WRITE setFromCcOrNrpnEnd NOTIFY fromCcOrNrpnEndChanged )
    Q_PROPERTY(int toCcOrNrpnStart READ toCcOrNrpnStart WRITE setToCcOrNrpnStart NOTIFY toCcOrNrpnStartChanged )
    Q_PROPERTY(int toCcOrNrpnEnd READ toCcOrNrpnEnd WRITE setToCcOrNrpnEnd NOTIFY toCcOrNrpnEndChanged )
    Q_PROPERTY(int toSelectedMidiEventTypeId READ toSelectedMidiEventTypeId WRITE setToSelectedMidiEventTypeId NOTIFY toSelectedMidiEventTypeIdChanged )
    Q_PROPERTY(int toChannel READ toChannel WRITE setToChannel NOTIFY toChannelChanged )
    Q_PROPERTY(int toData1 READ toData1 WRITE setToData1 NOTIFY toData1Changed )
    Q_PROPERTY(QString toDestinationName READ toDestinationName WRITE setToDestinationName NOTIFY toDestinationNameChanged )
    
    QML_ELEMENT
public:
    
    EasyConfigRoutePrivate(QObject *parent = nullptr):QObject(parent){}

    virtual ~EasyConfigRoutePrivate() {
        
    }

    
    
    int splitRangeId() const{return m_splitRangeId;} 
    
void setSplitRangeId(const int newSplitRangeId)
    {
        if (m_splitRangeId == newSplitRangeId)
            return;
        m_splitRangeId = newSplitRangeId;
        emit splitRangeIdChanged();
    }


    
    int fromSelectedMidiEventTypeId() const{return m_fromSelectedMidiEventTypeId;} 
    
void setFromSelectedMidiEventTypeId(const int newFromSelectedMidiEventTypeId)
    {
        if (m_fromSelectedMidiEventTypeId == newFromSelectedMidiEventTypeId)
            return;
        m_fromSelectedMidiEventTypeId = newFromSelectedMidiEventTypeId;
        emit fromSelectedMidiEventTypeIdChanged();
    }


    
    int fromChannel() const{return m_fromChannel;} 
    
void setFromChannel(const int newFromChannel)
    {
        if (m_fromChannel == newFromChannel)
            return;
        m_fromChannel = newFromChannel;
        emit fromChannelChanged();
    }


    
    int fromData1() const{return m_fromData1;} 
    
void setFromData1(const int newFromData1)
    {
        if (m_fromData1 == newFromData1)
            return;
        m_fromData1 = newFromData1;
        emit fromData1Changed();
    }


    
    int transpose() const{return m_transpose;} 
    
void setTranspose(const int newTranspose)
    {
        if (m_transpose == newTranspose)
            return;
        m_transpose = newTranspose;
        emit transposeChanged();
    }


    
    int fromCcOrNrpnStart() const{return m_fromCcOrNrpnStart;} 
    
void setFromCcOrNrpnStart(const int newFromCcOrNrpnStart)
    {
        if (m_fromCcOrNrpnStart == newFromCcOrNrpnStart)
            return;
        m_fromCcOrNrpnStart = newFromCcOrNrpnStart;
        emit fromCcOrNrpnStartChanged();
    }


    
    int fromCcOrNrpnEnd() const{return m_fromCcOrNrpnEnd;} 
    
void setFromCcOrNrpnEnd(const int newFromCcOrNrpnEnd)
    {
        if (m_fromCcOrNrpnEnd == newFromCcOrNrpnEnd)
            return;
        m_fromCcOrNrpnEnd = newFromCcOrNrpnEnd;
        emit fromCcOrNrpnEndChanged();
    }


    
    int toCcOrNrpnStart() const{return m_toCcOrNrpnStart;} 
    
void setToCcOrNrpnStart(const int newToCcOrNrpnStart)
    {
        if (m_toCcOrNrpnStart == newToCcOrNrpnStart)
            return;
        m_toCcOrNrpnStart = newToCcOrNrpnStart;
        emit toCcOrNrpnStartChanged();
    }


    
    int toCcOrNrpnEnd() const{return m_toCcOrNrpnEnd;} 
    
void setToCcOrNrpnEnd(const int newToCcOrNrpnEnd)
    {
        if (m_toCcOrNrpnEnd == newToCcOrNrpnEnd)
            return;
        m_toCcOrNrpnEnd = newToCcOrNrpnEnd;
        emit toCcOrNrpnEndChanged();
    }


    
    int toSelectedMidiEventTypeId() const{return m_toSelectedMidiEventTypeId;} 
    
void setToSelectedMidiEventTypeId(const int newToSelectedMidiEventTypeId)
    {
        if (m_toSelectedMidiEventTypeId == newToSelectedMidiEventTypeId)
            return;
        m_toSelectedMidiEventTypeId = newToSelectedMidiEventTypeId;
        emit toSelectedMidiEventTypeIdChanged();
    }


    
    int toChannel() const{return m_toChannel;} 
    
void setToChannel(const int newToChannel)
    {
        if (m_toChannel == newToChannel)
            return;
        m_toChannel = newToChannel;
        emit toChannelChanged();
    }


    
    int toData1() const{return m_toData1;} 
    
void setToData1(const int newToData1)
    {
        if (m_toData1 == newToData1)
            return;
        m_toData1 = newToData1;
        emit toData1Changed();
    }


    
    QString toDestinationName() const{return m_toDestinationName;} 
    
void setToDestinationName(const QString &newToDestinationName)
    {
        if (m_toDestinationName == newToDestinationName)
            return;
        m_toDestinationName = newToDestinationName;
        emit toDestinationNameChanged();
    }


    
    
signals:
    void splitRangeIdChanged();
    void fromSelectedMidiEventTypeIdChanged();
    void fromChannelChanged();
    void fromData1Changed();
    void transposeChanged();
    void fromCcOrNrpnStartChanged();
    void fromCcOrNrpnEndChanged();
    void toCcOrNrpnStartChanged();
    void toCcOrNrpnEndChanged();
    void toSelectedMidiEventTypeIdChanged();
    void toChannelChanged();
    void toData1Changed();
    void toDestinationNameChanged();
    

protected:
    

private:
    int m_splitRangeId;
    int m_fromSelectedMidiEventTypeId;
    int m_fromChannel;
    int m_fromData1;
    int m_transpose;
    int m_fromCcOrNrpnStart;
    int m_fromCcOrNrpnEnd;
    int m_toCcOrNrpnStart;
    int m_toCcOrNrpnEnd;
    int m_toSelectedMidiEventTypeId;
    int m_toChannel;
    int m_toData1;
    QString m_toDestinationName;
    
};
//-only-file null

//[[[end]]]
