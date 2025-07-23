//-define-file body GenHpp/UserConfigParseJson.cpp
//-define-file header GenHpp/UserConfigParseJson.h
//-only-file header //-
#pragma once
#include <QtCore/qjsonarray.h>
#include <QtCore/qjsondocument.h>
//-only-file body //-
//- #include "UserConfigParseJson.h"

//- {include-header}
#include "MidiClientUtil.hpp" //- #include "MidiClientUtil.h"
//- {include-header}
#include "UserDataConfig.hpp" //- #include "UserDataConfig.h"
//-only-file header


//-var {PRE} "UserConfigParseJson::"
class UserConfigParseJson {
public:
    UserConfigParseJson() {}

    //- {fn}
    void setChanges(UserDataConfig *userDataConfigItf, QJsonObject &jsonDoc)
    //-only-file body
    {
        QStringList connIn = convertJsonArrayToQList<QString>(jsonDoc["connectedInPorts"]);
        connIn.sort();
        userDataConfigItf->setConnectedInPorts(connIn);
        QStringList connOut = convertJsonArrayToQList<QString>(jsonDoc["connectedOutPorts"]);
        connOut.sort();
        userDataConfigItf->setConnectedOutPorts(connOut);

        bool isServerInitialConfig = !jsonDoc["uniqueId"].isString() && !jsonDoc["uniqueId"].isDouble();
        if (isServerInitialConfig) {
            return;
        }

        if (!jsonDoc["uniqueId"].isDouble() && userDataConfigItf->uniqueId() ==
            getJson<QString>(jsonDoc["uniqueId"])) {
            // Same session created the config, return;";
            return;
        }

        updateVirtualInPorts(userDataConfigItf,
                             convertJsonArrayToQList<QString>(jsonDoc["virtualInPorts"]));

        updateDropdownlists(userDataConfigItf, jsonDoc["dropdownlists"]);

        recreateSettings<UserDataConfig, MidiRoutePreset>(
            userDataConfigItf, jsonDoc, "midiRoutePresets");

        userDataConfigItf->setActivePreset(
            getJson<double>(jsonDoc["_activePresetID"]), false);
    }

    //-only-file header
private:
    //- {fn}
    void updateVirtualInPorts(UserDataConfig *userDataConfig,
                              const QStringList &virtualInPorts)
    //-only-file body
    {
        userDataConfig->clearVirtualPorts();
        for (const auto &value : virtualInPorts) {
            userDataConfig->addVirtualPort(value);
        }
    }

    //- {fn}
    void updateDropdownlists(UserDataConfig *userDataConfig,
                             const QJsonValueRef &dropdownlists)
    //-only-file body
    {
        userDataConfig->clearList<Dropdownlist *>();

        auto array = getJson<QJsonArray>(dropdownlists);
        for (const auto &value : array) {
            auto obj = getJson<QJsonObject>(value);
            userDataConfig->addDropdownList(getJson<QString>(obj["name"]),
                                            getJson<QString>(obj["data"]),
                                            getJson<QString>(obj["uuid"]));
        }
    }

    //- {fn}
    void purgeDeletedCreateMissing(
        const std::function<QString(int)> &getUuid,
        const std::function<void(QString, QJsonObject)> &createNewObject,
        const int qlistObjSize, const std::function<void(int)> &qlistRemoveAt,
        QJsonArray &midiRoutePresetsArray)
    //-only-file body
    {
        QStringList presetUuidInJson;
        QMap<QString, QJsonObject> presetUuidInJsonMap;

        for (const auto &value : midiRoutePresetsArray) {
            auto valueObj = getJson<QJsonObject>(value);
            QString uuid = getJson<QString>(valueObj["uuid"]);
            presetUuidInJson.push_back(uuid);
            presetUuidInJsonMap[uuid] = valueObj;
        }

        QStringList uuidInPresets;
        for (auto it = qlistObjSize - 1; it >= 0; --it) {
            QString uuid = getUuid(it);
            bool containsUuid = presetUuidInJson.contains(uuid);
            if (containsUuid) {
                uuidInPresets.append(uuid);
            } else {
                qlistRemoveAt(it);
            }
        }

        for (const auto &j : presetUuidInJson) {
            if (!uuidInPresets.contains(j)) {
                createNewObject(j, presetUuidInJsonMap[j]);
            }
        }
    }

