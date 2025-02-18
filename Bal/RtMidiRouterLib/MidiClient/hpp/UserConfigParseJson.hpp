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


        userDataConfigItf->setActivePresetID(getJsonDouble( jsonDoc["_activePresetID"]));

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
            auto obj = getJsonObject(value);
            userDataConfig->addDropdownList(getJsonString(obj["name"]),
                                            getJsonString(obj["data"])                                                );
        }

    }

    //- {fn}
    void purgeDeletedCreateMissing(const std::function<QString(int)>& getUuid,
                                   const std::function<void(QString)>& createNewObject,
                                   const int qlistObjSize,
                                   const std::function<void(int)>& qlistRemoveAt,
                                   QJsonArray &midiRoutePresetsArray)
    //-only-file body
    {
        QStringList presetUuidInJson;


        for (const auto &value : midiRoutePresetsArray) {
            auto valueObj = getJsonObject(value);
            presetUuidInJson.push_back( getJsonString(valueObj["uuid"]));
        }

        QStringList uuidInPresets;
        for (auto it = qlistObjSize - 1; it >= 0; --it) {
            QString uuid = getUuid(it);
            bool containsUuid =  presetUuidInJson.contains(uuid);
            if (containsUuid) {
                uuidInPresets.append(uuid);
            }
            else {
                qlistRemoveAt(it);
            }
        }

        for (const auto &j: presetUuidInJson){
            if (!uuidInPresets.contains(j)){
                createNewObject(j);
            }
        }
    }

    //-only-file header
    template<typename T>
    T* getObjByUuid(const QList<T*>& presets, const QString& uuid) {
        for (auto const& preset : presets) {
            if (preset->uuid() == uuid) {
                return preset;
            }
        }
        return nullptr; // Return nullptr if no match is found
    }



    //- {fn}
    void updateMidiRoutePresets(UserDataConfigItf *userDataConfig, const QJsonValueRef &midiRoutePresets)
    //-only-file body
    {        
        userDataConfig->clearMidiRoutePresets(); //TEMPORARY TO TEST RECREATE
        auto midiRoutePresetsArray = getJsonArray(midiRoutePresets);
        purgeDeletedCreateMissing
            ([&userDataConfig](int idx){
                return userDataConfig->midiRoutePresets().at(idx)->uuid();
            },
             [&userDataConfig](QString uuid){
                 MidiRoutePreset *preset = new MidiRoutePreset(userDataConfig->computerUuid());
                 userDataConfig->addMidiRoutePresets(preset);
                 preset->setUuid(uuid);
             },
             userDataConfig->midiRoutePresets().size(),
             [&userDataConfig](int idx){
                 userDataConfig->delMidiRoutePresets(idx);
             },
             midiRoutePresetsArray);


        for (const auto &value : midiRoutePresetsArray) {
            auto valueObj = getJsonObject(value);
            QString uuid = getJsonString(valueObj["uuid"]);
            auto preset = getObjByUuid(userDataConfig->midiRoutePresets(),uuid);
            if (preset == nullptr) {
                throw std::runtime_error("Unexpected JSON format");
            }
            preset->setIsEnabled(getJsonBool( valueObj["isEnabled"]));
            preset->setName(getJsonString(valueObj["name"]));
            preset->setIsSendAllUserControls(getJsonBool(valueObj["isSendAllUserControls"]));


            updateMidiControl(preset->midiControlOn(), valueObj["midiControlOn"], PresetMidiControl::PresetMidiType::PRESET_ON);
            updateMidiControl(preset->midiControlOff(), valueObj["midiControlOff"], PresetMidiControl::PresetMidiType::PRESET_OFF);

            //update userControls
            updateUserControls(preset, valueObj);
            //update midirouteInputs
            //Delete these two lines


        }
    }

    //- {fn}
    void updateUserControls(MidiRoutePreset *preset, QJsonObject &presetJsonObj)
    //-only-file body
    {
        preset->clearUserControls(); //TEMPORARY TO TEST RECREATE
        auto userControlsArray = getJsonArray(presetJsonObj["userControls"]);
        purgeDeletedCreateMissing
            ([&preset](int idx){
                return preset->userControls().at(idx)->uuid();
            },
             [&preset](QString uuid){
                 UserControl *userControl = new UserControl();
                 preset->addUserControls(userControl);
                 userControl->setUuid(uuid);
             },
             preset->userControls().size(),
             [&preset](int idx){
                 preset->delUserControls(idx);
             },
             userControlsArray);

        for (const auto &value : userControlsArray) {
            auto userControlJsonObj = getJsonObject(value);
            QString uuid = getJsonString(userControlJsonObj["uuid"]);
            auto userControl = getObjByUuid(preset->userControls(),uuid);
            if (userControl == nullptr) {
                throw std::runtime_error("Unexpected JSON format");
            }

            userControl->setEventType(static_cast<UserControl::EventType>(getJsonDouble(userControlJsonObj["eventType"])));
            userControl->setDescription(getJsonString( userControlJsonObj["description"]));
            userControl->setInputVal(getJsonDouble(userControlJsonObj["inputVal"]));
            userControl->setMinVal(getJsonDouble(userControlJsonObj["minVal"]));
            userControl->setMaxVal(getJsonDouble(userControlJsonObj["maxVal"]));
            userControl->setIs64Mode(getJsonBool(userControlJsonObj["is64Mode"]));
            userControl->setIsEditMode(getJsonBool(userControlJsonObj["isEditMode"]));
            userControl->setChannelId(getJsonDouble(userControlJsonObj["channelId"]));
            userControl->setCcId(getJsonDouble(userControlJsonObj["ccId"]));
            userControl->setNrpnControl(getJsonDouble(userControlJsonObj["nrpnControl"]));
            userControl->setOutputPortnName(getJsonString(userControlJsonObj["outputPortnName"]));
            userControl->setIsShowDropdown(getJsonBool(userControlJsonObj["isShowDropdown"]));
            userControl->setDropdownListId(getJsonDouble(userControlJsonObj["dropdownListId"]));
        }
    }

    //-only-file header
    /*
    MidiRoutePreset* createMidiRoutePreset(UserDataConfigItf *userDataConfig, const QJsonValueRef &value)
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
    */

    //- {fn}
    void updateMidiControl(PresetMidiControl *control,  const QJsonValueRef &value, PresetMidiControl::PresetMidiType type)
    //-only-file body
    {
        auto valueObj = getJsonObject(value);
        control->setChannel(getJsonDouble( valueObj["channel"]));
        control->setData1(getJsonDouble(valueObj["data1"]));
        control->setData2(getJsonDouble(valueObj["data2"]));
        control->setEventTypeId(getJsonDouble(valueObj["eventTypeId"]));
        control->setPresetMidiType(type);
        control->setPortName(getJsonString(valueObj["portName"]));
        control->setPresetUuid(getJsonString(valueObj["presetUuid"]));
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
    QJsonObject getJsonObject(QJsonValueRef obj)
    //-only-file body
    {
        if (obj.isObject()){
            return obj.toObject();
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

    //- {fn}
    bool getJsonBool(QJsonValueRef obj)
    //-only-file body
    {
        if(obj.isBool()){
            return obj.toBool();
        } else {
            throw std::runtime_error("Unexpected JSON format");
        }
    }

    //- {fn}
    double getJsonDouble(QJsonValueRef obj)
    //-only-file body
    {
        if(obj.isDouble()){
            return obj.toDouble();
        } else {
            throw std::runtime_error("Unexpected JSON format");
        }
    }

    //-only-file header
};


