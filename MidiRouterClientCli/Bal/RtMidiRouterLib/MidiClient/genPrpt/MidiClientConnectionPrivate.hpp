//-define-file header genPrpt/MidiClientConnectionPrivate.h
//-only-file header //-
//- #pragma once


#include <QObject>
#include <QObjectComputedProperty>
#include <QQmlEngine>

//- {include-header}
#include "../hpp/UserDataConfig.hpp" //- #include "../GenHpp/UserDataConfig.h"

//-only-file null
/*[[[cog
import cog
from MidiClientConnectionPrivate import prptClass


cog.outl(prptClass.getClassHeader(),
        dedent=True, trimblanklines=True)

]]] */
//-only-file header
class MidiClientConnectionPrivate : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString serverStatusText READ serverStatusText WRITE setServerStatusText NOTIFY serverStatusTextChanged )
    Q_PROPERTY(ServerStatus serverStatus READ serverStatus WRITE setServerStatus NOTIFY serverStatusChanged )
    Q_PROPERTY(UserDataConfig * userDataConfig READ userDataConfig  NOTIFY userDataConfigChanged )
    
    QML_ELEMENT
public:
    
    MidiClientConnectionPrivate(QObject *parent):QObject(parent){}

    virtual ~MidiClientConnectionPrivate() {
        
    }

    
enum class ServerStatus {
        STOPPED, STARTING, RUNNING, FAILED
    };
Q_ENUM(ServerStatus)

    
    QString serverStatusText() const{return m_serverStatusText;} 
    
void setServerStatusText(const QString &newServerStatusText)
    {
        if (m_serverStatusText == newServerStatusText)
            return;
        m_serverStatusText = newServerStatusText;
        emit serverStatusTextChanged();
    }


    
    ServerStatus serverStatus() const{return m_serverStatus;} 
    
void setServerStatus(const ServerStatus &newServerStatus)
    {
        if (m_serverStatus == newServerStatus)
            return;
        m_serverStatus = newServerStatus;
        emit serverStatusChanged();
    }


    
    UserDataConfig * userDataConfig() const{return m_userDataConfig;} 
    

    
    
    
signals:
    void serverStatusTextChanged();
    void serverStatusChanged();
    void userDataConfigChanged();
    

protected:
    UserDataConfig * m_userDataConfig = new UserDataConfig(this);;
    

private:
    QString m_serverStatusText ;
    ServerStatus m_serverStatus = ServerStatus::STOPPED;
    
};
//-only-file null

//[[[end]]]
