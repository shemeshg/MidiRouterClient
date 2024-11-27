#pragma once
#include <QJSValue>
#include <QString>
#include "MidiClient/MidiClientConnection.h"
#include "QtWebSockets/qwebsocket.h"
#include "QtWebSockets/qwebsocketserver.h"
#include "libs/QWebchannelCppClient/WebChannelClient.h"

class MidiClientClass: public QObject
{
public:
    MidiClientClass(QObject *parent = nullptr);
    ~MidiClientClass() { stop(); }
    void start(const QString &serverName, int portNumber);
    void stop();
    int getPort(){
        return port;
    }
    bool getClientIsRunning(){
        return clientIsRunning;
    }

    void invokeMethod(const QString &object,
                      const QString &method,
                      const QJsonArray &args,
                      bool isResponse,
                      const QJSValue &callback,
                      QJSEngine *engine);

    MidiClientConnection midiClientConnection{};


private slots:
    void userDataChanges(const QJsonArray& message);
    void dataToClient(const QJsonArray &message);

private:
    int port = -1;
    bool clientIsRunning = false;

    std::unique_ptr<QWebSocket> qwebsocket = std::unique_ptr<QWebSocket>(new QWebSocket());
    std::unique_ptr<CWebChannelClient> qwebsocketClient = std::unique_ptr<CWebChannelClient>(
        new CWebChannelClient(qwebsocket.get()));

    void runUserDataChanges();
};
