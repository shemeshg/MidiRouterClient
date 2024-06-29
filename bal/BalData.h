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

//[[[end]]]

void startServer(int portNumber);
void stopServer();

void startClient(const QString &serverName, int portNumber);
void stopClient();
void testDummyDelete(const QJSValue &callback);

MidiClientConnection *midiClientConnection() { return &mcc.midiClientConnection; }

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

//[[[end]]]
MidiServerClass msc{};
MidiClientClass mcc{};
void updateServerStatus();
};