    //-only-file header
    template <typename T>
    T *getObjByUuid(const QList<T *> &presets, const QString &uuid) {
        for (auto const &preset : presets) {
            if (preset->uuid() == uuid) {
                return preset;
            }
        }
        return nullptr; // Return nullptr if no match is found
    }

    template <typename T, typename S>
    void purgeDeletedCreateMissingT(S *userDataConfig, QJsonArray &jsonAry) {
        purgeDeletedCreateMissing(
            [&userDataConfig](int idx) {
                return userDataConfig->template listItems<T *>().at(idx)->uuid();
            },
            [&userDataConfig](QString uuid, QJsonObject) {
                auto preset = userDataConfig->template addNewListItem<T *>();
                preset->setUuid(uuid);
            },
            userDataConfig->template listItems<T *>().size(),
            [&userDataConfig](int idx) {
                userDataConfig->template delListItem<T *>(idx);
            },
            jsonAry);
    }

    template <typename Parent, typename ChildListType>
    void recreateSettings(Parent *parent, QJsonObject &midirouteInputJsonObj,
                          QString arrayListKey) {        
        auto midiRouterChainsArray =
            getJson<QJsonArray>(midirouteInputJsonObj[arrayListKey]);
        purgeDeletedCreateMissingT<ChildListType>(parent, midiRouterChainsArray);

        for (const auto &value : midiRouterChainsArray) {
            auto midiRouterChainsJsonObj = getJson<QJsonObject>(value);
            QString uuid = getJson<QString>(midiRouterChainsJsonObj["uuid"]);

            auto midiRouterChain =
                getObjByUuid(parent->template listItems<ChildListType *>(), uuid);
            if (midiRouterChain == nullptr) {
                throw std::runtime_error("Unexpected JSON format");
            }
            setSettings(midiRouterChain, midiRouterChainsJsonObj);
        }
    }

    template <typename ObjType> class FieldSetter {
    public:
        FieldSetter(ObjType *obj, QJsonObject &jsonObj)
            : obj_(obj), jsonObj_(jsonObj) {}

        template <typename FuncReturnType, typename Func>
        void setField(Func func, const QString &tagName) {
            std::function<void(FuncReturnType)> boundFunction =
                std::bind(func, obj_, std::placeholders::_1);
            boundFunction(getJson<FuncReturnType>(jsonObj_[tagName]));
        }

    private:
        ObjType *obj_;
        QJsonObject &jsonObj_;
    };

    template <typename FuncReturnType, typename Func, typename Object>
    void setField(Func func, QString tagName, Object *obj, QJsonObject &jsonObj) {
        // Call the passed function with an example argument
        std::function<void(FuncReturnType)> boundFunction =
            std::bind(func, obj, std::placeholders::_1);
        boundFunction(getJson<FuncReturnType>(jsonObj[tagName]));
    }

    //- {fn}
    void updateMidirouteInputs(MidiRoutePreset *preset,
                               QJsonObject &presetJsonObj)
    //-only-file body
    {

        recreateSettings<MidiRoutePreset, MidiRouteInput>(preset, presetJsonObj,
                                                          "midiRouteInputs");
    }

    //- {fn}
    void setSettings(MidiRoutePreset *preset, QJsonObject &valueObj)
    //-only-file body
    {
        preset->setIsEnabled(getJson<bool>(valueObj["isEnabled"]));
        preset->setName(getJson<QString>(valueObj["name"]));

        updateMidiControl(preset->midiControlOn(), valueObj["midiControlOn"],
                          PresetMidiControl::PresetMidiType::PRESET_ON);
        updateMidiControl(preset->midiControlOff(), valueObj["midiControlOff"],
                          PresetMidiControl::PresetMidiType::PRESET_OFF);
        updateMidiControl(preset->midiControlToggle(), valueObj["midiControlToggle"],
                          PresetMidiControl::PresetMidiType::PRESET_TOGGLE);
        updateMidiControl(preset->midiControlSelect(), valueObj["midiControlSelect"],
                          PresetMidiControl::PresetMidiType::PRESET_SELECT);

        updateUserControls(preset, valueObj);
        updateMidirouteInputs(preset, valueObj);
    }

