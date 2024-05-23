#pragma once

#include <QObject>
#include <QVariant>
#include <QJsonObject>

class WcUserData : public QObject
{
    Q_OBJECT
public:
    explicit WcUserData(QObject *parent = nullptr);
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
signals:
    bool userDataChanges(QVariant msg);
    void applicationQuitSignal();
};


