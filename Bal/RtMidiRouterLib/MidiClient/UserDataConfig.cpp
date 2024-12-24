#include "UserDataConfig.h"
#include <QSettings>
#include "GenHpp/MidiClientUtil.h"
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





QJsonObject UserDataConfig::getJson(){
    UserConfigGenJson userConfigGenJson;
    return userConfigGenJson.getJson(this);
}



UserDataConfig::UserDataConfig(QObject *parent)
    : UserDataConfigPrivate{parent}
{
    
    loadComputerUuid();
    m_uniqueId = getUuId();

    clearDropdownlists();
    m_virtualInPorts = {};

    clearMidiRoutePresets();
    addPreset();
    setActivePreset(0);
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
