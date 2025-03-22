#pragma once

#include <QObject>
#include <QObjectComputedProperty>
#include <QQmlEngine>
#include "JsAsync.h"

/*[[[cog
import cog
from BalDataPrivate import classBalDataPrivate


cog.outl(classBalDataPrivate.getClassHeader(),
        dedent=True, trimblanklines=True)

]]] */
class BalDataPrivate : public JsAsync
{
    Q_OBJECT
    Q_PROPERTY(int x READ x WRITE setX NOTIFY xChanged )
    Q_PROPERTY(int y READ y WRITE setY NOTIFY yChanged )
    Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged )
    Q_PROPERTY(int height READ height WRITE setHeight NOTIFY heightChanged )
    Q_PROPERTY(int serverPort READ serverPort  NOTIFY serverPortChanged )
    Q_PROPERTY(bool isServerRunning READ isServerRunning  NOTIFY isServerRunningChanged )
    Q_PROPERTY(int reqServerPortNumber READ reqServerPortNumber WRITE setReqServerPortNumber NOTIFY reqServerPortNumberChanged )
    Q_PROPERTY(QString clientServerName READ clientServerName WRITE setClientServerName NOTIFY clientServerNameChanged )
    Q_PROPERTY(bool isClientConnectLocal READ isClientConnectLocal WRITE setIsClientConnectLocal NOTIFY isClientConnectLocalChanged )
    Q_PROPERTY(bool isAutoStartServer READ isAutoStartServer WRITE setIsAutoStartServer NOTIFY isAutoStartServerChanged )
    Q_PROPERTY(int clientPortNumber READ clientPortNumber WRITE setClientPortNumber NOTIFY clientPortNumberChanged )
    Q_PROPERTY(bool isAutoConnectClient READ isAutoConnectClient WRITE setIsAutoConnectClient NOTIFY isAutoConnectClientChanged )
    Q_PROPERTY(bool isSaveConfigOnServer READ isSaveConfigOnServer WRITE setIsSaveConfigOnServer NOTIFY isSaveConfigOnServerChanged )
    Q_PROPERTY(QString defaultFontSize READ defaultFontSize WRITE setDefaultFontSize NOTIFY defaultFontSizeChanged )
    Q_PROPERTY(QString defaultHeaderTabSelected READ defaultHeaderTabSelected WRITE setDefaultHeaderTabSelected NOTIFY defaultHeaderTabSelectedChanged )
    
    QML_ELEMENT
public:
    BalDataPrivate(QObject *parent = nullptr);
    virtual ~BalDataPrivate() = default;

    
    
    int x() const{return m_x;} 
    
void setX(const int newX)
    {
        if (m_x == newX)
            return;
        m_x = newX;
        emit xChanged();
    }


    
    int y() const{return m_y;} 
    
void setY(const int newY)
    {
        if (m_y == newY)
            return;
        m_y = newY;
        emit yChanged();
    }


    
    int width() const{return m_width;} 
    
void setWidth(const int newWidth)
    {
        if (m_width == newWidth)
            return;
        m_width = newWidth;
        emit widthChanged();
    }


    
    int height() const{return m_height;} 
    
void setHeight(const int newHeight)
    {
        if (m_height == newHeight)
            return;
        m_height = newHeight;
        emit heightChanged();
    }


    
    int serverPort() const{return m_serverPort;} 
    

    
    bool isServerRunning() const{return m_isServerRunning;} 
    

    
    int reqServerPortNumber() const{return m_reqServerPortNumber;} 
    
void setReqServerPortNumber(const int newReqServerPortNumber)
    {
        if (m_reqServerPortNumber == newReqServerPortNumber)
            return;
        m_reqServerPortNumber = newReqServerPortNumber;
        emit reqServerPortNumberChanged();
    }


    
    QString clientServerName() const{return m_clientServerName;} 
    
void setClientServerName(const QString &newClientServerName)
    {
        if (m_clientServerName == newClientServerName)
            return;
        m_clientServerName = newClientServerName;
        emit clientServerNameChanged();
    }


    
    bool isClientConnectLocal() const{return m_isClientConnectLocal;} 
    
void setIsClientConnectLocal(const bool newIsClientConnectLocal)
    {
        if (m_isClientConnectLocal == newIsClientConnectLocal)
            return;
        m_isClientConnectLocal = newIsClientConnectLocal;
        emit isClientConnectLocalChanged();
    }


    
    bool isAutoStartServer() const{return m_isAutoStartServer;} 
    
void setIsAutoStartServer(const bool newIsAutoStartServer)
    {
        if (m_isAutoStartServer == newIsAutoStartServer)
            return;
        m_isAutoStartServer = newIsAutoStartServer;
        emit isAutoStartServerChanged();
    }


    
    int clientPortNumber() const{return m_clientPortNumber;} 
    
void setClientPortNumber(const int newClientPortNumber)
    {
        if (m_clientPortNumber == newClientPortNumber)
            return;
        m_clientPortNumber = newClientPortNumber;
        emit clientPortNumberChanged();
    }


    
    bool isAutoConnectClient() const{return m_isAutoConnectClient;} 
    
void setIsAutoConnectClient(const bool newIsAutoConnectClient)
    {
        if (m_isAutoConnectClient == newIsAutoConnectClient)
            return;
        m_isAutoConnectClient = newIsAutoConnectClient;
        emit isAutoConnectClientChanged();
    }


    
    bool isSaveConfigOnServer() const{return m_isSaveConfigOnServer;} 
    
void setIsSaveConfigOnServer(const bool newIsSaveConfigOnServer)
    {
        if (m_isSaveConfigOnServer == newIsSaveConfigOnServer)
            return;
        m_isSaveConfigOnServer = newIsSaveConfigOnServer;
        emit isSaveConfigOnServerChanged();
    }


    
    QString defaultFontSize() const{return m_defaultFontSize;} 
    
void setDefaultFontSize(const QString &newDefaultFontSize)
    {
        if (m_defaultFontSize == newDefaultFontSize)
            return;
        m_defaultFontSize = newDefaultFontSize;
        emit defaultFontSizeChanged();
    }


    
    QString defaultHeaderTabSelected() const{return m_defaultHeaderTabSelected;} 
    
void setDefaultHeaderTabSelected(const QString &newDefaultHeaderTabSelected)
    {
        if (m_defaultHeaderTabSelected == newDefaultHeaderTabSelected)
            return;
        m_defaultHeaderTabSelected = newDefaultHeaderTabSelected;
        emit defaultHeaderTabSelectedChanged();
    }



signals:
    void xChanged();
    void yChanged();
    void widthChanged();
    void heightChanged();
    void serverPortChanged();
    void isServerRunningChanged();
    void reqServerPortNumberChanged();
    void clientServerNameChanged();
    void isClientConnectLocalChanged();
    void isAutoStartServerChanged();
    void clientPortNumberChanged();
    void isAutoConnectClientChanged();
    void isSaveConfigOnServerChanged();
    void defaultFontSizeChanged();
    void defaultHeaderTabSelectedChanged();
    

protected:
    int m_serverPort;
    bool m_isServerRunning;
    

private:
    int m_x;
    int m_y;
    int m_width;
    int m_height;
    int m_reqServerPortNumber;
    QString m_clientServerName;
    bool m_isClientConnectLocal;
    bool m_isAutoStartServer;
    int m_clientPortNumber;
    bool m_isAutoConnectClient;
    bool m_isSaveConfigOnServer;
    QString m_defaultFontSize;
    QString m_defaultHeaderTabSelected;
    
    void ctorClass();
};

//[[[end]]]