    //- {fn}
    void setSettings(EasyConfigRoute *easyConfigRoute, QJsonObject &easyConfigRouteJsonObj)
    //-only-file body
    {
        FieldSetter fst(easyConfigRoute, easyConfigRouteJsonObj);
        fst.setField<int>(&EasyConfigRoute::setFromCcOrNrpnEnd, "fromCcOrNrpnEnd");
        fst.setField<int>(&EasyConfigRoute::setFromCcOrNrpnStart, "fromCcOrNrpnStart");
        fst.setField<int>(&EasyConfigRoute::setFromChannel, "fromChannel");
        fst.setField<int>(&EasyConfigRoute::setFromData1, "fromData1");
        fst.setField<int>(&EasyConfigRoute::setFromSelectedMidiEventTypeId, "fromSelectedMidiEventTypeId");
        fst.setField<int>(&EasyConfigRoute::setSplitRangeId, "splitRangeId");
        fst.setField<int>(&EasyConfigRoute::setToCcOrNrpnEnd, "toCcOrNrpnEnd");
        fst.setField<int>(&EasyConfigRoute::setToCcOrNrpnStart, "toCcOrNrpnStart");
        fst.setField<int>(&EasyConfigRoute::setToChannel, "toChannel");
        fst.setField<int>(&EasyConfigRoute::setToData1, "toData1");
        fst.setField<QString>(&EasyConfigRoute::setToDestinationName, "toDestinationName");
        fst.setField<int>(&EasyConfigRoute::setToSelectedMidiEventTypeId, "toSelectedMidiEventTypeId");
        fst.setField<int>(&EasyConfigRoute::setTranspose, "transpose");
    }

    //- {fn}
    void setSettings(UserControl *userControl, QJsonObject &userControlJsonObj)
    //-only-file body
    {

        userControl->setEventType(static_cast<UserControl::EventType>(
            getJson<double>(userControlJsonObj["eventType"])));

        FieldSetter fst(userControl, userControlJsonObj);
        fst.setField<QString>(&UserControl::setDescription, "description");
        fst.setField<double>(&UserControl::setInputVal, "inputVal");
        fst.setField<double>(&UserControl::setMinVal, "minVal");
        fst.setField<double>(&UserControl::setMaxVal, "maxVal");
        fst.setField<bool>(&UserControl::setIs64Mode, "is64Mode");
        fst.setField<double>(&UserControl::setChannelId, "channelId");
        fst.setField<double>(&UserControl::setCcId, "ccId");
        fst.setField<double>(&UserControl::setNrpnControl, "nrpnControl");
        fst.setField<QString>(&UserControl::setOutputPortnName, "outputPortnName");
        fst.setField<bool>(&UserControl::setIsShowDropdown, "isShowDropdown");
        fst.setField<bool>(&UserControl::setIsSendOnPresetChange, "isSendOnPresetChange");
        fst.setField<QString>(&::UserControl::setDropdownListUuid, "dropdownListUuid");
    }

