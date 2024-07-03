#include "BalData.h"

BalData::BalData(QObject *parent)
    : BalDataPrivate{parent}
{


/*[[[cog
import cog
from BalDataPrivate import localStore


cog.outl(localStore.getLclStorCntr(),
        dedent=True, trimblanklines=True)

]]] */
loadX();
loadY();
loadWidth();
loadHeight();
loadReqServerPortNumber();
loadClientServerName();
loadIsClientConnectLocal();
loadIsAutoStartServer();
loadClientPortNumber();
loadIsAutoConnectClient();

//[[[end]]]
}


/*[[[cog
import cog
from BalDataPrivate import localStore


cog.outl(localStore.getLclStorCpp(),
        dedent=True, trimblanklines=True)

]]] */
void BalData::loadX()
{
    int s = settings.value("x", 100).toInt();
    setX(s);
}

void BalData::saveX(const int s)
{
    settings.setValue("x", s);
    loadX();
}
void BalData::loadY()
{
    int s = settings.value("y", 100).toInt();
    setY(s);
}

void BalData::saveY(const int s)
{
    settings.setValue("y", s);
    loadY();
}
void BalData::loadWidth()
{
    int s = settings.value("width", 800).toInt();
    setWidth(s);
}

void BalData::saveWidth(const int s)
{
    settings.setValue("width", s);
    loadWidth();
}
void BalData::loadHeight()
{
    int s = settings.value("height", 500).toInt();
    setHeight(s);
}

void BalData::saveHeight(const int s)
{
    settings.setValue("height", s);
    loadHeight();
}
void BalData::loadReqServerPortNumber()
{
    int s = settings.value("reqServerPortNumber", 12345).toInt();
    setReqServerPortNumber(s);
}

void BalData::saveReqServerPortNumber(const int s)
{
    settings.setValue("reqServerPortNumber", s);
    loadReqServerPortNumber();
}
void BalData::loadClientServerName()
{
    QString s = settings.value("clientServerName", "localhost").toString();
    setClientServerName(s);
}

void BalData::saveClientServerName(const QString s)
{
    settings.setValue("clientServerName", s);
    loadClientServerName();
}
void BalData::loadIsClientConnectLocal()
{
    bool s = settings.value("isClientConnectLocal", true).toBool();
    setIsClientConnectLocal(s);
}

void BalData::saveIsClientConnectLocal(const bool s)
{
    settings.setValue("isClientConnectLocal", s);
    loadIsClientConnectLocal();
}
void BalData::loadIsAutoStartServer()
{
    bool s = settings.value("isAutoStartServer", true).toBool();
    setIsAutoStartServer(s);
}

void BalData::saveIsAutoStartServer(const bool s)
{
    settings.setValue("isAutoStartServer", s);
    loadIsAutoStartServer();
}
void BalData::loadClientPortNumber()
{
    int s = settings.value("clientPortNumber", 12345).toInt();
    setClientPortNumber(s);
}

void BalData::saveClientPortNumber(const int s)
{
    settings.setValue("clientPortNumber", s);
    loadClientPortNumber();
}
void BalData::loadIsAutoConnectClient()
{
    bool s = settings.value("isAutoConnectClient", true).toBool();
    setIsAutoConnectClient(s);
}

void BalData::saveIsAutoConnectClient(const bool s)
{
    settings.setValue("isAutoConnectClient", s);
    loadIsAutoConnectClient();
}

//[[[end]]]

void BalData::startClient()
{
    if (isClientConnectLocal()) {
        startClient("localhost", reqServerPortNumber());
    } else {
        startClient(clientServerName(), clientPortNumber());
    }
}

void BalData::onApplicationStarted()
{
    qDebug() << "Application staarted";
    if (isAutoStartServer()) {
        qDebug() << "Auto start server";
        startServer(reqServerPortNumber());
    }
    if (isAutoConnectClient()) {
        startClient();
    }
}
void BalData::updateServerStatus()
{
    m_serverPort = msc.getPort();
    m_isServerRunning = msc.getServerIsRunning();
    emit serverPortChanged();
    emit isServerRunningChanged();
}

void BalData::startServer(int portNumber)
{
    msc.start(portNumber);
    updateServerStatus();
    if (isServerRunning()) {
        saveReqServerPortNumber(serverPort());
    }
}

void BalData::stopServer()
{
    msc.stop();
    updateServerStatus();
}

void BalData::startClient(const QString &serverName, int portNumber)
{
    mcc.start(serverName, portNumber);
}

void BalData::stopClient()
{
    mcc.stop();
}

void BalData::testDummyDelete(const QJSValue &callback)
{
    mcc.invokeMethod("wcmidiout", "getPortCount", {}, true, callback, qjsEngine(this));
}
