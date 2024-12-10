#include "UserDataConfig.h"
#include <QSettings>
#include "MidiClientUtil.h"
#include "UserConfigGenJson.h"
#include "UserConfigParseJson.h"

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
    emit dropdownlistsChanged();
}

void UserDataConfig::clearMidiRoutePreset()
{
    for (const MidiRoutePreset *item : m_midiRoutePresets) {
        delete item;
    }
    // Clear the outer list
    m_midiRoutePresets.clear();
    emit midiRoutePresetsChanged();
}

QJsonObject UserDataConfig::getJson(){
    UserConfigGenJson userConfigGenJson;
    return userConfigGenJson.getJson(this);
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

void UserDataConfig::resetUserDataConfig(const QJsonValue &jsonData){

    //QJsonDocument jsonDoc = QJsonDocument::fromVariant(jsonData.toVariant());
    //if (jsonDoc["uniqueId"].isString() && jsonDoc["uniqueId"].toString() != computerUuid()){

        UserConfigParseJson userConfigParseJson;
    QJsonObject j;
        if (jsonData.isArray()){
             QJsonArray a = jsonData.toArray();
            j = a[0].toObject();
        } else {

            j = jsonData.toObject();
        }
        userConfigParseJson.setChanges(this, j);

}
