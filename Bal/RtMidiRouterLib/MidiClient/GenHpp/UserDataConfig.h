#pragma once
#include "../genPrpt/UserDataConfigPrivate.h"
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
    virtual ~UserDataConfig();
    void resetUserDataConfig(const QJsonValue &jsonData);
    void clearVirtualPorts();
    void addVirtualPort(QString port);
    void addDropdownList(QString name, QString data);
public slots:
    QJsonObject getJson();
    void setActivePreset(int id);
    void addPreset();
    void deletePreset(int id);
private:
    void loadComputerUuid();
};
