#include "MidiClientClass.h"
#include <QDebug>
#include <QJSEngine>

MidiClientClass::MidiClientClass()
{
    CWebChannelConnection::connect(qwebsocket.get(), &QWebSocket::disconnected, [=] {
        qDebug() << "Disconnected";
    });
}

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
            QJsonValue outports = qwebsocketClient->invokeMethodBlocking("wcmidiout",
                                                                         "getPortCount",
                                                                         {});
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

void MidiClientClass::invokeMethod(const QString &object,
                                   const QString &method,
                                   const QJsonArray &args,
                                   bool isResponse,
                                   const QJSValue &callback,
                                   QJSEngine *engine)
{
    if (isResponse) {
        auto resopnse1 = qwebsocketClient->invokeMethod(object, method, args);
        resopnse1->connect(resopnse1, &CWebChannelResponse::result, [=](const QJsonValue &message) {
            QJSValue cbCopy(callback);
            cbCopy.call(QJSValueList{engine->toScriptValue(message)});
        });
    } else {
        qwebsocketClient->invokeNoResponseMethod(object, method, args);
    }
}
