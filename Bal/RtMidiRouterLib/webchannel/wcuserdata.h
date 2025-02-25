#pragma once

#include <QObject>
#include <QVariant>
#include <QJsonObject>
#include "wcmidiin.h"
#include "wcmidiout.h"
#include "ApplyConfig.h"

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
        emit userDataChanges(getJon());
    }

    Q_INVOKABLE QVariant getJon(){
        auto json = userdata.toJsonObject();
        QStringList inPorts=getMapStringVal(wcmidiin->getPorts());
        QStringList outPorts=getMapStringVal(wcmidiout->getPorts());

        json["connectedInPorts"] = QJsonArray::fromStringList(inPorts);
        json["connectedOutPorts"] = QJsonArray::fromStringList(outPorts);
        userdata = json.toVariantMap();
        return userdata;

    }

    Q_INVOKABLE void applicationQuit(){
        emit applicationQuitSignal();

    }

    Q_INVOKABLE QJsonObject applyConfig(const QJsonObject &json){
        ApplyConfig ac(wcmidiin, wcmidiout);
        auto ret = ac.applyConfig(json);
        setJon(json);
        return ret;
    }

public slots:
    void presetOnOff(bool isMidiControlOn, QString presetUuid){
        qDebug()<<"WE ARE AT public slots presetOnOff";
    }
signals:
    bool userDataChanges(QVariant msg);
    void applicationQuitSignal();
private:
    Webchannel::WcMidiIn *wcmidiin;
    Webchannel::WcMidiOut *wcmidiout;

    QStringList getMapStringVal(QVariantMap map){
        QStringList list;
        for (auto it = map.begin(); it != map.end(); ++it) {
            list.append(it.value().toString());
        }
        return list;
    }
};


