#pragma once

#include "QtWebSockets/qwebsocketserver.h"

class MidiServerClass
{
public:
    MidiServerClass();
    ~MidiServerClass() {
        delete server;
        stop();
    }
    void start(int portNumber);
    void stop();
    int getPort(){
        return port;
    }
    bool getServerIsRunning(){
        return serverIsRunning;
    }
private:
    int port = -1;
    bool serverIsRunning = false;
    QWebSocketServer *server;
};