    //- {fn}
    void setFilterSettings(MidiRouterChain *midiRouterChain,
                           QJsonObject &midiRouterChainsJsonObj)
    //-only-file body
    {        
        auto midiRouterFiltersArray =
            getJson<QJsonArray>(midiRouterChainsJsonObj["midiRoutersFilters"]);

        purgeDeletedCreateMissing(
            [&midiRouterChain](int idx) {
                QString s="";
                auto itm = midiRouterChain->midiRoutersFilters().at(idx);

                if (itm.canConvert<FilterMidiDestination*>()) {
                    s = itm.value<FilterMidiDestination*>()->uuid();
                } else if (itm.canConvert<FilterToConsole*>()) {
                    s = itm.value<FilterToConsole*>()->uuid();
                } else if (itm.canConvert<FilterNetworkDestination*>()) {
                    s = itm.value<FilterNetworkDestination*>()->uuid();
                } else if (itm.canConvert<FilterSchedule*>()) {
                    s = itm.value<FilterSchedule*>()->uuid();
                } else if (itm.canConvert<FilterAndTransform*>()) {
                    s = itm.value<FilterAndTransform*>()->uuid();
                } else {
                    throw std::runtime_error("Unexpected JSON format");
                }


                return s;
            },
            [&midiRouterChain](QString uuid, QJsonObject filterJsonObj) {
                int filterType = getJson<double>(filterJsonObj["filterType"]);

                if (filterType == static_cast<int>(MidiRoutersFilter::FilterType::TO_MIDI_DESTINATION)){
                    auto item = midiRouterChain->addFilterMidiDestination(
                        getJson<QString>(filterJsonObj["midiInputName"])
                        );
                    item->setUuid(uuid);
                } else if (filterType == static_cast<int>(MidiRoutersFilter::FilterType::TO_CONSOLE)){
                    auto item = midiRouterChain->addFilterToConsole(
                        static_cast<FilterToConsole::LogTo>(getJson<double>(filterJsonObj["logTo"])),
                        getJson<QString>(filterJsonObj["userdata"]));
                    item->setUuid(uuid);
                } else if (filterType == static_cast<int>(MidiRoutersFilter::FilterType::SCHEDULE_TO)){
                    auto item = midiRouterChain->addFilterFilterSchedule(
                        static_cast<FilterSchedule::DefferedType>(
                            getJson<double>(filterJsonObj["defferedType"])),
                        getJson<double>(filterJsonObj["defferedTo"]));
                    item->setUuid(uuid);
                } else if (filterType == static_cast<int>(MidiRoutersFilter::FilterType::TO_NETWORK)){
                    auto item = midiRouterChain->addFilterNetworkDestination(
                        getJson<QString>(filterJsonObj["serverName"]),
                        getJson<double>(filterJsonObj["serverPort"]),
                        getJson<QString>(filterJsonObj["midiInputName"]));
                    item->setUuid(uuid);
                } else if (filterType == static_cast<int>(MidiRoutersFilter::FilterType::FILTER_AND_TRANSFORM)){
                    auto item = midiRouterChain->addFilterAndTransform(
                        getJson<QString>(filterJsonObj["name"]),
                        static_cast<FilterAndTransform::ConditionAction>(
                            getJson<double>(filterJsonObj["conditionAction"])),
                        getJson<QString>(filterJsonObj["filterChannel"]),
                        getJson<QString>(filterJsonObj["filterEvents"]),
                        getJson<QString>(filterJsonObj["filterData1"]),
                        getJson<QString>(filterJsonObj["filterData2"]));
                    item->setUuid(uuid);
                }
                else {
                    throw std::runtime_error("Unexpected JSON format");
                }

            },
            midiRouterChain->midiRoutersFilters().size(),
            [&midiRouterChain](int idx) {
                midiRouterChain->delMidiRoutersFilter(idx);
            },
            midiRouterFiltersArray);


    }

    //- {fn}
    void setSettings(MidiRouterChain *midiRouterChain,
                     QJsonObject &midiRouterChainsJsonObj)
    //-only-file body
    {
        FieldSetter fst(midiRouterChain, midiRouterChainsJsonObj);
        fst.setField<QString>(&MidiRouterChain::setName, "name");
        fst.setField<bool>(&MidiRouterChain::setIsEasyConfig, "isEasyConfig");


        setFilterSettings(midiRouterChain, midiRouterChainsJsonObj);

    }

    //- {fn}
    void updateUserControls(MidiRoutePreset *preset, QJsonObject &presetJsonObj)
    //-only-file body
    {
        recreateSettings<MidiRoutePreset, UserControl>(preset, presetJsonObj,
                                                       "userControls");
    }



