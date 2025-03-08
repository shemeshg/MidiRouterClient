#pragma once
#include "BalDataPrivate.h"
#include "RtMidiRouterLib/MidiClientClass.h"
#include "RtMidiRouterLib/MidiServerClass.h"
#include "config.h"

class BalData : public BalDataPrivate

{
    Q_OBJECT
    Q_PROPERTY(MidiClientConnection *midiClientConnection READ midiClientConnection CONSTANT)
    QML_ELEMENT
public:
    explicit BalData(QObject *parent = nullptr);


public slots:
    QString qtVer() {
        return "App:" + QString(PROJECT_VER) + " qt:" + qVersion();
    }

    void openCashFolder();

    void queryRemoteMidiPorts(QString serverName, QString serverPort, const QJSValue &callback);
   
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
void saveIsSaveConfigOnServer(const bool IsSaveConfigOnServer);
void saveDefaultFontSize(const QString DefaultFontSize);

//[[[end]]]

void onApplicationStarted();
void startServer(int portNumber);
void stopServer();

void setAsyncServerStatusAndText(MidiClientConnection::ServerStatus serverStatus,
                                 const QJSValue &callback)
{
    makeAsync<bool>(callback, [=]() {
        mcc->midiClientConnection->setServerStatusAndText(serverStatus);
        return true;
    });
}

void stopClient();
void testDummyDelete(const QJSValue &callback);
void applyConfig(const QJSValue &callback);
void getPortNumber(const QString &midiPortName, const QJSValue &callback);
void setNonRegisteredParameterInt( int portNumber,int parameter,int data,QStringList channels,const QJSValue &callback);
void sendControlChange( int portNumber,int controller,int value,QStringList channels,const QJSValue &callback);
void sendProgramChange( int portNumber,int program,QStringList channels,const QJSValue &callback);
MidiClientConnection *midiClientConnection() { return mcc->midiClientConnection; }

void startClient();

private:
QSettings settings{"shemeshg", "MidiRouterClient"};

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
void loadIsSaveConfigOnServer();
void loadDefaultFontSize();

//[[[end]]]

void startClient(const QString &serverName, int portNumber);


MidiServerClass *msc= new MidiServerClass(this);
MidiClientClass *mcc = new MidiClientClass(this);
MidiClientClass *remoteMcc = new MidiClientClass(this);

void updateServerStatus();


QJsonArray getListToJsonAry(const QStringList &sl)
{
    QJsonArray ary;
    for (const auto &itm: sl){
        ary.append(itm);
    }
    return ary;
}

};
