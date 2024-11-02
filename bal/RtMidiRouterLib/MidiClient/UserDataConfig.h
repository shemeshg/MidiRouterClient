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

    void resetUserDataConfig(QJsonValue jsonData){

        QJsonDocument jsonDoc = QJsonDocument::fromVariant(jsonData.toVariant());
        qDebug() << "json[" <<  jsonDoc.toJson() << "]";
        qDebug()<<"check if this is not our ID";
    }
public slots:

private:
    void loadComputerUuid();
    void clearDropdownlists();
};
