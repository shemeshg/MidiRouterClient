#pragma once

#include <QObject>
#include <QObjectComputedProperty>
#include <QQmlEngine>

/*[[[cog
import cog
from MidiClientConnectionPrivate import classMidiClientConnectionPrivate


cog.outl(classMidiClientConnectionPrivate.getClassHeader(),
        dedent=True, trimblanklines=True)

]]] */
class MidiClientConnectionPrivate : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString serverStatusText READ serverStatusText WRITE setServerStatusText NOTIFY serverStatusTextChanged )
    Q_PROPERTY(ServerStatus serverStatus READ serverStatus WRITE setServerStatus NOTIFY serverStatusChanged )
    
    QML_ELEMENT
public:
    MidiClientConnectionPrivate(QObject *parent = nullptr);

    
enum class ServerStatus {
        Stopped, Starting, Running, Failed
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



signals:
    void serverStatusTextChanged();
    void serverStatusChanged();
    

protected:
    

private:
    QString m_serverStatusText;
    ServerStatus m_serverStatus;
    
    void ctorClass();
};

//[[[end]]]
