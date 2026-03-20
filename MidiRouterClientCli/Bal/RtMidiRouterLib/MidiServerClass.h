#pragma once
#include<QObject>
#include "QtWebSockets/qwebsocketserver.h"


class MidiServerClass: public QObject
{
    Q_OBJECT
public:

    MidiServerClass(QObject *parent):QObject(parent){}
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

    void setConfigFilePath(const QString &s){
        isCustomConfigFilePath = true;
        customConfigFilePath = s;
    }
    const QString getConfigFilePath();
    const bool getIsSaveConfigOnServer();

private:
    int port = -1;
    bool serverIsRunning = false;
    QWebSocketServer *server;

    bool isCustomConfigFilePath = false;
    QString customConfigFilePath;


};


