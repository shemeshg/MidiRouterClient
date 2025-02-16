//-define-file body GenHpp/UserConfigParseJson.cpp
//-define-file header GenHpp/UserConfigParseJson.h
//-only-file header //-
#pragma once
#include <QtCore/qjsonarray.h>
#include <QtCore/qjsondocument.h>
//- #include "UserDataConfigItf.h"
//-only-file null
#include "UserDataConfigItf.hpp"
//-only-file body //-
//- #include "UserConfigParseJson.h"
//-only-file header

//-var {PRE} "UserConfigParseJson::"
class UserConfigParseJson
{
public:
    UserConfigParseJson(){
    }

    //- {fn}
    void setChanges(UserDataConfigItf *userDataConfigItf, QJsonObject &jsonDoc)
    //-only-file body
    {

        userDataConfigItf->setConnectedInPorts(stringListFromJsonAry(jsonDoc["connectedInPorts"]));
        userDataConfigItf->setConnectedOutPorts(stringListFromJsonAry(jsonDoc["connectedOutPorts"]));

        bool isServerInitialConfig = !jsonDoc["uniqueId"].isString();
        if (isServerInitialConfig){
            return;
        }

        if (userDataConfigItf->getUniqueId() == getJsonString(jsonDoc["uniqueId"])){
            qDebug()<<"Same session created the config, return;";
            //return;
        }

        updateVirtualInPorts(userDataConfigItf,stringListFromJsonAry(jsonDoc["virtualInPorts"]));

        updateDropdownlists(userDataConfigItf, jsonDoc["dropdownlists"]);

        updateMidiRoutePresets(userDataConfigItf, jsonDoc["midiRoutePresets"]);

        if (jsonDoc["_activePresetID"].isDouble()) {
            userDataConfigItf->setActivePresetID(jsonDoc["_activePresetID"].toInt());
        }
    }

    //-only-file header
private:
    //- {fn}
    void updateVirtualInPorts(UserDataConfigItf *userDataConfig, const QStringList &virtualInPorts)
    //-only-file body
    {
            userDataConfig->clearVirtualPorts();
            for (const auto &value : virtualInPorts) {
                userDataConfig->addVirtualPort(value);
            }
    }

    //- {fn}
    void updateDropdownlists(UserDataConfigItf *userDataConfig, const QJsonValueRef &dropdownlists)
    //-only-file body
    {
        userDataConfig->clearDropdownlists();

            auto array = getJsonArray(dropdownlists);
            for (const auto &value : array) {
                auto obj = value.toObject();
                userDataConfig->addDropdownList(getJsonString(obj["name"]),
                                                getJsonString(obj["data"])                                                );
            }

    }

    //- {fn}
    void purgeDeletedCreateMissingPresets(UserDataConfigItf *userDataConfig, const QJsonValueRef &midiRoutePresets)
    //-only-file body
    {
        QStringList presetUuidInJson;

        auto array = getJsonArray(midiRoutePresets);
        for (const auto &value : array) {
            auto valueObj = value.toObject();
            presetUuidInJson.push_back( getJsonString(valueObj["uuid"]));
        }

        QStringList uuidInPresets;
        for (auto it = userDataConfig->midiRoutePresets().size() - 1; it >= 0; --it) {
            QString uuid = userDataConfig->midiRoutePresets().at(it)->uuid();
            bool containsUuid =  presetUuidInJson.contains(uuid);
            if (containsUuid) {
                uuidInPresets.append(uuid);
            }
            else {
                userDataConfig->delMidiRoutePresets(it);
            }
        }

        for (const auto &j: presetUuidInJson){
            if (!uuidInPresets.contains(j)){
                MidiRoutePreset *preset = new MidiRoutePreset(userDataConfig->computerUuid());

                userDataConfig->addMidiRoutePresets(preset);
                preset->setUuid(j);
            }
        }
    }

