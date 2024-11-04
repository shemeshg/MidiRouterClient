#pragma once
#include "UserDataConfigPrivate.h"
#include <QJsonValue>
#include <QtCore/qjsonarray.h>
#include <QtCore/qjsondocument.h>
#include <QtCore/qjsonobject.h>

class UserDataConfig : public UserDataConfigPrivate

{
    Q_OBJECT    
    QML_ELEMENT
public:
    explicit UserDataConfig(QObject *parent = nullptr);

    virtual ~UserDataConfig() { clearDropdownlists(); }

    void resetUserDataConfig(const QJsonValue &jsonData){
        QJsonDocument jsonDoc = QJsonDocument::fromVariant(jsonData.toVariant());        
        if (jsonDoc["uniqueId"].isString() && jsonDoc["uniqueId"].toString() != computerUuid()){
            setChanges(jsonDoc);
        }
    }


public slots:

private:
    void loadComputerUuid();
    void clearDropdownlists();

    void  setChanges(QJsonDocument &jsonDoc){
        qDebug()<<"Empllay remote configuration";
        qDebug() << "json[" <<  jsonDoc.toJson().replace("\\n", "\n") << "]";

        if (jsonDoc["virtualInPorts"].isArray()){
            m_virtualInPorts = {};

            for (const QJsonValue &value : jsonDoc["virtualInPorts"].toArray()) {
                m_virtualInPorts.append(value.toString());
            }
            emit virtualInPortsChanged();
        }
        //qDebug()<<"virtualInPorts are:" << m_virtualInPorts;


        if (jsonDoc["_activePresetID"].isDouble()){
            setActivePresetID(jsonDoc["_activePresetID"].toInt());
        }
        //dropdownlists
    }
};
