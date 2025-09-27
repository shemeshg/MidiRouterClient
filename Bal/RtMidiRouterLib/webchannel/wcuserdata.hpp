//-define-file body webchannel/wcuserdata.cpp
//-define-file header webchannel/wcuserdata.h
//-only-file header //-
#pragma once

#include <QObject>
#include <QVariant>
#include <QJsonObject>
#include <QStandardPaths>
#include <QDir>
#include <QSettings>
#include "wcmidiin.h"
#include "wcmidiout.h"
//- {include-header}
#include "ApplyConfig.hpp" //- #include "ApplyConfig.h"

//-only-file body //-
//- #include "wcuserdata.h"

//-only-file header
//-var {PRE} "WcUserData::"
class WcUserData : public QObject
{
    Q_OBJECT
public:
    //- {function} 1 1
    explicit WcUserData(Webchannel::WcMidiIn *wcmidiin,
                        Webchannel::WcMidiOut *wcmidiout,
                        QObject *parent)
    //-only-file body
        :wcmidiin{wcmidiin},
        wcmidiout{wcmidiout},
        QObject(parent)
    {

        applayConfig.init(wcmidiin,wcmidiout);
        QString str;
        if (isSaveConfigOnServer) {
            str = cashFileRead(cahedFileName);
        }
        if (str.isEmpty()){
            str = R"(
{
    "_activePresetID": 0,
    "appVer": "2.4.0",
    "connectedInPorts": [
    ],
    "connectedOutPorts": [
    ],
    "dropdownlists": [],
    "midiRoutePresets": [
        {
            "isEnabled": true,
            "midiControlOff": {
                "channel": -1,
                "data1": -1,
                "data2": -1,
                "eventTypeId": 0,
                "portName": "",
                "presetMidiType": 0
            },
            "midiControlOn": {
                "channel": -1,
                "data1": -1,
                "data2": -1,
                "eventTypeId": 0,
                "portName": "",
                "presetMidiType": 1
            },
            "midiControlSelect": {
                "channel": -1,
                "data1": -1,
                "data2": -1,
                "eventTypeId": 0,
                "portName": "",
                "presetMidiType": 3
            },
            "midiControlToggle": {
                "channel": -1,
                "data1": -1,
                "data2": -1,
                "eventTypeId": 0,
                "portName": "",
                "presetMidiType": 2
            },
            "midiRouteInputs": [],
            "name": "Preset 0",
            "userControls": [],
            "uuid": "f4c3edd5-446d-464b-91eb-20cb375e57b3"
        }
    ],
    "uniqueId": "f58983da-9054-4273-9a74-7d7f8158cd3e",
    "virtualInPorts": []
}
            )";
        }



        QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
        if (isSaveConfigOnServer && doc.isNull()){
            str = "{\"criticalError\": true}";
            doc = QJsonDocument::fromJson(str.toUtf8());
        }

        userdata = doc.object();

        if (isSaveConfigOnServer) {
            auto d = doc.object();
            d["uniqueId"] = 0;
            applyConfig(d);

        }

    }

    //- {function} 1 1
    virtual ~WcUserData()
    //-only-file body
    {
        isSaveConfigOnServer = settings.value("isSaveConfigOnServer", true).toBool();
        if (isSaveConfigOnServer) {
            auto o = userdata.toJsonObject();
            QJsonDocument jsonDoc(o);
            QString s = jsonDoc.toJson(QJsonDocument::Compact);
            cashFileWrite(cahedFileName, s);            
        }
    }

    //-only-file header
    QVariant userdata;
public slots:
    //- {fn}
    void setJon(QVariant msg)
    //-only-file body
    {

        userdata = msg;
        emit userDataChanges(getJon());
    }

    //- {fn}
    QVariant getJon()
    //-only-file body
    {
        auto json = userdata.toJsonObject();
        QStringList inPorts=getMapStringVal(wcmidiin->getPorts());
        QStringList outPorts=getMapStringVal(wcmidiout->getPorts());

        json["connectedInPorts"] = QJsonArray::fromStringList(inPorts);
        json["connectedOutPorts"] = QJsonArray::fromStringList(outPorts);
        userdata = json.toVariantMap();
        return userdata;

    }

    //- {fn}
    void applicationQuit()
    //-only-file body
    {
        emit applicationQuitSignal();

    }

    //- {fn}
    QJsonObject applyConfig( QString s)
    //-only-file body
    {

        QJsonDocument jsonDoc = QJsonDocument::fromJson(s.toUtf8());

        auto o = jsonDoc.object();
        wcmidiin->listenersStop();
        auto ret = applayConfig.applyConfig(o);
        wcmidiin->listenersStart();
        setJon(o);
        return ret;
    }

    //- {fn}
    QJsonObject applyConfig( QJsonObject json)
    //-only-file body
    {
        wcmidiin->listenersStop();
        auto ret = applayConfig.applyConfig(json);
        wcmidiin->listenersStart();
        json["criticalError"] = applayConfig.criticalError;
        setJon(json);
        return ret;
    }



    //- {fn}
    void presetOnOff(int presetMidiType, QString presetUuid)
    //-only-file body
    {

        if (presetMidiType == 3){
            auto json = userdata.toJsonObject();
            applayConfig.selectPreset(json, presetOnOffStatus,presetUuid);
        } else if (presetMidiType == 2){
            auto json = userdata.toJsonObject();
            applayConfig.togglePreset(json, presetOnOffStatus,presetUuid);
        } else  {
            presetOnOffStatus[presetUuid] = presetMidiType;
        }



        if (isInPresetOnOff){return;}
        wcmidiin->listenersStop();
        isInPresetOnOff = true;
        QTimer::singleShot(10, [=]() {
            auto json = userdata.toJsonObject();
            auto j = applayConfig.presetOnOff(json, presetOnOffStatus);
            j["uniqueId"] = uniqueId++;
            applyConfig(j);
            isInPresetOnOff = false;
        });






    }

    //-only-file header
signals:
    bool userDataChanges(QVariant msg);
    void applicationQuitSignal();
private:
    Webchannel::WcMidiIn *wcmidiin;
    Webchannel::WcMidiOut *wcmidiout;
    ApplyConfig applayConfig;

    int uniqueId = 1;
    QMap<QString, int> presetOnOffStatus;
    std::atomic<bool> isInPresetOnOff = false;


    //- {fn}
    QStringList getMapStringVal(QVariantMap map)
    //-only-file body
    {
        QStringList list;
        for (auto it = map.begin(); it != map.end(); ++it) {
            list.append(it.value().toString());
        }
        return list;
    }

    //-only-file header
    const QString cahedFileName = "midiRouterClient.json";

    //- {fn}
    void cashFileWrite(const QString &fileName, QString &fileContent)
    //-only-file body
    {
        QString cacheFolderPath = QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
        QString filePath = cacheFolderPath + QDir::separator() + fileName;
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << fileContent;
            file.close();
        }
    }

    //- {fn}
    QString cashFileRead(const QString &fileName)
    //-only-file body
    {
        QString cacheFolderPath = QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
        QString filePath = cacheFolderPath + QDir::separator() + fileName;

        QString fileContent;
        // Check if the file exists
        if (QFile::exists(filePath)) {
            QFile file(filePath);
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream stream(&file);
                fileContent = stream.readAll();
                file.close();
            }
        }
        return fileContent;
    }

    //-only-file header
    QSettings settings{"shemeshg", "MidiRouterClient"};
    bool isSaveConfigOnServer = settings.value("isSaveConfigOnServer", false).toBool();

};


