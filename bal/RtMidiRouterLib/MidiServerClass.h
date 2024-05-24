#pragma once

#include <QObject>
#include "QtWebSockets/qwebsocketserver.h"

class WebSocketTransport;

QT_BEGIN_NAMESPACE
class QWebSocketServer;
QT_END_NAMESPACE

class MidiServerClass
{
public:
    MidiServerClass();
    ~MidiServerClass() { stop(); }
    void start();
    void stop();
    int getPort(){
        return port;
    }
    bool getServerIsRunning(){
        return serverIsRunning;
    }
private:
    int port = 12345;
    bool serverIsRunning = false;
    QWebSocketServer *server;
};


