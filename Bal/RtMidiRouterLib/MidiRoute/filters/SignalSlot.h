#pragma once
#include <QObject>
#include <QDebug>
#include <iostream>
#include <QWebSocket>
#include "libs/QWebchannelCppClient/WebChannelClient.h"
#include "RtMidiWrap/midievent.h"

#include "RtMidiWrap/playmidiout.h"

class SignalSlotClass : public QObject
{
    Q_OBJECT
public:
    // Remote server
    std::unique_ptr<QWebSocket> opendRemoteServersSockets;
    std::unique_ptr<CWebChannelClient> opendRemoteServers;
    QString connectionString;
    int remoteMidiPortNumber;

    void openConnection(QString serverName, int serverPort, int _remoteMidiPortNumber){

               remoteMidiPortNumber = _remoteMidiPortNumber;
               connectionString = "ws://%1:%2";
               connectionString = connectionString.arg( serverName).arg(serverPort);

               opendRemoteServersSockets = std::unique_ptr<QWebSocket>(new QWebSocket());
               opendRemoteServers = std::unique_ptr<CWebChannelClient>(new CWebChannelClient(opendRemoteServersSockets.get()));

               opendRemoteServersSockets->open(QUrl( connectionString ));

               constexpr int msecTimeout = 100;
               if (WaitForSignal(opendRemoteServersSockets.get(), &QWebSocket::connected, msecTimeout)){
                   qDebug() << "connected.";

                   opendRemoteServers->initialize();
                   if (WaitForSignal(opendRemoteServers.get(), &CWebChannelClient::initialized))
                   {
                       opendRemoteServers->invokeMethodBlocking("wcmidiout", "openPort", {remoteMidiPortNumber});
                       qDebug() << "Initialized";
                   } else {
                       qDebug() << "Did not Initialized";
                   }

               }


    }

    // Local Ports
    std::unique_ptr<RtMidiWrap::PlayMidiOut> alreadyOpenedMidiOut = std::unique_ptr<RtMidiWrap::PlayMidiOut>(new RtMidiWrap::PlayMidiOut());
    void openPort(std::string portName){
        alreadyOpenedMidiOut->openPort(portName);
    }
    void openPort(int portNumber){
        alreadyOpenedMidiOut->openPort(portNumber);

    }
public slots:

    void invokeMethod(QString connectionString , int remoteMidiPortNumber, QString obj, QString method, QJsonArray args){

        if (connectionString != this->connectionString || remoteMidiPortNumber != this->remoteMidiPortNumber){
            return;
        }

        opendRemoteServers->invokeMethod(obj, method, args);

    }
    void sendMessage(std::vector<BYTE> msg){
        alreadyOpenedMidiOut->sendMessage(&msg);
    }

    void setNonRegisteredParameterInt( int parameter, int data, std::vector<BYTE> channels){
        alreadyOpenedMidiOut->setNonRegisteredParameterInt(parameter, data, channels);
    }
};


class SignalClass : public QObject
{
    Q_OBJECT
public:
    SignalClass(SignalSlotClass &s, QObject *Parent = 0)
            : QObject(Parent)
        {

            connect(this, SIGNAL(invokeMethod(QString,int,QString,QString,QJsonArray)), &s,
                    SLOT(invokeMethod(QString,int,QString,QString,QJsonArray)));
            qRegisterMetaType< std::vector<BYTE> >( "std::vector<BYTE>" );
            connect(this, SIGNAL(sendMessage(std::vector<BYTE>)), &s, SLOT(sendMessage(std::vector<BYTE>)));
            connect(this, SIGNAL(setNonRegisteredParameterInt(int,int,std::vector<BYTE>)), &s, SLOT(setNonRegisteredParameterInt(int,int,std::vector<BYTE>)));
        }

    void sendRemoteServer(RtMidiWrap::MidiEvent &m, std::string &serverName, int serverPort, int remoteMidiPortNumber){
        QString connectionString = "ws://%1:%2";
        connectionString = connectionString.arg( QString::fromStdString(serverName)).arg(serverPort);

        QJsonArray message;
        for ( unsigned int i=0; i<m.data.size(); i++)
                message.push_back((int)m.data[i]);

        emit invokeMethod( connectionString, remoteMidiPortNumber, "wcmidiout", "sendMessage", {remoteMidiPortNumber, message});
    }

    void doTest(QString in){
         emit test(in);
    }

    void doSendMessage(std::vector<BYTE> &msg){
        emit sendMessage(msg);
    }

    void doSetNonRegisteredParameterInt(int parameter, int data, std::vector<BYTE> channels){
        emit setNonRegisteredParameterInt(parameter, data, channels);
    }
signals:
    void test(QString in);
    void invokeMethod(QString connectionString , int remoteMidiPortNumber, QString obj, QString method, QJsonArray args);
    void sendMessage(std::vector<BYTE> msg);
    void setNonRegisteredParameterInt( int parameter, int data, std::vector<BYTE> channels);
};



