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
        MidiRoutePreset *preset = createMidiRoutePreset(value);
        if (value["easyConfig"].isObject() && value["easyConfig"]["inputZonesAndRoutes"].isObject()) {
            updateEasyConfig(preset, value["easyConfig"]["inputZonesAndRoutes"].toObject());
        }
        m_midiRoutePresets.push_back(preset);
    }
    emit midiRoutePresetsChanged();
}

MidiRoutePreset* UserDataConfig::createMidiRoutePreset(const QJsonValue &value) {
    MidiRoutePreset *preset = new MidiRoutePreset(m_computerUuid);
    preset->setName(value["name"].toString());
    preset->setIsSendAllUserControls(value["isSendAllUserControls"].isBool());
    preset->setUuid(value["uuid"].toString());

    updateMidiControl(preset->midiControlOn(), value["midiControlOn"], PresetMidiControl::PresetMidiType::PRESET_ON);
    updateMidiControl(preset->midiControlOff(), value["midiControlOff"], PresetMidiControl::PresetMidiType::PRESET_OFF);

    return preset;
}

void UserDataConfig::updateEasyConfig(MidiRoutePreset *preset, const QJsonObject &easyConfig) {
    preset->clearEasyConfig();
    for (auto it = easyConfig.begin(); it != easyConfig.end(); ++it) {
        qDebug() << "key: " << it.key();
        qDebug() << it.value();
        EasyConfig *easyConfigEntry = new EasyConfig();
        easyConfigEntry->setMidiInputName(it.key());

        if (it.value().toObject()["keyboardSplits"].isArray()) {
            QList<int> keyboardSplits = extractKeyboardSplits(it.value().toObject()["keyboardSplits"].toArray());
            easyConfigEntry->setKeyboardSplits(keyboardSplits);
        }

        if (it.value().toObject()["zoneNames"].isArray()) {
            QJsonArray jsonArray = it.value().toObject()["zoneNames"].toArray();
            QStringList stringList;
            for (const QJsonValue &value : jsonArray) {
                stringList.append(value.toString());
            }

            easyConfigEntry->setZoneNames(stringList);

        }

        if (it.value().toObject()["easyConfigRoutes"].isArray()) {
            QJsonArray jsonArray = it.value().toObject()["easyConfigRoutes"].toArray();
            for (const QJsonValue &value : jsonArray) {
                qDebug()<<"Lets parse easyConfigRoute "<< value;
                EasyConfigRoute *easyConfigRoute = new EasyConfigRoute();
                easyConfigRoute->setFromCcOrNrpnEnd(value["fromCcOrNrpnEnd"].toInt());
                easyConfigRoute->setFromCcOrNrpnStart(value["fromCcOrNrpnStart"].toInt());
                easyConfigRoute->setFromChannel(value["fromChannel"].toInt());
                easyConfigRoute->setFromData1(value["fromData1"].toInt());
                easyConfigRoute->setFromSelectedMidiEventTypeId(value["fromSelectedMidiEventTypeId"].toInt());
                easyConfigRoute->setSplitRangeId(value["splitRangeId"].toInt());
                easyConfigRoute->setToCcOrNrpnEnd(value["toCcOrNrpnEnd"].toInt());
                easyConfigRoute->setToCcOrNrpnStart(value["toCcOrNrpnStart"].toInt());
                easyConfigRoute->setToChannel(value["toChannel"].toInt());
                easyConfigRoute->setToData1(value["toData1"].toInt());
                easyConfigRoute->setToDestinationName(value["toDestinationName"].toString());
                easyConfigRoute->setToSelectedMidiEventTypeId(value["toSelectedMidiEventTypeId"].toInt());
                easyConfigRoute->setTranspose(value["transpose"].toInt());

                easyConfigEntry->addEasyConfigRoute(easyConfigRoute);

            }
        }
        preset->addEasyConfig(easyConfigEntry);
    }
}

QList<int> UserDataConfig::extractKeyboardSplits(const QJsonArray &array) {
    QList<int> keyboardSplits;
    for (const QJsonValue &value : array) {
        keyboardSplits.push_back(value["splitPosition"].toInt());
    }
    return keyboardSplits;
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