    //- {fn}
    void updateMidiRoutePresets(UserDataConfigItf *userDataConfig, const QJsonValueRef &midiRoutePresets)
    //-only-file body
    {

        //userDataConfig->clearMidiRoutePresets(); //UNMARK TO TEST RECREATE
        purgeDeletedCreateMissingPresets(userDataConfig,midiRoutePresets);
        return;


        if (midiRoutePresets.isArray()){
            auto array = midiRoutePresets.toArray();
            for (const QJsonValue &value : array) {
                //get preset by uuid
                //update preset fields
                //update preset updateMidiControl
                //update userControls
                //update midirouteInputs
                //Delete these two lines
                MidiRoutePreset *preset = createMidiRoutePreset(userDataConfig,value);
                userDataConfig->addMidiRoutePresets(preset);
            }

        }
    }

    //- {fn}
    MidiRoutePreset* createMidiRoutePreset(UserDataConfigItf *userDataConfig, const QJsonValue &value)
    //-only-file body
    {
        auto preset = new MidiRoutePreset(userDataConfig->computerUuid());
        preset->setName(value["name"].toString());
        preset->setIsSendAllUserControls(value["isSendAllUserControls"].toBool());
        preset->setUuid(value["uuid"].toString());
        preset->setIsEnabled(value["isEnabled"].toBool());

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

    //- {fn}
    void updateMidiControl(PresetMidiControl *control, const QJsonValue &value, PresetMidiControl::PresetMidiType type)
    //-only-file body
    {
        control->setChannel(value["channel"].toInt());
        control->setData1(value["data1"].toInt());
        control->setData2(value["data2"].toInt());
        control->setEventTypeId(value["eventTypeId"].toInt());
        control->setPresetMidiType(type);
        control->setPortName(value["portName"].toString());
        control->setPresetUuid(value["presetUuid"].toString());
    }

    //- {fn}
    UserControl* createUserControl(const QJsonValue &userControlValue)
    //-only-file body
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

    //- {fn}
    void updateMidiRouteInputs(MidiRoutePreset *preset, const QJsonObject &midiRouteInputs)
    //-only-file body
    {
        preset->clearMidiRouteInputs();
        for (auto it = midiRouteInputs.begin(); it != midiRouteInputs.end(); ++it) {
            MidiRouteInput *midiRouteInputEntry = createMidiRouteInputEntry( it.value().toObject());
            preset->addMidiRouteInputs(midiRouteInputEntry);
            auto easyConfig = it.value().toObject()["easyConfig"];
            auto inputZonesAndRoutes = easyConfig.toObject()["inputZonesAndRoutes"];
            if (easyConfig.isObject() && inputZonesAndRoutes.isObject()) {
                createEasyConfigEntry(midiRouteInputEntry->easyConfig(),  inputZonesAndRoutes.toObject());
            }
        }
    }

    //- {fn}
    MidiRouteInput* createMidiRouteInputEntry(const QJsonObject &value)
    //-only-file body
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

    //- {fn}
    void updateMidiRoutersFilters(const QJsonValueRef &midiRoutersFilters, MidiRouterChain *midiRouterChain)
    //-only-file body
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


    //- {fn}
    void createEasyConfigEntry(EasyConfig *easyConfigEntry ,const QJsonObject &value)
    //-only-file body
    {


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

    //- {fn}
    QStringList convertToQStringList(const QJsonArray &array)
    //-only-file body
    {
        QStringList stringList;
        for (const QJsonValue &value : array) {
            stringList.append(value.toString());
        }
        return stringList;
    }

    //- {fn}
    EasyConfigRoute* createEasyConfigRoute(const QJsonObject &value)
    //-only-file body
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

    //- {fn}
    QStringList stringListFromJsonAry(const QJsonValueRef &j)
    //-only-file body
    {
        QStringList s;

        for (const auto &value : getJsonArray(j)) {
            s.append(getJsonString(value));
        }

        return s;
    }

    //- {fn}
    QJsonArray getJsonArray(QJsonValueRef obj)
    //-only-file body
    {
        if (obj.isArray()){
            return obj.toArray();
        } else {
            throw std::runtime_error("Unexpected JSON format");
        }
    }

    //- {fn}
    QString getJsonString(QJsonValueRef obj)
    //-only-file body
    {
        if(obj.isString()){
            return obj.toString();
        } else {
            throw std::runtime_error("Unexpected JSON format");
        }
    }

    //-only-file header
};


