#include "MidiServerClass.h"

#include "./libs/websocket/websocketclientwrapper.h"
#include "./libs/websocket/websockettransport.h"

#include <QCoreApplication>
#include <QWebChannel>
#include <QWebSocketServer>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>
#include <QSettings>

#include "webchannel/wcmidiout.h"
#include "webchannel/wcmidiin.h"
#include "webchannel/wcuserdata.h"

using namespace Webchannel;

MidiServerClass::MidiServerClass() {}

void MidiServerClass::connectAndExec()
{
    QWebSocketServer *server = new QWebSocketServer(QStringLiteral(
                                                        "QWebChannel Standalone Example Server"),
                                                    QWebSocketServer::NonSecureMode);
    if (!server->listen(QHostAddress::Any, port)) {
        //qFatal("Failed to open web socket server.");
        serverIsRunning = false;
    } else {
        serverIsRunning = true;
    }

    if (!serverIsRunning){
        return;
    }

    // wrap WebSocket clients in QWebChannelAbstractTransport objects
    WebSocketClientWrapper *clientWrapper=new WebSocketClientWrapper(server); //NOLINT

    // setup the channel
    QWebChannel *channel=new QWebChannel(); //NOLINT
    QObject::connect(clientWrapper, &WebSocketClientWrapper::clientConnected,
                     channel, &QWebChannel::connectTo);

    // setup the dialog and publish it to the QWebChannel
    WcMidiOut *wcmidiout = new WcMidiOut(); //NOLINT
    channel->registerObject(QStringLiteral("wcmidiout"), wcmidiout);
    WcMidiIn *wcmidiin = new WcMidiIn(); //NOLINT
    channel->registerObject(QStringLiteral("wcmidiin"), wcmidiin);
    WcUserData *wcuserdata = new WcUserData(); //NOLINT
    channel->registerObject(QStringLiteral("wcuserdata"), wcuserdata);
    //QObject::connect(wcuserdata, SIGNAL(applicationQuitSignal()), &app, SLOT(quit()));
}
