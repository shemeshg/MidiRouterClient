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


void UserDataConfig::updateVirtualInPorts(const QJsonArray &array) {
    m_virtualInPorts.clear();
    for (const QJsonValue &value : array) {
        m_virtualInPorts.append(value.toString());
    }
    emit virtualInPortsChanged();
}

void UserDataConfig::updateDropdownlists(const QJsonArray &array) {
    for (const QJsonValue &value : array) {
        Dropdownlist *d = new Dropdownlist();
        d->setName(value["name"].toString());
        d->setData(value["data"].toString());
        m_dropdownlists.push_back(d);
    }
    emit dropdownlistsChanged();
}

void UserDataConfig::updateMidiRoutePresets(const QJsonArray &array) {
    for (const QJsonValue &value : array) {
        MidiRoutePreset *p = new MidiRoutePreset(m_computerUuid);
        p->setName(value["name"].toString());
        p->setIsSendAllUserControls(value["isSendAllUserControls"].isBool());
        p->setUuid(value["uuid"].toString());

        updateMidiControl(p->midiControlOn(), value["midiControlOn"], PresetMidiControl::PresetMidiType::PRESET_ON);
        updateMidiControl(p->midiControlOff(), value["midiControlOff"], PresetMidiControl::PresetMidiType::PRESET_OFF);

        if (value["easyConfig"].isObject() && value["easyConfig"]["inputZonesAndRoutes"].isObject()) {
            p->clearEasyConfig();
            auto a = value["easyConfig"]["inputZonesAndRoutes"].toObject();
            for (auto it = a.begin(); it != a.end(); ++it) {
                qDebug() << "key: " << it.key();
                qDebug() << it.value();
                EasyConfig *e=p->addEasyConfig(it.value().toString());


                //{"easyConfigRoutes":[],"keyboardSplits":[{"splitPosition":60}],"midiInputName":"0_Scarlett 2i4 USB","zoneNames":["I0S0","I0S1"]}
                if  (it.value().toObject()["keyboardSplits"].isArray()){
                    QList<int> kbdSplits={};
                    for (const QJsonValue &value : it.value().toObject()["keyboardSplits"].toArray()) {
                        kbdSplits.push_back(value["splitPosition"].toInt());
                    }
                    e->setKeyboardSplits(kbdSplits);
                    qDebug()<<"Our keyboard splits are "<<kbdSplits;
                }

            }
        }

        m_midiRoutePresets.push_back(p);
    }
    emit midiRoutePresetsChanged();
}

void UserDataConfig::updateMidiControl(PresetMidiControl *control, const QJsonValue &value, PresetMidiControl::PresetMidiType type) {
    control->setChannel(value["channel"].toInt());
    control->setData1(value["data1"].toInt());
    control->setData2(value["data2"].toInt());
    control->setEventTypeId(value["eventTypeId"].toInt());
    control->setPresetMidiType(type);
    control->setPortName(value["portName"].toString());
    control->setPresetUuid(value["presetUuid"].toString());
}


void UserDataConfig::setChanges(QJsonDocument &jsonDoc){
    qDebug()<<"Empllay remote configuration";
    //qDebug() << "json[" <<  jsonDoc.toJson().replace("\\n", "\n") << "]";

    if (jsonDoc["virtualInPorts"].isArray()) {
            updateVirtualInPorts(jsonDoc["virtualInPorts"].toArray());
    }
    //qDebug()<<"virtualInPorts are:" << m_virtualInPorts;

    if (jsonDoc["_activePresetID"].isDouble()) {
        setActivePresetID(jsonDoc["_activePresetID"].toInt());
    }


    clearDropdownlists();
    if (jsonDoc["dropdownlists"].isArray()) {
        updateDropdownlists(jsonDoc["dropdownlists"].toArray());
    }


    clearMidiRoutePreset();
    if (jsonDoc["midiRoutePresets"].isArray()) {
        updateMidiRoutePresets(jsonDoc["midiRoutePresets"].toArray());
    }

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
