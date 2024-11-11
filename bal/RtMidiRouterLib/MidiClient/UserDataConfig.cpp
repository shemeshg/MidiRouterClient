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
            p->setIsSendAllUserControls(value["isSendAllUserControls"].isBool());
            p->setUuid(value["uuid"].toString());

            p->midiControlOn()->setChannel(value["midiControlOn"]["channel"].toInt());
            p->midiControlOn()->setData1(value["midiControlOn"]["data1"].toInt());
            p->midiControlOn()->setData2(value["midiControlOn"]["data2"].toInt());
            p->midiControlOn()->setEventTypeId(value["midiControlOn"]["eventTypeId"].toInt());
            p->midiControlOn()->setPresetMidiType(PresetMidiControl::PresetMidiType::PRESET_ON);
            p->midiControlOn()->setPortName(value["midiControlOn"]["portName"].toString());
            p->midiControlOn()->setPresetUuid(value["midiControlOn"]["presetUuid"].toString());

            p->midiControlOff()->setChannel(value["midiControlOff"]["channel"].toInt());
            p->midiControlOff()->setData1(value["midiControlOff"]["data1"].toInt());
            p->midiControlOff()->setData2(value["midiControlOff"]["data2"].toInt());
            p->midiControlOff()->setEventTypeId(value["midiControlOff"]["eventTypeId"].toInt());
            p->midiControlOff()->setPresetMidiType(PresetMidiControl::PresetMidiType::PRESET_OFF);
            p->midiControlOff()->setPortName(value["midiControlOff"]["portName"].toString());
            p->midiControlOff()->setPresetUuid(value["midiControlOff"]["presetUuid"].toString());


            if (value["easyConfig"].isObject() && value["easyConfig"]["inputZonesAndRoutes"].isObject()){
                p->clearEasyConfig();
                qDebug()<<"a "<<value["easyConfig"];
                auto a= value["easyConfig"]["inputZonesAndRoutes"].toObject();
                for (auto it = a.begin();
                     it != a.end(); ++it) {
                    qDebug()<<"key: "<<it.key(); //Already QString
                   //qDebug()<<it.value();
                }
            }


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
