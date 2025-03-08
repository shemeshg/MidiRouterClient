#pragma once
#include<QObject>
#include "QtWebSockets/qwebsocketserver.h"

class MidiServerClass: public QObject
{
    Q_OBJECT
public:
<<<<<<< HEAD
    MidiServerClass(QObject *parent = nullptr):QObject(parent){}


=======
    MidiServerClass(QObject *parent):QObject(parent){}
>>>>>>> e1c2bc8 (memory parent issues)
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


