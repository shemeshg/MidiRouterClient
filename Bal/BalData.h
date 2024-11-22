#pragma once
#include "BalDataPrivate.h"
#include "RtMidiRouterLib/MidiClientClass.h"
#include "RtMidiRouterLib/MidiServerClass.h"

class BalData : public BalDataPrivate

{
    Q_OBJECT
    Q_PROPERTY(MidiClientConnection *midiClientConnection READ midiClientConnection CONSTANT)
    QML_ELEMENT
public:
    explicit BalData(QObject *parent = nullptr);


public slots:
    QString qtVer() { return QT_VERSION_STR; }
   
/*[[[cog
import cog
from BalDataPrivate import localStore


cog.outl(localStore.getLclStorHdrPub(),
        dedent=True, trimblanklines=True)

]]] */
void saveX(const int X);
void saveY(const int Y);
void saveWidth(const int Width);
void saveHeight(const int Height);
void saveReqServerPortNumber(const int ReqServerPortNumber);
void saveClientServerName(const QString ClientServerName);
void saveIsClientConnectLocal(const bool IsClientConnectLocal);
void saveIsAutoStartServer(const bool IsAutoStartServer);
void saveClientPortNumber(const int ClientPortNumber);
void saveIsAutoConnectClient(const bool IsAutoConnectClient);

//[[[end]]]

void onApplicationStarted();
void startServer(int portNumber);
void stopServer();

void setAsyncServerStatusAndText(MidiClientConnection::ServerStatus serverStatus,
                                 const QJSValue &callback)
{
    makeAsync<bool>(callback, [=]() {
        mcc.midiClientConnection.setServerStatusAndText(serverStatus);
        return true;
    });
}

void stopClient();
void testDummyDelete(const QJSValue &callback);
void applyConfig(const QJSValue &callback);
MidiClientConnection *midiClientConnection() { return &mcc.midiClientConnection; }

void startClient();

private:
QSettings settings;

/*[[[cog
import cog
from BalDataPrivate import localStore


cog.outl(localStore.getLclStorHdrPrv(),
        dedent=True, trimblanklines=True)

]]] */
void loadX();
void loadY();
void loadWidth();
void loadHeight();
void loadReqServerPortNumber();
void loadClientServerName();
void loadIsClientConnectLocal();
void loadIsAutoStartServer();
void loadClientPortNumber();
void loadIsAutoConnectClient();

//[[[end]]]

void startClient(const QString &serverName, int portNumber);

MidiServerClass msc{};
MidiClientClass mcc{};
void updateServerStatus();

};
