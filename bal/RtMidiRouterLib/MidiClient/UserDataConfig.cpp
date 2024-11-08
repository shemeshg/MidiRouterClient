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
    for (const Dropdownlist *item : m_dropdownlists) {
            delete item;
    }
    // Clear the outer list
    m_dropdownlists.clear();
}

void UserDataConfig::clearMidiRoutePreset()
{
    for (const MidiRoutePreset *item : m_midiRoutePresets) {
        delete item;
    }
    // Clear the outer list
    m_midiRoutePresets.clear();
}

void UserDataConfig::setChanges(QJsonDocument &jsonDoc){
    qDebug()<<"Empllay remote configuration";
    //qDebug() << "json[" <<  jsonDoc.toJson().replace("\\n", "\n") << "]";

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

    clearDropdownlists();
    if (jsonDoc["dropdownlists"].isArray()){
        qDebug()<<"dropdownlists"<<jsonDoc["dropdownlists"];
        for (const QJsonValue &value : jsonDoc["dropdownlists"].toArray()) {
            Dropdownlist *d = new Dropdownlist();
            d->setName(value["name"].toString());
            d->setData(value["data"].toString());
            m_dropdownlists.push_back(d);
        }
        emit dropdownlistsChanged();
    }

    clearMidiRoutePreset();
    if (jsonDoc["midiRoutePresets"].isArray()){
        for (const QJsonValue &value : jsonDoc["midiRoutePresets"].toArray()) {
            MidiRoutePreset *p = new MidiRoutePreset(m_computerUuid);
            p->setName(value["name"].toString());
            m_midiRoutePresets.push_back(p);
        }
        emit midiRoutePresetsChanged();
    }
    /*
    QJsonValue gg = jsonDoc["midiRoutePresets"];
    QJsonArray gg1 =  gg.toArray();
    qDebug()<<"***#####";
    qDebug()<<gg;
    qDebug()<<"***";
    qDebug()<<QJsonDocument(gg1).toJson();
    */
}

UserDataConfig::UserDataConfig(QObject *parent)
    : UserDataConfigPrivate{parent}
{
    setActivePresetID(0);
    loadComputerUuid();
    m_uniqueId = getUuId();

    clearDropdownlists();
    m_virtualInPorts = {};

    clearMidiRoutePreset();
    MidiRoutePreset *p = new MidiRoutePreset(m_computerUuid);
    p->setName("Default preset");
    m_midiRoutePresets.push_back(p);
    emit midiRoutePresetsChanged();
}
