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

UserControl* UserDataConfig::createUserControl(const QJsonValue &userControlValue) {
    auto userControl = new UserControl();
    userControl->setEventType(static_cast<UserControl::EventType>(userControlValue["eventType"].toInt()));
    userControl->setDescription(userControlValue["description"].toString());
    userControl->setInputVal(userControlValue["inputVal"].toInt());
    userControl->setMinVal(userControlValue["minVal"].toInt());
    userControl->setMaxVal(userControlValue["maxVal"].toInt());
    userControl->setIs64Mode(userControlValue["is64Mode"].toBool());
    userControl->setIsEditMode(userControlValue["isEditMode"].toBool());
    userControl->setChannelId(userControlValue["channelId"].toInt());
    userControl->setCcId(userControlValue["ccId"].toInt());
    userControl->setNrpnControl(userControlValue["nrpnControl"].toInt());
    userControl->setOutputPortnName(userControlValue["outputPortnName"].toString());
    userControl->setIsShowDropdown(userControlValue["isShowDropdown"].toBool());
    userControl->setDropdownListId(userControlValue["dropdownListId"].toInt());
    return userControl;
}


MidiRouteInput* UserDataConfig::createMidiRouteInputEntry( const QJsonObject &value) {
    MidiRouteInput *midiRouteInputEEntry = new MidiRouteInput();
    midiRouteInputEEntry->setMidiInputName(value["midiInputName"].toString());
    auto ignoreTypes = value["ignoreTypes"];
    midiRouteInputEEntry->setIgnoreTypesMidiSysex(ignoreTypes["midiSysex"].toBool());
    midiRouteInputEEntry->setIgnoreTypesMidiTime(ignoreTypes["midiTime"].toBool());
    midiRouteInputEEntry->setIgnoreTypesMidiSense(ignoreTypes["midiSense"].toBool());
    auto midiRouteClock = value["midiRouteClock"];
    midiRouteInputEEntry->setMidiRouteClockTimeSig(midiRouteClock["timeSig"].toInt());
    midiRouteInputEEntry->setMidiRouteClockTimeSigDivBy(midiRouteClock["timeSigDivBy"].toInt());
    midiRouteInputEEntry->setMidiRouteClockFromSppPos(midiRouteClock["fromSppPos"].toInt());
    if (midiRouteClock["propegateInputs"].isArray()){
        QStringList list;
        for (const auto &propegateVal : midiRouteClock["propegateInputs"].toArray()) {            
            list.push_back(propegateVal.toObject()["midiInputName"].toString()) ;
        }
        midiRouteInputEEntry->setMidiRouteClockPropegateInputs(list);        
    }


    if(value["cc14bitAry"].isArray()){
        midiRouteInputEEntry->clearMidiRouteInputCc14bit();
        for (const auto &cc14bit : value["cc14bitAry"].toArray()) {
            MidiRouteInputCc14bit *midiRouteInputCc14bit = new MidiRouteInputCc14bit();
            midiRouteInputCc14bit->setChannel(cc14bit.toObject()["channel"].toInt());
            midiRouteInputCc14bit->setCc(cc14bit.toObject()["cc"].toInt());
            midiRouteInputEEntry->addMidiRouteInputCc14bit(midiRouteInputCc14bit);
        }
    }
    //midiRouteInputEEntry->setMidiRouteClockPropegateInputs(convertToQStringList(value["midiRouteClock"]["propegateInputs"].toArray()));
    //now for midiRouteInputs ***
    return midiRouteInputEEntry;
}

void UserDataConfig::updateMidiRouteInputs(MidiRoutePreset *preset, const QJsonObject &midiRouteInputs) {
    preset->clearMidiRouteInputs();
    for (auto it = midiRouteInputs.begin(); it != midiRouteInputs.end(); ++it) {
        qDebug() << "midiRouteInputEntry key: " << it.key();
        qDebug() << it.value();
        MidiRouteInput *midiRouteInputEntry = createMidiRouteInputEntry( it.value().toObject());
        preset->addMidiRouteInput(midiRouteInputEntry);
    }
}

MidiRoutePreset* UserDataConfig::createMidiRoutePreset(const QJsonValue &value) {
    auto preset = new MidiRoutePreset(m_computerUuid);
    preset->setName(value["name"].toString());
    preset->setIsSendAllUserControls(value["isSendAllUserControls"].toBool());
    preset->setUuid(value["uuid"].toString());

    updateMidiControl(preset->midiControlOn(), value["midiControlOn"], PresetMidiControl::PresetMidiType::PRESET_ON);
    updateMidiControl(preset->midiControlOff(), value["midiControlOff"], PresetMidiControl::PresetMidiType::PRESET_OFF);

    if (value["userControls"].isArray()) {
        for (const auto &userControlValue : value["userControls"].toArray()) {
            auto userControl = createUserControl(userControlValue);
            preset->addUserControl(userControl);
        }
    }



    if (value["midiRouteInputs"].isObject()){
        updateMidiRouteInputs(preset, value["midiRouteInputs"].toObject());
    }
    return preset;
}

void UserDataConfig::updateEasyConfig(MidiRoutePreset *preset, const QJsonObject &easyConfig) {
    preset->clearEasyConfig();
    for (auto it = easyConfig.begin(); it != easyConfig.end(); ++it) {
        qDebug() << "key: " << it.key();
        qDebug() << it.value();
        EasyConfig *easyConfigEntry = createEasyConfigEntry(it.key(), it.value().toObject());
        preset->addEasyConfig(easyConfigEntry);
    }
}

EasyConfig* UserDataConfig::createEasyConfigEntry(const QString &key, const QJsonObject &value) {
    EasyConfig *easyConfigEntry = new EasyConfig();
    easyConfigEntry->setMidiInputName(key);

    if (value["keyboardSplits"].isArray()) {
        QList<int> keyboardSplits = extractKeyboardSplits(value["keyboardSplits"].toArray());
        easyConfigEntry->setKeyboardSplits(keyboardSplits);
    }

    if (value["zoneNames"].isArray()) {
        QStringList zoneNames = convertToQStringList(value["zoneNames"].toArray());
        easyConfigEntry->setZoneNames(zoneNames);
    }

    if (value["easyConfigRoutes"].isArray()) {
        QJsonArray jsonArray = value["easyConfigRoutes"].toArray();
        for (const QJsonValue &routeValue : jsonArray) {
            qDebug() << "Lets parse easyConfigRoute " << routeValue;
            EasyConfigRoute *easyConfigRoute = createEasyConfigRoute(routeValue.toObject());
            easyConfigEntry->addEasyConfigRoute(easyConfigRoute);
        }
    }



    return easyConfigEntry;
}

EasyConfigRoute* UserDataConfig::createEasyConfigRoute(const QJsonObject &value) {
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

    return easyConfigRoute;
}

QList<int> UserDataConfig::extractKeyboardSplits(const QJsonArray &array) {
    QList<int> keyboardSplits;
    for (const QJsonValue &value : array) {
        keyboardSplits.push_back(value["splitPosition"].toInt());
    }
    return keyboardSplits;
}

QStringList UserDataConfig::convertToQStringList(const QJsonArray &array) {
    QStringList stringList;
    for (const QJsonValue &value : array) {
        stringList.append(value.toString());
    }
    return stringList;
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
