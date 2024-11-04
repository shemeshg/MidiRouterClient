#include "UserDataConfig.h"
#include <QSettings>
#include "MidiClientUtil.h"

void UserDataConfig::loadComputerUuid()
{
    QSettings settings;
    QString s = settings.value("computerUuid", "").toString();
    if (s.isEmpty()) {
        s = getUuId();
        settings.setValue("computerUuid", s);
    }
    m_computerUuid = s;
}

void UserDataConfig::clearDropdownlists()
{
    for (const QList<Dropdownlist *> &innerList : m_dropdownlists) {
        for (Dropdownlist *item : innerList) {
            delete item;
        }
    }
    // Clear the outer list
    m_dropdownlists.clear();
}

void UserDataConfig::setChanges(QJsonDocument &jsonDoc){
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

UserDataConfig::UserDataConfig(QObject *parent)
    : UserDataConfigPrivate{parent}
{
    setActivePresetID(0);
    loadComputerUuid();
    m_uniqueId = getUuId();

    clearDropdownlists();
    Dropdownlist *d = new Dropdownlist();
    d->setData("my data1");
    d->setName("my name1");

    QList<Dropdownlist *> l;
    l.push_back(d);
    d = new Dropdownlist();
    d->setData("my data2");
    d->setName("my name2");
    l.push_back(d);

    m_dropdownlists.push_back(l);

    m_virtualInPorts = {"shalom", "olam"};
}
