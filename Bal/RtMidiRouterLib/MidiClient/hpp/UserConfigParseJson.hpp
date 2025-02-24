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

        userDataConfigItf->setConnectedInPorts(
            convertJsonArrayToQList<QString>(jsonDoc["connectedInPorts"]));
        userDataConfigItf->setConnectedOutPorts(
            convertJsonArrayToQList<QString>(jsonDoc["connectedOutPorts"]));

        bool isServerInitialConfig = !jsonDoc["uniqueId"].isString();
        if (isServerInitialConfig) {
            return;
        }

        if (userDataConfigItf->uniqueId() ==
            getJson<QString>(jsonDoc["uniqueId"])) {
            qDebug() << "Same session created the config, return;";
            // return;
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
                                            getJson<QString>(obj["data"]));
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
                T *preset = new T();
                userDataConfig->addListItem(preset);
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
        fst.setField<bool>(&UserControl::setIsEditMode, "isEditMode");
        fst.setField<double>(&UserControl::setChannelId, "channelId");
        fst.setField<double>(&UserControl::setCcId, "ccId");
        fst.setField<double>(&UserControl::setNrpnControl, "nrpnControl");
        fst.setField<QString>(&UserControl::setOutputPortnName, "outputPortnName");
        fst.setField<bool>(&UserControl::setIsShowDropdown, "isShowDropdown");
        fst.setField<double>(&UserControl::setDropdownListId, "dropdownListId");
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
                auto itm = midiRouterChain->midiRoutersFilters().at(idx);
                MidiRoutersFilter* filterPtr = nullptr;
                if (itm.canConvert<MidiRoutersFilter*>()) {
                    filterPtr  = qvariant_cast<MidiRoutersFilter*>(itm);
                }
                if (filterPtr == nullptr){
                    throw std::runtime_error("Unexpected JSON format");
                }


                return filterPtr->uuid();
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
            auto midiRouteInputCc14bit = new MidiRouteInputCc14bit();
            auto cc14bitObj = getJson<QJsonObject>(cc14bit);
            FieldSetter fsCc14(midiRouteInputCc14bit, cc14bitObj);
            fsCc14.setField<double>(&MidiRouteInputCc14bit::setChannel, "channel");
            fsCc14.setField<double>(&MidiRouteInputCc14bit::setCc, "cc");

            midiRouteInput->addListItem(midiRouteInputCc14bit);
        }
        recreateSettings<MidiRouteInput, MidiRouterChain>(
            midiRouteInput, midirouteInputJsonObj, "midiRouterChains");

        auto easyConfigObj = getJson<QJsonObject>(midirouteInputJsonObj["easyConfig"]);
        midiRouteInput->easyConfig()->setKeyboardSplits(convertJsonArrayToQList<int>(easyConfigObj["keyboardSplits"]));
        midiRouteInput->easyConfig()->setZoneNames(convertJsonArrayToQList<QString>(easyConfigObj["zoneNames"]));

        recreateSettings<EasyConfig, EasyConfigRoute>(midiRouteInput->easyConfig(), easyConfigObj, "easyConfigRoutes");
    }

    //- {fn}
    MidiRouteInput *createMidiRouteInputEntryDELTE(const QJsonObject &value)
    //-only-file body
    {
        auto midiRouteInputEntry = new MidiRouteInput();
        midiRouteInputEntry->setMidiInputName(value["midiInputName"].toString());

        const auto ignoreTypes = value["ignoreTypes"].toObject();
        midiRouteInputEntry->setIgnoreTypesMidiSysex(
            ignoreTypes["midiSysex"].toBool());
        midiRouteInputEntry->setIgnoreTypesMidiTime(
            ignoreTypes["midiTime"].toBool());
        midiRouteInputEntry->setIgnoreTypesMidiSense(
            ignoreTypes["midiSense"].toBool());

        const auto midiRouteClock = value["midiRouteClock"].toObject();
        midiRouteInputEntry->setMidiRouteClockTimeSig(
            midiRouteClock["timeSig"].toInt());
        midiRouteInputEntry->setMidiRouteClockTimeSigDivBy(
            midiRouteClock["timeSigDivBy"].toInt());
        midiRouteInputEntry->setMidiRouteClockFromSppPos(
            midiRouteClock["fromSppPos"].toInt());

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
            midiRouteInputEntry->clearList<MidiRouteInputCc14bit *>();
            for (const auto &cc14bit : cc14bitAry.toArray()) {
                auto midiRouteInputCc14bit = new MidiRouteInputCc14bit();
                const auto cc14bitObj = cc14bit.toObject();
                midiRouteInputCc14bit->setChannel(cc14bitObj["channel"].toInt());
                midiRouteInputCc14bit->setCc(cc14bitObj["cc"].toInt());
                midiRouteInputEntry->addListItem(midiRouteInputCc14bit);
            }
        }

        auto midiRouterChains = value["midiRouterChains"];
        if (midiRouterChains.isArray()) {
            midiRouteInputEntry->clearMidiRouterChains();
            // now all midi Chains and Filters
            for (const auto &fval : midiRouterChains.toArray()) {
                auto midiRouterChain = new MidiRouterChain();
                auto val = fval.toObject();
                midiRouterChain->setName(val["name"].toString());
                midiRouterChain->setIsEasyConfig(val["isEasyConfig"].isBool());

                // now for filters
                updateMidiRoutersFilters(val["midiRoutersFilters"], midiRouterChain);

                midiRouteInputEntry->addListItem(midiRouterChain);
            }
        }
        return midiRouteInputEntry;
    }

    //- {fn}
    void updateMidiRoutersFilters(const QJsonValueRef &midiRoutersFilters,
                                  MidiRouterChain *midiRouterChain)
    //-only-file body
    {
        if (midiRoutersFilters.isArray()) {
            midiRouterChain->clearMidiRoutersFilters();
            for (const auto &filterVal : midiRoutersFilters.toArray()) {
                auto filter = filterVal.toObject();

                if (filter["filterType"].toInt() ==
                    static_cast<int>(
                        MidiRoutersFilter::FilterType::TO_MIDI_DESTINATION)) {
                    midiRouterChain->addFilterMidiDestination(
                        filter["baseMidiRouteInput"]
                            .toObject()["midiInputName"]
                            .toString());
                } else if (filter["filterType"].toInt() ==
                           static_cast<int>(
                               MidiRoutersFilter::FilterType::TO_CONSOLE)) {
                    midiRouterChain->addFilterToConsole(
                        static_cast<FilterToConsole::LogTo>(filter["logTo"].toInt()),
                        filter["userdata"].toString());
                } else if (filter["filterType"].toInt() ==
                           static_cast<int>(
                               MidiRoutersFilter::FilterType::SCHEDULE_TO)) {

                    midiRouterChain->addFilterFilterSchedule(
                        static_cast<FilterSchedule::DefferedType>(
                            filter["defferedType"].toInt()),
                        filter["defferedTo"].toInt());
                } else if (filter["filterType"].toInt() ==
                           static_cast<int>(
                               MidiRoutersFilter::FilterType::TO_NETWORK)) {
                    midiRouterChain->addFilterNetworkDestination(
                        filter["serverName"].toString(), filter["serverPort"].toInt(),
                        filter["baseMidiRouteInput"]
                            .toObject()["midiInputName"]
                            .toString());
                } else if (filter["filterType"].toInt() ==
                           static_cast<int>(
                               MidiRoutersFilter::FilterType::FILTER_AND_TRANSFORM)) {
                    midiRouterChain->addFilterAndTransform(
                        filter["name"].toString(),
                        static_cast<FilterAndTransform::ConditionAction>(
                            filter["conditionAction"].toInt()),
                        filter["filterChannel"].toString(),
                        filter["filterEvents"].toString(),
                        filter["filterData1"].toString(),
                        filter["filterData2"].toString());
                }
            }
        }
    }



    //- {fn}
    QList<int> extractKeyboardSplits(const QJsonArray &array)
    //-only-file body
    {
        QList<int> keyboardSplits;
        for (const QJsonValue &value : array) {
            keyboardSplits.push_back(value["splitPosition"].toInt());
        }
        return keyboardSplits;
    }





    //-only-file header
};
