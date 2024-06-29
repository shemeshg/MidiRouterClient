#include "MidiClientClass.h"
#include <QDebug>

MidiClientClass::MidiClientClass() {}

void MidiClientClass::start(const QString &serverName, int portNumber)
{
    qDebug() << "client " << serverName << " port " << portNumber;
    QString connectionString = "ws://%1:%2";
    connectionString = connectionString.arg(serverName).arg(portNumber);

    qwebsocket->open(QUrl(connectionString));

    constexpr int msecTimeout = 1000;
    qDebug() << "opening ";
    if (WaitForSignal(qwebsocket.get(), &QWebSocket::connected, msecTimeout)) {
        qDebug() << "connected.";

        qwebsocketClient->initialize();
        if (WaitForSignal(qwebsocketClient.get(), &CWebChannelClient::initialized)) {
            qDebug() << "Initialized";
            // Testing
            auto outports = qwebsocketClient->invokeMethodBlocking("wcmidiout", "getPortCount", {});
            qDebug() << "We have " << outports << " out ports";
            // End testing
        } else {
            qDebug() << "Did not Initialized";
        }
    } else {
        qDebug() << "Could not connect.";
    }
}

void MidiClientClass::stop()
{
    qDebug() << "client stopped";
}
