#pragma once

#include <QObject>
#include <QVariant>
#include <QJsonObject>
#include <QStandardPaths>
#include <QDir>
#include <QSettings>
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

    virtual ~WcUserData(){
        if (isSaveConfigOnServer) {
            auto o = userdata.toJsonObject();
            QJsonDocument jsonDoc(o);
            QString s = jsonDoc.toJson(QJsonDocument::Compact);
            cashFileWrite(cahedFileName, s);

            qDebug()<<isSaveConfigOnServer;
            qDebug()<<"Cash path is "<<QStandardPaths::writableLocation(QStandardPaths::CacheLocation);

        }
    }

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
        auto json = userdata.toJsonObject();
        ApplyConfig ac(wcmidiin, wcmidiout);
        json = ac.presetOnOff(json, isMidiControlOn, presetUuid);
        applyConfig(json);
        qDebug()<<"WE ARE AT public slots presetOnOff" <<isMidiControlOn;

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

    const QString cahedFileName = "midiRouterClient.json";
    void cashFileWrite(const QString &fileName, QString &fileContent)
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

    QString cashFileRead(const QString &fileName)
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

    QSettings settings;
    bool isSaveConfigOnServer = settings.value("isSaveConfigOnServer", true).toBool();

};


