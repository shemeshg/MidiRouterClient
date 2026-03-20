#pragma once
#include "BalDataPrivate.h"
#include "RtMidiRouterLib/MidiClientClass.h"
#include "RtMidiRouterLib/MidiServerClass.h"
#include "config.h"
#include <QSettings>
#include <QFutureWatcher>
#include <QtConcurrent>

class BalData : public BalDataPrivate

{
    Q_OBJECT
    Q_PROPERTY(MidiClientConnection *midiClientConnection READ midiClientConnection CONSTANT)
    QML_ELEMENT
public:
    explicit BalData(QObject *parent = nullptr);

    void startClient(const QString &serverName, int portNumber);

    const QString getServerConfigFilePath(){
        return msc->getConfigFilePath();
    }

    void setServerConfigFilePath(const QString &s){
        msc->setConfigFilePath(s);
    }

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
void saveIsMonitorInExternalDialog(const bool IsMonitorInExternalDialog);
void saveDefaultFontSize(const QString DefaultFontSize);
void saveDefaultHeaderTabSelected(const QString DefaultHeaderTabSelected);

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
void applyConfigEngine(const QJSValue &callback, QJSEngine *engine);
void uploadJson(QString filePath, const QJSValue &callback);
void getPortNumber(const QString &midiPortName, const QJSValue &callback);
void setNonRegisteredParameterInt( int portNumber,int parameter,int data,QStringList channels,const QJSValue &callback);
void sendControlChange( int portNumber,int controller,int value,QStringList channels,const QJSValue &callback);
void sendProgramChange( int portNumber,int program,QStringList channels,const QJSValue &callback);
MidiClientConnection *midiClientConnection() { return mcc->midiClientConnection; }

void startClient();


private:
   #ifdef Q_OS_WIN
    QSettings settings{QSettings::IniFormat, QSettings::SystemScope,"shemeshg", "MidiRouterClient"};
   #else
    QSettings settings{"shemeshg", "MidiRouterClient"};
   #endif

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
void loadIsMonitorInExternalDialog();
void loadDefaultFontSize();
void loadDefaultHeaderTabSelected();

//[[[end]]]



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

template<typename T>
void makeAsync(const QJSValue &callback, std::function<T()> func)
{
    auto *watcher = new QFutureWatcher<T>(this);
    QObject::connect(watcher, &QFutureWatcher<T>::finished, this, [this, watcher, callback]() {
        T returnValue = watcher->result();
        QJSValue cbCopy(callback);
        QJSEngine *engine = qjsEngine(this);
        cbCopy.call(QJSValueList{engine->toScriptValue(returnValue)});
        watcher->deleteLater();
    });
    watcher->setFuture(QtConcurrent::run([=]() { return func(); }));
}

};
