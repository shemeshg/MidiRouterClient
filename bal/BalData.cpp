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

//[[[end]]]

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

void BalData::startClient(int portNumber)
{
    mcc.start(portNumber);
}

void BalData::stopClient()
{
    mcc.stop();
}
