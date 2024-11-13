#include "MidiClientClass.h"
#include <QDebug>
#include <QJSEngine>

MidiClientClass::MidiClientClass(QObject *parent)
    : QObject(parent)
{
    CWebChannelConnection::connect(qwebsocket.get(), &QWebSocket::disconnected, [=] {
        if (midiClientConnection.serverStatus()
            == MidiClientConnectionPrivate::ServerStatus::STARTING) {
            return;
        }
        midiClientConnection.setServerStatusAndText(
            MidiClientConnectionPrivate::ServerStatus::STOPPED);
        qDebug() << "Disconnected";
        qwebsocketClient = std::unique_ptr<CWebChannelClient>(
            new CWebChannelClient(qwebsocket.get()));
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
    midiClientConnection.setServerStatusAndText(MidiClientConnectionPrivate::ServerStatus::STARTING);
    if (WaitForSignal(qwebsocket.get(), &QWebSocket::connected, msecTimeout)) {
        qDebug() << "connected.";

        qwebsocketClient->initialize();
        if (WaitForSignal(qwebsocketClient.get(), &CWebChannelClient::initialized)) {
            qDebug() << "Initialized";
            midiClientConnection.setServerStatusAndText(
                MidiClientConnectionPrivate::ServerStatus::RUNNING);
            midiClientConnection.setServerStatusText("Running " + serverName + " "
                                                     + QString::number(portNumber));

            userDataChanges();

            QPointer<CWebChannelConnection> wcuserdataCallbacks;
            wcuserdataCallbacks = qwebsocketClient->connect("wcuserdata", "userDataChanges");
            connect(wcuserdataCallbacks,
                &CWebChannelConnection::signal,
                this,
                &MidiClientClass::userDataChanges);



            // End testing
        } else {
            midiClientConnection.setServerStatusAndText(
                MidiClientConnectionPrivate::ServerStatus::FAILED);
            qDebug() << "Did not Initialized";
        }
    } else {
        qDebug() << "Could not connect.";
        midiClientConnection.setServerStatusAndText(
            MidiClientConnectionPrivate::ServerStatus::FAILED);
    }
}

void MidiClientClass::stop()
{
    qwebsocket->close();
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

void MidiClientClass::userDataChanges(){
    auto resopnse1 = qwebsocketClient->invokeMethod("wcuserdata", "getJon", {});
    resopnse1->connect(resopnse1, &CWebChannelResponse::result, [=](const QJsonValue& message)
            {
                midiClientConnection.userDataConfig()->resetUserDataConfig(message);
            });
}