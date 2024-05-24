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

//[[[end]]]

void BalData::updateServerStatus()
{
    m_serverPort = mc.getPort();
    m_isServerRunning = mc.getServerIsRunning();
    emit serverPortChanged();
    emit isServerRunningChanged();
}

void BalData::startServer(int portNumber)
{
    mc.start(portNumber);
    updateServerStatus();
}

void BalData::stopServer()
{
    mc.stop();
    updateServerStatus();
}
