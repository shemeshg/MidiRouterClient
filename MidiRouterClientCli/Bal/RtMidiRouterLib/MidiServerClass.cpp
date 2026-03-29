#include "MidiServerClass.h"

#include "./libs/websocket/websocketclientwrapper.h"

#include <QWebChannel>

#include "webchannel/wcmidiout.h"
#include "webchannel/wcmidiin.h"
#include "webchannel/wcuserdata.h"

#include <QDir>
#include <QSettings>
#include <QStandardPaths>

using namespace Webchannel;


void MidiServerClass::start(int portNumber)
{
    if (serverIsRunning) {
        return;
    }
    server = new QWebSocketServer(QStringLiteral("QWebChannel Standalone Example Server"),
                                  QWebSocketServer::NonSecureMode);

    // wrap WebSocket clients in QWebChannelAbstractTransport objects
    WebSocketClientWrapper *clientWrapper = new WebSocketClientWrapper(server, this); //NOLINT

    // setup the channel
    QWebChannel *channel = new QWebChannel(server); //NOLINT
    QObject::connect(clientWrapper,
                     &WebSocketClientWrapper::clientConnected,
                     channel,
                     &QWebChannel::connectTo);

    // setup the dialog and publish it to the QWebChannel
    WcMidiOut *wcmidiout = new WcMidiOut(server); //NOLINT
    channel->registerObject(QStringLiteral("wcmidiout"), wcmidiout);
    WcMidiIn *wcmidiin = new WcMidiIn(server); //NOLINT
    channel->registerObject(QStringLiteral("wcmidiin"), wcmidiin);
    WcUserData *wcuserdata = new WcUserData(
        getIsSaveConfigOnServer(),
        getConfigFilePath(),
        wcmidiin, wcmidiout, server); //NOLINT
    channel->registerObject(QStringLiteral("wcuserdata"), wcuserdata);
    //QObject::connect(wcuserdata, SIGNAL(applicationQuitSignal()), &app, SLOT(quit()));

    QObject::connect(wcmidiin, &WcMidiIn::presetOnOff, wcuserdata, &WcUserData::presetOnOff);


    if (!server->listen(QHostAddress::Any, portNumber)) {
        //qFatal("Failed to open web socket server.");
        serverIsRunning = false;
    } else {
        serverIsRunning = true;
        port = server->serverPort();
    }

    if (!serverIsRunning){
        return;
    }
}

void MidiServerClass::stop()
{
    if (serverIsRunning) {
        delete server;
        serverIsRunning = false;
    }
}

const QString MidiServerClass::getConfigFilePath()
{
    if (isCustomConfigFilePath) {
        return customConfigFilePath;
    }

    QString cacheFolderPath = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation);

    QDir dir(cacheFolderPath);
    QString filePath = dir.filePath("midiRouterClient.json");
    return filePath;
}

const bool MidiServerClass::getIsSaveConfigOnServer()
{
    if (isCustomConfigFilePath) {return true;}
#ifdef Q_OS_WIN
    QSettings settings{QSettings::IniFormat, QSettings::UserScope,"shemeshg", "MidiRouterClient"};
#else
    QSettings settings{"shemeshg", "MidiRouterClient"};
#endif

    return settings.value("isSaveConfigOnServer", true).toBool();
}
