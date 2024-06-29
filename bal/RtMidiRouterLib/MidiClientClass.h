#pragma once
#include <QString>

class MidiClientClass
{
public:
    MidiClientClass();
    ~MidiClientClass() { stop(); }
    void start(const QString &serverName, int portNumber);
    void stop();
    int getPort(){
        return port;
    }
    bool getClientIsRunning(){
        return clientIsRunning;
    }
private:
    int port = -1;
    bool clientIsRunning = false;
    //QWebSocketServer *server;
};
