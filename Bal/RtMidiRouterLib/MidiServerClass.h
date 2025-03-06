#pragma once
#include<QObject>
#include "QtWebSockets/qwebsocketserver.h"

class MidiServerClass: public QObject
{
    Q_OBJECT
public:
    MidiServerClass(QObject *parent = nullptr):QObject(parent){}


    ~MidiServerClass() {

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


