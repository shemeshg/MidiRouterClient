#include "UserConfigParseJson.h"
    void UserConfigParseJson::setChanges(UserDataConfig *userDataConfig, QJsonObject &jsonDoc) 
    {

        updateVirtualInPorts(userDataConfig,jsonDoc["virtualInPorts"]);

        if (jsonDoc["_activePresetID"].isDouble()) {
            userDataConfig->setActivePresetID(jsonDoc["_activePresetID"].toInt());
        }


        userDataConfig->setConnectedInPorts(stringListFromJsonAry(jsonDoc["connectedInPorts"]));
        userDataConfig->setConnectedOutPorts(stringListFromJsonAry(jsonDoc["connectedOutPorts"]));

        updateDropdownlists(userDataConfig, jsonDoc["dropdownlists"]);

        updateMidiRoutePresets(userDataConfig, jsonDoc["midiRoutePresets"]);
    }

    void UserConfigParseJson::updateVirtualInPorts(UserDataConfig *userDataConfig, const QJsonValue &virtualInPorts) 
    {
        if (virtualInPorts.isArray()){
            auto array = virtualInPorts.toArray();
            userDataConfig->clearVirtualPorts();
            for (const QJsonValue &value : array) {
                userDataConfig->addVirtualPort(value.toString());
            }

        }
    }

    void UserConfigParseJson::updateDropdownlists(UserDataConfig *userDataConfig, const QJsonValue &dropdownlists) 
    {
        userDataConfig->clearDropdownlists();
        if (dropdownlists.isArray()) {
            auto array = dropdownlists.toArray();
            for (const QJsonValue &value : array) {
                userDataConfig->addDropdownList(value["name"].toString(),value["data"].toString());
            }
        }
    }

    void UserConfigParseJson::updateMidiRoutePresets(UserDataConfig *userDataConfig, const QJsonValue &midiRoutePresets) 
    {
        userDataConfig->clearMidiRoutePresets();
        if (midiRoutePresets.isArray()){
            auto array = midiRoutePresets.toArray();
            for (const QJsonValue &value : array) {
                MidiRoutePreset *preset = createMidiRoutePreset(userDataConfig,value);
                auto easyConfig = value["easyConfig"];
                auto inputZonesAndRoutes = easyConfig["inputZonesAndRoutes"];
                if (easyConfig.isObject() && inputZonesAndRoutes.isObject()) {
                    updateEasyConfig(preset, inputZonesAndRoutes.toObject());
                }
                userDataConfig->addMidiRoutePresets(preset);
            }

        }
        if (userDataConfig->midiRoutePresets().size() == 0) {
            userDataConfig->addPreset();
            userDataConfig->setActivePreset(0);
        }
    }

    MidiRoutePreset* UserConfigParseJson::createMidiRoutePreset(UserDataConfig *userDataConfig, const QJsonValue &value) 
    {
        auto preset = new MidiRoutePreset(userDataConfig->computerUuid());
        preset->setName(value["name"].toString());
        preset->setIsSendAllUserControls(value["isSendAllUserControls"].toBool());
        preset->setUuid(value["uuid"].toString());

        updateMidiControl(preset->midiControlOn(), value["midiControlOn"], PresetMidiControl::PresetMidiType::PRESET_ON);
        updateMidiControl(preset->midiControlOff(), value["midiControlOff"], PresetMidiControl::PresetMidiType::PRESET_OFF);

        auto userControls = value["userControls"];
        if (userControls.isArray()) {
            for (const auto &userControlValue : userControls.toArray()) {
                auto userControl = createUserControl(userControlValue);
                preset->addUserControls(userControl);
            }
        }

        auto midiRouteInputs = value["midiRouteInputs"];
        if (midiRouteInputs.isObject()){
            updateMidiRouteInputs(preset, midiRouteInputs.toObject());
        }

        return preset;
    }

    void UserConfigParseJson::updateMidiControl(PresetMidiControl *control, const QJsonValue &value, PresetMidiControl::PresetMidiType type) 
    {
        control->setChannel(value["channel"].toInt());
        control->setData1(value["data1"].toInt());
        control->setData2(value["data2"].toInt());
        control->setEventTypeId(value["eventTypeId"].toInt());
        control->setPresetMidiType(type);
        control->setPortName(value["portName"].toString());
        control->setPresetUuid(value["presetUuid"].toString());
    }

    UserControl* UserConfigParseJson::createUserControl(const QJsonValue &userControlValue) 
    {
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

    void UserConfigParseJson::updateMidiRouteInputs(MidiRoutePreset *preset, const QJsonObject &midiRouteInputs) 
    {
        preset->clearMidiRouteInputs();
        for (auto it = midiRouteInputs.begin(); it != midiRouteInputs.end(); ++it) {
            MidiRouteInput *midiRouteInputEntry = createMidiRouteInputEntry( it.value().toObject());
            preset->addMidiRouteInputs(midiRouteInputEntry);
        }
    }

    MidiRouteInput* UserConfigParseJson::createMidiRouteInputEntry(const QJsonObject &value) 
    {
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

        auto propegateInputs = midiRouteClock["propegateInputs"];
        if (propegateInputs.isArray()) {
            QStringList list;
            for (const auto &propegateVal : propegateInputs.toArray()) {
                list.push_back(propegateVal.toObject()["midiInputName"].toString());
            }
            midiRouteInputEntry->setMidiRouteClockPropegateInputs(list);
        }

        auto cc14bitAry = value["cc14bitAry"];
        if (cc14bitAry.isArray()) {
            midiRouteInputEntry->clearMidiRouteInputCc14bit();
            for (const auto &cc14bit : cc14bitAry.toArray()) {
                auto midiRouteInputCc14bit = new MidiRouteInputCc14bit();
                const auto cc14bitObj = cc14bit.toObject();
                midiRouteInputCc14bit->setChannel(cc14bitObj["channel"].toInt());
                midiRouteInputCc14bit->setCc(cc14bitObj["cc"].toInt());
                midiRouteInputEntry->addMidiRouteInputCc14bit(midiRouteInputCc14bit);
            }
        }


        auto midiRouterChains = value["midiRouterChains"];
        if (midiRouterChains.isArray()) {
            midiRouteInputEntry->clearMidiRouterChains();
            //now all midi Chains and Filters
            for (const auto &fval : midiRouterChains.toArray()) {
                auto midiRouterChain = new MidiRouterChain();
                auto val = fval.toObject();
                midiRouterChain->setName(val["name"].toString());
                midiRouterChain->setIsEasyConfig(val["isEasyConfig"].isBool());


                //now for filters
                updateMidiRoutersFilters(val["midiRoutersFilters"],midiRouterChain);


                midiRouteInputEntry->addMidiRouterChains(midiRouterChain);
            }

        }
        return midiRouteInputEntry;
    }

    void UserConfigParseJson::updateMidiRoutersFilters(const QJsonValueRef &midiRoutersFilters, MidiRouterChain *midiRouterChain) 
    {
        if (midiRoutersFilters.isArray()) {
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

    void UserConfigParseJson::updateEasyConfig(MidiRoutePreset *preset, const QJsonObject &easyConfig) 
    {
        preset->clearEasyConfig();
        for (auto it = easyConfig.begin(); it != easyConfig.end(); ++it) {
            EasyConfig *easyConfigEntry = createEasyConfigEntry(it.key(), it.value().toObject());
            preset->addEasyConfig(easyConfigEntry);
        }
    }

    EasyConfig* UserConfigParseJson::createEasyConfigEntry(const QString &key, const QJsonObject &value) 
    {
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
                EasyConfigRoute *easyConfigRoute = createEasyConfigRoute(routeValue.toObject());
                easyConfigEntry->addEasyConfigRoutes(easyConfigRoute);
            }
        }



        return easyConfigEntry;
    }

    QList<int> UserConfigParseJson::extractKeyboardSplits(const QJsonArray &array) 
    {
        QList<int> keyboardSplits;
        for (const QJsonValue &value : array) {
            keyboardSplits.push_back(value["splitPosition"].toInt());
        }
        return keyboardSplits;
    }

    QStringList UserConfigParseJson::convertToQStringList(const QJsonArray &array) 
    {
        QStringList stringList;
        for (const QJsonValue &value : array) {
            stringList.append(value.toString());
        }
        return stringList;
    }

    EasyConfigRoute* UserConfigParseJson::createEasyConfigRoute(const QJsonObject &value) 
    {
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

    QStringList UserConfigParseJson::stringListFromJsonAry(const QJsonValue &j) 
    {
        QStringList s;
        if (j.isArray()){
            auto array = j.toArray();
            for (const QJsonValue &value : array) {
                s.append(value.toString());
            }
        }
        return s;
    }
