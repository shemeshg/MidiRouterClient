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
//- {include-body}
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


        QString str;
        if (isSaveConfigOnServer) {
            str = cashFileRead(cahedFileName);
        }
        if (str.isEmpty()){
            str = "{}";
        }



        QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
        if (isSaveConfigOnServer && doc.isNull()){
            str = "{\"criticalError\": true}";
            doc = QJsonDocument::fromJson(str.toUtf8());
        }

        userdata = doc.object();

        if (isSaveConfigOnServer) {
            auto d = doc.object();


            QTimer::singleShot(1000, [=]() {
                applyConfig(d);
            });

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
        ApplyConfig ac(wcmidiin, wcmidiout);
        QJsonDocument jsonDoc = QJsonDocument::fromJson(s.toUtf8());

        auto o = jsonDoc.object();
        auto ret = ac.applyConfig(o);
        setJon(o);
        return ret;
    }

    //- {fn}
    QJsonObject applyConfig( QJsonObject json)
    //-only-file body
    {
        ApplyConfig ac(wcmidiin, wcmidiout);
        auto ret = ac.applyConfig(json);
        json["criticalError"] = ac.criticalError;
        setJon(json);
        return ret;
    }



    //- {fn}
    void presetOnOff(int presetMidiType, QString presetUuid)
    //-only-file body
    {        
        presetOnOffStatus[presetUuid] = presetMidiType;
        if (isInPresetOnOff){return;}
        isInPresetOnOff = true;
        QTimer::singleShot(250, [=]() {
            auto json = userdata.toJsonObject();
            ApplyConfig ac(wcmidiin, wcmidiout);
            json = ac.presetOnOff(json, presetOnOffStatus);
            json["uniqueId"] = uniqueId++;
            applyConfig(json);
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


