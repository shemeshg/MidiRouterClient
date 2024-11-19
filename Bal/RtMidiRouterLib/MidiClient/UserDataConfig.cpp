#include "UserDataConfig.h"
#include <QSettings>
#include "FilterToConsle.h"
#include "MidiClientUtil.h"
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
}

void UserDataConfig::clearMidiRoutePreset()
{
    for (const MidiRoutePreset *item : m_midiRoutePresets) {
        delete item;
    }
    // Clear the outer list
    m_midiRoutePresets.clear();
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


MidiRouteInput* UserDataConfig::createMidiRouteInputEntry(const QJsonObject &value) {
    auto midiRouteInputEntry = new MidiRouteInput();
    midiRouteInputEntry->setMidiInputName(value["midiInputName"].toString());

    const auto ignoreTypes = value["ignoreTypes"].toObject();
    midiRouteInputEntry->setIgnoreTypesMidiSysex(ignoreTypes["midiSysex"].toBool());
    midiRouteInputEntry->setIgnoreTypesMidiTime(ignoreTypes["midiTime"].toBool());
    midiRouteInputEntry->setIgnoreTypesMidiSense(ignoreTypes["midiSense"].toBool());

    const auto midiRouteClock = value["midiRouteClock"].toObject();
    midiRouteInputEntry->setMidiRouteClockTimeSig(midiRouteClock["timeSig"].toInt());
    midiRouteInputEntry->setMidiRouteClockTimeSigDivBy(midiRouteClock["timeSigDivBy"].toInt());
    midiRouteInputEntry->setMidiRouteClockFromSppPos(midiRouteClock["fromSppPos"].toInt());

    if (midiRouteClock["propegateInputs"].isArray()) {
        QStringList list;
        for (const auto &propegateVal : midiRouteClock["propegateInputs"].toArray()) {
            list.push_back(propegateVal.toObject()["midiInputName"].toString());
        }
        midiRouteInputEntry->setMidiRouteClockPropegateInputs(list);
    }

    if (value["cc14bitAry"].isArray()) {
        midiRouteInputEntry->clearMidiRouteInputCc14bit();
        for (const auto &cc14bit : value["cc14bitAry"].toArray()) {
            auto midiRouteInputCc14bit = new MidiRouteInputCc14bit();
            const auto cc14bitObj = cc14bit.toObject();
            midiRouteInputCc14bit->setChannel(cc14bitObj["channel"].toInt());
            midiRouteInputCc14bit->setCc(cc14bitObj["cc"].toInt());
            midiRouteInputEntry->addMidiRouteInputCc14bit(midiRouteInputCc14bit);
        }
    }


    if (value["midiRouterChains"].isArray()) {
        midiRouteInputEntry->clearMidiRouterChains();
        //now all midi Chains and Filters
        for (const auto &fval : value["midiRouterChains"].toArray()) {
            auto midiRouterChain = new MidiRouterChain();
            auto val = fval.toObject();
            midiRouterChain->setName(val["name"].toString());
            midiRouterChain->setIsEasyConfig(val["isEasyConfig"].isBool());
            qDebug()<<"in chain"<<midiRouterChain->name();


            //now for filters
            updateMidiRoutersFilters(val["midiRoutersFilters"],midiRouterChain);


            midiRouteInputEntry->addMidiRouterChains(midiRouterChain);
        }

    }
    return midiRouteInputEntry;
}


void UserDataConfig::updateMidiRoutersFilters(const QJsonValueRef &midiRoutersFilters, MidiRouterChain *midiRouterChain){
    if (midiRoutersFilters.isArray()) {
        qDebug()<<"we are in folter "<<midiRoutersFilters;
        midiRouterChain->clearMidiRoutersFilters();
        for (const auto &filterVal : midiRoutersFilters.toArray()) {
            auto filter = filterVal.toObject();

            if (filter["filterType"].toInt() == static_cast<int>(MidiRoutersFilter::FilterType::TO_MIDI_DESTINATION)){                
                midiRouterChain->addFilterMidiDestination(filter["baseMidiRouteInput"].toObject()["midiInputName"].toString());
            } else if (filter["filterType"].toInt() == static_cast<int>(MidiRoutersFilter::FilterType::TO_CONSOLE)){
                midiRouterChain->addFilterToConsole(
                    static_cast<FilterToConsole::LogTo>(filter["logTo"].toInt()),
                    filter["userdata"].toString()
                    );
            } else if (filter["filterType"].toInt() == static_cast<int>(MidiRoutersFilter::FilterType::SCHEDULE_TO)){


                midiRouterChain->addFilterFilterSchedule(
                        static_cast<FilterSchedule::DefferedType>(filter["defferedType"].toInt()),
                        filter["defferedTo"].toInt()
                    );
            } else if (filter["filterType"].toInt() == static_cast<int>(MidiRoutersFilter::FilterType::TO_NETWORK)){
                midiRouterChain->addFilterNetworkDestination(filter["serverName"].toString(),
                                                             filter["serverPort"].toInt(),
                                                             filter["baseMidiRouteInput"].toObject()["midiInputName"].toString()
                                                             );
            } else if (filter["filterType"].toInt() == static_cast<int>(MidiRoutersFilter::FilterType::FILTER_AND_TRANSFORM)) {
                midiRouterChain->addFilterAndTransform(filter["name"].toString(),
                                                       static_cast<FilterAndTransform::ConditionAction>(filter["conditionAction"].toInt()),
                                                       filter["filterChannel"].toString(),
                                                       filter["filterEvents"].toString(),
                                                       filter["filterData1"].toString(),
                                                       filter["filterData2"].toString()
                                                       );
            }

        }
    }
}

void UserDataConfig::updateMidiRouteInputs(MidiRoutePreset *preset, const QJsonObject &midiRouteInputs) {
    preset->clearMidiRouteInputs();
    for (auto it = midiRouteInputs.begin(); it != midiRouteInputs.end(); ++it) {
        qDebug() << "midiRouteInputEntry key: " << it.key();
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
            qDebug() << "Lets parse easyConfigRoute ";
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

void UserDataConfig::setChanges(QJsonDocument &jsonDoc){
    qDebug()<<"Empllay remote configuration";
    //qDebug() << "json[" <<  jsonDoc.toJson().replace("\\n", "\n") << "]";

    UserConfigParseJson userConfigParseJson;
    userConfigParseJson.setChanges(this, jsonDoc);

    //qDebug()<<"virtualInPorts are:" << m_virtualInPorts;

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
