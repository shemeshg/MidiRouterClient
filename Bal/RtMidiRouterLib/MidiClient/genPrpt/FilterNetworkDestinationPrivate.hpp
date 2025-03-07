//-define-file header genPrpt/FilterNetworkDestinationPrivate.h
//-only-file header //-
#pragma once

#include <QObject>
#include <QObjectComputedProperty>
#include <QQmlEngine>

//- {include-header}
#include "MidiRoutersFilter.hpp" //- #include "MidiRoutersFilter.h"

//-only-file null
/*[[[cog
import cog
from FilterNetworkDestinationPrivate import prptClass


cog.outl(prptClass.getClassHeader(),
        dedent=True, trimblanklines=True)

]]] */
//-only-file header
class FilterNetworkDestinationPrivate : public MidiRoutersFilter
{
    Q_OBJECT
    Q_PROPERTY(QString baseMidiRouteInput READ baseMidiRouteInput WRITE setBaseMidiRouteInput NOTIFY baseMidiRouteInputChanged )
    Q_PROPERTY(QString serverName READ serverName WRITE setServerName NOTIFY serverNameChanged )
    Q_PROPERTY(int serverPort READ serverPort WRITE setServerPort NOTIFY serverPortChanged )
    
    QML_ELEMENT
public:
    
    FilterNetworkDestinationPrivate(QObject *parent = nullptr):MidiRoutersFilter(parent){}

    virtual ~FilterNetworkDestinationPrivate() {
        
    }

    
    
    QString baseMidiRouteInput() const{return m_baseMidiRouteInput;} 
    
void setBaseMidiRouteInput(const QString &newBaseMidiRouteInput)
    {
        if (m_baseMidiRouteInput == newBaseMidiRouteInput)
            return;
        m_baseMidiRouteInput = newBaseMidiRouteInput;
        emit baseMidiRouteInputChanged();
    }


    
    QString serverName() const{return m_serverName;} 
    
void setServerName(const QString &newServerName)
    {
        if (m_serverName == newServerName)
            return;
        m_serverName = newServerName;
        emit serverNameChanged();
    }


    
    int serverPort() const{return m_serverPort;} 
    
void setServerPort(const int newServerPort)
    {
        if (m_serverPort == newServerPort)
            return;
        m_serverPort = newServerPort;
        emit serverPortChanged();
    }


    
    
    
signals:
    void baseMidiRouteInputChanged();
    void serverNameChanged();
    void serverPortChanged();
    

protected:
    

private:
    QString m_baseMidiRouteInput ;
    QString m_serverName ;
    int m_serverPort = 0;
    
};
//-only-file null

//[[[end]]]
