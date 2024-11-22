#pragma once

#include <QObject>
#include <QVariant>
#include <QJsonObject>
#include "WcMidiIn.h"
#include "WcMidiOut.h"

class WcUserData : public QObject
{
    Q_OBJECT
public:
    explicit WcUserData(Webchannel::WcMidiIn *wcmidiin,
                        Webchannel::WcMidiOut *wcmidiout,
                        QObject *parent = nullptr);
    QVariant userdata;
public:
    Q_INVOKABLE void setJon(QVariant msg){
        userdata = msg;
        emit userDataChanges(userdata);
    }

    Q_INVOKABLE QVariant getJon(){
        return userdata;

    }

    Q_INVOKABLE void applicationQuit(){
        emit applicationQuitSignal();

    }

    Q_INVOKABLE void applyConfig(QJsonObject json){
        //qDebug()<<"Server will applay a config of "<<json;
        wcmidiin->restart();
        wcmidiout->restart();

        auto inPortsMap = wcmidiin->getPorts();
        auto outPortMap = wcmidiout->getPorts();
        qDebug()<<inPortsMap;
        //setJon(json);
    }
signals:
    bool userDataChanges(QVariant msg);
    void applicationQuitSignal();
private:
    Webchannel::WcMidiIn *wcmidiin;
    Webchannel::WcMidiOut *wcmidiout;
};


