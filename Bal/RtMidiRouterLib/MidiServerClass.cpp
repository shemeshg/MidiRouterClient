#include "MidiServerClass.h"

#include "./libs/websocket/websocketclientwrapper.h"

#include <QWebChannel>

#include "webchannel/wcmidiout.h"
#include "webchannel/wcmidiin.h"
#include "webchannel/wcuserdata.h"

using namespace Webchannel;

MidiServerClass::MidiServerClass() {}

void MidiServerClass::start(int portNumber)
{
    if (serverIsRunning) {
        return;
    }
    server = new QWebSocketServer(QStringLiteral("QWebChannel Standalone Example Server"),
                                  QWebSocketServer::NonSecureMode);

    // wrap WebSocket clients in QWebChannelAbstractTransport objects
    WebSocketClientWrapper *clientWrapper = new WebSocketClientWrapper(server); //NOLINT

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
    WcUserData *wcuserdata = new WcUserData(wcmidiin, wcmidiout, server); //NOLINT
    channel->registerObject(QStringLiteral("wcuserdata"), wcuserdata);
    //QObject::connect(wcuserdata, SIGNAL(applicationQuitSignal()), &app, SLOT(quit()));

    //void presetOnOff(bool isMidiControlOn, QString presetUuid);
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
        serverIsRunning = false;
    }
}
