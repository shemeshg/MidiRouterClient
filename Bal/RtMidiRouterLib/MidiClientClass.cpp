#include "MidiClientClass.h"
#include <QDebug>
#include <QJSEngine>

MidiClientClass::MidiClientClass(QObject *parent)
    : QObject(parent)
{
    CWebChannelConnection::connect(qwebsocket, &QWebSocket::disconnected, [=] {
        if (midiClientConnection->serverStatus()
            == MidiClientConnectionPrivate::ServerStatus::STARTING) {
            return;
        }
        midiClientConnection->setServerStatusAndText(
            MidiClientConnectionPrivate::ServerStatus::STOPPED);
        qDebug() << "Disconnected";
        qwebsocketClient =
            new CWebChannelClient(qwebsocket);
    });

    qDebug()<<"Created MidiClientClass";
}

void MidiClientClass::start(const QString &serverName, int portNumber)
{

    qDebug() << "client " << serverName << " port " << portNumber;
    QString connectionString = "ws://%1:%2";
    connectionString = connectionString.arg(serverName).arg(portNumber);

    qwebsocket->open(QUrl(connectionString));

    constexpr int msecTimeout = 1000;
    qDebug() << "opening ";
    midiClientConnection->setServerStatusAndText(MidiClientConnectionPrivate::ServerStatus::STARTING);
    if (WaitForSignal(qwebsocket, &QWebSocket::connected, msecTimeout)) {
        qDebug() << "connected.";

        qwebsocketClient->initialize();
        if (WaitForSignal(qwebsocketClient, &CWebChannelClient::initialized)) {
            qDebug() << "Initialized";
            midiClientConnection->setServerStatusAndText(
                MidiClientConnectionPrivate::ServerStatus::RUNNING);
            midiClientConnection->setServerStatusText("Running " + serverName + " "
                                                     + QString::number(portNumber));

            runUserDataChanges();

            QPointer<CWebChannelConnection> wcuserdataCallbacks;
            wcuserdataCallbacks = qwebsocketClient->connect("wcuserdata", "userDataChanges");
            connect(wcuserdataCallbacks,
                &CWebChannelConnection::signal,
                this,
                &MidiClientClass::userDataChanges);


            QPointer<CWebChannelConnection> dataToClientCallback;
            dataToClientCallback = qwebsocketClient->connect("wcmidiin", "dataToClient");

            connect(dataToClientCallback,
                    &CWebChannelConnection::signal,
                    this,
                    &MidiClientClass::dataToClient);


            // End testing
        } else {
            midiClientConnection->setServerStatusAndText(
                MidiClientConnectionPrivate::ServerStatus::FAILED);
            qDebug() << "Did not Initialized";
        }
    } else {
        qDebug() << "Could not connect.";
        midiClientConnection->setServerStatusAndText(
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

void MidiClientClass::userDataChanges(const QJsonArray& message){
    midiClientConnection->userDataConfig()->resetUserDataConfig(message);
}

void MidiClientClass::runUserDataChanges(){

    auto resopnse1 = qwebsocketClient->invokeMethodBlocking("wcuserdata", "getJon", {});
    /*
    resopnse1->connect(resopnse1, &CWebChannelResponse::result, [=](const QJsonValue& message)
            {
                midiClientConnection.userDataConfig()->resetUserDataConfig(message);
            });
    */
   midiClientConnection->userDataConfig()->resetUserDataConfig(resopnse1);
}


void MidiClientClass::dataToClient(const QJsonArray& message)
{   for (const auto &obj:  message){
        if (obj.isString()){
            QString str = obj.toString();
            auto  itemObj = QJsonDocument::fromJson(str.toUtf8());

            auto inputObj = midiClientConnection->userDataConfig()->activePreset()->getInputOrCreateByName(itemObj["portName"].toString());
            inputObj->monitor()->addLogItem(str);
        }
    }

}