    //- {fn}
    void updateMidiControl(PresetMidiControl *control, const QJsonValueRef &value,
                           PresetMidiControl::PresetMidiType type)
    //-only-file body
    {
        auto valueObj = getJson<QJsonObject>(value);
        FieldSetter fst(control, valueObj);
        fst.setField<double>(&PresetMidiControl::setChannel, "channel");
        fst.setField<double>(&PresetMidiControl::setData1, "data1");
        fst.setField<double>(&PresetMidiControl::setData2, "data2");
        fst.setField<double>(&PresetMidiControl::setEventTypeId, "eventTypeId");

        control->setPresetMidiType(type);

        fst.setField<QString>(&PresetMidiControl::setPortName, "portName");
    }



    //- {fn}
    void setSettings(MidiRouteInput *midiRouteInput,
                     QJsonObject &midirouteInputJsonObj)
    //-only-file body
    {
        FieldSetter fst(midiRouteInput, midirouteInputJsonObj);
        fst.setField<QString>(&MidiRouteInput::setMidiInputName, "midiInputName");

        auto ignoreTypes =
            getJson<QJsonObject>(midirouteInputJsonObj["ignoreTypes"]);
        FieldSetter fstIgnoreType(midiRouteInput, ignoreTypes);
        fstIgnoreType.setField<bool>(&MidiRouteInput::setIgnoreTypesMidiSysex,
                                     "midiSysex");
        fstIgnoreType.setField<bool>(&MidiRouteInput::setIgnoreTypesMidiTime,
                                     "midiTime");
        fstIgnoreType.setField<bool>(&MidiRouteInput::setIgnoreTypesMidiSense,
                                     "midiSense");

        auto midiRouteClock =
            getJson<QJsonObject>(midirouteInputJsonObj["midiRouteClock"]);
        FieldSetter fstMidiRouteClock(midiRouteInput, midiRouteClock);
        fstMidiRouteClock.setField<double>(
            &MidiRouteInput::setMidiRouteClockTimeSig, "timeSig");
        fstMidiRouteClock.setField<double>(
            &MidiRouteInput::setMidiRouteClockTimeSigDivBy, "timeSigDivBy");
        fstMidiRouteClock.setField<double>(
            &MidiRouteInput::setMidiRouteClockFromSppPos, "fromSppPos");

        auto propegateInputs =
            getJson<QJsonArray>(midiRouteClock["propegateInputs"]);
        QStringList propegateInputsList;
        for (const auto &propegateVal : propegateInputs) {
            propegateInputsList.push_back(
                propegateVal.toObject()["midiInputName"].toString());
        }
        midiRouteInput->setMidiRouteClockPropegateInputs(propegateInputsList);

        auto cc14bitAry = getJson<QJsonArray>(midirouteInputJsonObj["cc14bitAry"]);
        midiRouteInput->clearList<MidiRouteInputCc14bit *>();
        for (const auto &cc14bit : cc14bitAry) {
             MidiRouteInputCc14bit *midiRouteInputCc14bit = midiRouteInput->addNewListItem<MidiRouteInputCc14bit *>();
            auto cc14bitObj = getJson<QJsonObject>(cc14bit);
            FieldSetter fsCc14(midiRouteInputCc14bit, cc14bitObj);
            fsCc14.setField<double>(&MidiRouteInputCc14bit::setChannel, "channel");
            fsCc14.setField<double>(&MidiRouteInputCc14bit::setCc, "cc");
        }
        recreateSettings<MidiRouteInput, MidiRouterChain>(
            midiRouteInput, midirouteInputJsonObj, "midiRouterChains");

        auto easyConfigObj = getJson<QJsonObject>(midirouteInputJsonObj["easyConfig"]);
        midiRouteInput->easyConfig()->setKeyboardSplits(convertJsonArrayToQList<int>(easyConfigObj["keyboardSplits"]));
        midiRouteInput->easyConfig()->setZoneNames(convertJsonArrayToQList<QString>(easyConfigObj["zoneNames"]));

        recreateSettings<EasyConfig, EasyConfigRoute>(midiRouteInput->easyConfig(), easyConfigObj, "easyConfigRoutes");
    }


    //-only-file header
};
