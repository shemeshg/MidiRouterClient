#pragma once
#include "UserDataConfigPrivate.h"
#include <QJsonValue>
#include <QtCore/qjsondocument.h>
#include <QtCore/qjsonobject.h>

class UserDataConfig : public UserDataConfigPrivate

{
    Q_OBJECT    
    QML_ELEMENT
public:
    explicit UserDataConfig(QObject *parent = nullptr);

    virtual ~UserDataConfig() { clearDropdownlists(); }

    void resetUserDataConfig(QJsonValue &jsonData){
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
        qDebug() << "json[" <<  jsonDoc.toJson() << "]";

    }
};
