//-define-file body GenHpp/UserConfigParseJson.cpp
//-define-file header GenHpp/UserConfigParseJson.h
//-only-file header //-
#pragma once
#include <QtCore/qjsonarray.h>
#include <QtCore/qjsondocument.h>
//- #include "UserDataConfig.h"
//-only-file null
#include "UserDataConfig.hpp"
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
    void setChanges(UserDataConfig *userDataConfigItf, QJsonObject &jsonDoc)
    //-only-file body
    {

        userDataConfigItf->setConnectedInPorts(stringListFromJsonAry(jsonDoc["connectedInPorts"]));
        userDataConfigItf->setConnectedOutPorts(stringListFromJsonAry(jsonDoc["connectedOutPorts"]));

        bool isServerInitialConfig = !jsonDoc["uniqueId"].isString();
        if (isServerInitialConfig){
            return;
        }

        if (userDataConfigItf->uniqueId() == getJson<QString>(jsonDoc["uniqueId"])){
            qDebug()<<"Same session created the config, return;";
            //return;
        }

        updateVirtualInPorts(userDataConfigItf,stringListFromJsonAry(jsonDoc["virtualInPorts"]));

        updateDropdownlists(userDataConfigItf, jsonDoc["dropdownlists"]);

        recreateSettings<UserDataConfig, MidiRoutePreset>(userDataConfigItf,jsonDoc,"midiRoutePresets");


        userDataConfigItf->setActivePreset(getJson<double>( jsonDoc["_activePresetID"]), false);

    }

    //-only-file header
private:
    //- {fn}
    void updateVirtualInPorts(UserDataConfig *userDataConfig, const QStringList &virtualInPorts)
    //-only-file body
    {
        userDataConfig->clearVirtualPorts();
        for (const auto &value : virtualInPorts) {
            userDataConfig->addVirtualPort(value);
        }
    }

    //- {fn}
    void updateDropdownlists(UserDataConfig *userDataConfig, const QJsonValueRef &dropdownlists)
    //-only-file body
    {
        userDataConfig->clearList<Dropdownlist *>();

        auto array = getJsonArray(dropdownlists);
        for (const auto &value : array) {
            auto obj = getJson<QJsonObject>(value);
            userDataConfig->addDropdownList(getJson<QString>(obj["name"]),
                                            getJson<QString>(obj["data"])                                                );
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
            auto valueObj = getJson<QJsonObject>(value);
            presetUuidInJson.push_back( getJson<QString>(valueObj["uuid"]));
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

    template<typename T, typename S>
    void purgeDeletedCreateMissingT(S *userDataConfig, QJsonArray &jsonAry){
        purgeDeletedCreateMissing
            ([&userDataConfig](int idx){
                return userDataConfig->template listItems<T *>().at(idx)->uuid();
            },
             [&userDataConfig](QString uuid){
                 T *preset = new T();
                 userDataConfig->addListItem(preset);
                 preset->setUuid(uuid);
             },
             userDataConfig->template listItems<T *>().size(),
             [&userDataConfig](int idx){
                 userDataConfig->template delListItem<T *>(idx);
             },
             jsonAry);
    }

    template<typename Parent, typename ChildListType>
    void recreateSettings(Parent *parent, QJsonObject &midirouteInputJsonObj, QString arrayListKey){
        parent->template clearList<ChildListType *>(); //TEMPORARY TO TEST RECREATE
        auto midiRouterChainsArray = getJsonArray(midirouteInputJsonObj[arrayListKey]);
        purgeDeletedCreateMissingT<ChildListType>(parent,midiRouterChainsArray);

        for (const auto &value : midiRouterChainsArray) {
            auto midiRouterChainsJsonObj = getJson<QJsonObject>(value);
            QString uuid = getJson<QString>(midiRouterChainsJsonObj["uuid"]);

            auto midiRouterChain = getObjByUuid(parent->template listItems<ChildListType *>(),uuid);
            if (midiRouterChain == nullptr) {
                throw std::runtime_error("Unexpected JSON format");
            }
            setSettings(midiRouterChain, midiRouterChainsJsonObj);
        }
    }


    //- {fn}
    void updateMidirouteInputs(MidiRoutePreset *preset, QJsonObject &presetJsonObj)
    //-only-file body
    {

        recreateSettings<MidiRoutePreset, MidiRouteInput>(preset,presetJsonObj,"midiRouteInputs");

    }

    //- {fn}
    void setSettings(MidiRoutePreset *preset,QJsonObject &valueObj)
    //-only-file body
    {
        preset->setIsEnabled(getJson<bool>( valueObj["isEnabled"]));
        preset->setName(getJson<QString>(valueObj["name"]));
        preset->setIsSendAllUserControls(getJson<bool>(valueObj["isSendAllUserControls"]));


        updateMidiControl(preset->midiControlOn(), valueObj["midiControlOn"], PresetMidiControl::PresetMidiType::PRESET_ON);
        updateMidiControl(preset->midiControlOff(), valueObj["midiControlOff"], PresetMidiControl::PresetMidiType::PRESET_OFF);

        updateUserControls(preset, valueObj);
        updateMidirouteInputs(preset, valueObj);
    }

    //- {fn}
    void setSettings(UserControl *userControl,QJsonObject &userControlJsonObj)
    //-only-file body
    {
        userControl->setEventType(static_cast<UserControl::EventType>(getJson<double>(userControlJsonObj["eventType"])));
        userControl->setDescription(getJson<QString>( userControlJsonObj["description"]));
        userControl->setInputVal(getJson<double>(userControlJsonObj["inputVal"]));
        userControl->setMinVal(getJson<double>(userControlJsonObj["minVal"]));
        userControl->setMaxVal(getJson<double>(userControlJsonObj["maxVal"]));
        userControl->setIs64Mode(getJson<bool>(userControlJsonObj["is64Mode"]));
        userControl->setIsEditMode(getJson<bool>(userControlJsonObj["isEditMode"]));
        userControl->setChannelId(getJson<double>(userControlJsonObj["channelId"]));
        userControl->setCcId(getJson<double>(userControlJsonObj["ccId"]));
        userControl->setNrpnControl(getJson<double>(userControlJsonObj["nrpnControl"]));
        userControl->setOutputPortnName(getJson<QString>(userControlJsonObj["outputPortnName"]));
        userControl->setIsShowDropdown(getJson<bool>(userControlJsonObj["isShowDropdown"]));
        userControl->setDropdownListId(getJson<double>(userControlJsonObj["dropdownListId"]));
    }


    //- {fn}
    void setSettings(MidiRouterChain *midiRouterChain,QJsonObject &midiRouterChainsJsonObj)
    //-only-file body
    {
        midiRouterChain->setName(getJson<QString>(midiRouterChainsJsonObj["name"]));
        midiRouterChain->setIsEasyConfig(getJson<bool>(midiRouterChainsJsonObj["isEasyConfig"]));
    }

    //- {fn}
    void updateUserControls(MidiRoutePreset *preset, QJsonObject &presetJsonObj)
    //-only-file body
    {
        recreateSettings<MidiRoutePreset, UserControl>(preset,presetJsonObj,"userControls");
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
        auto valueObj = getJson<QJsonObject>(value);
        control->setChannel(getJson<double>( valueObj["channel"]));
        control->setData1(getJson<double>(valueObj["data1"]));
        control->setData2(getJson<double>(valueObj["data2"]));
        control->setEventTypeId(getJson<double>(valueObj["eventTypeId"]));
        control->setPresetMidiType(type);
        control->setPortName(getJson<QString>(valueObj["portName"]));
        control->setPresetUuid(getJson<QString>(valueObj["presetUuid"]));
    }



    //- {fn}
    void updateMidiRouteInputsDELETE(MidiRoutePreset *preset, const QJsonObject &midiRouteInputs)
    //-only-file body
    {
        preset->clearList<MidiRouteInput *>();
        for (auto it = midiRouteInputs.begin(); it != midiRouteInputs.end(); ++it) {
            MidiRouteInput *midiRouteInputEntry = createMidiRouteInputEntryDELTE( it.value().toObject());
            preset->addListItem(midiRouteInputEntry);
            auto easyConfig = it.value().toObject()["easyConfig"];
            auto inputZonesAndRoutes = easyConfig.toObject()["inputZonesAndRoutes"];
            if (easyConfig.isObject() && inputZonesAndRoutes.isObject()) {
                createEasyConfigEntry(midiRouteInputEntry->easyConfig(),  inputZonesAndRoutes.toObject());
            }
        }
    }

    //- {fn}
    void setSettings(MidiRouteInput *midiRouteInput, QJsonObject &midirouteInputJsonObj)
    //-only-file body
    {
        midiRouteInput->setMidiInputName(getJson<QString>( midirouteInputJsonObj["midiInputName"]));

        auto ignoreTypes = getJson<QJsonObject>(midirouteInputJsonObj["ignoreTypes"]);
        midiRouteInput->setIgnoreTypesMidiSysex(getJson<bool>( ignoreTypes["midiSysex"]));
        midiRouteInput->setIgnoreTypesMidiTime(getJson<bool>( ignoreTypes["midiTime"]));
        midiRouteInput->setIgnoreTypesMidiSense(getJson<bool>( ignoreTypes["midiSense"]));

         auto midiRouteClock = getJson<QJsonObject>(midirouteInputJsonObj["midiRouteClock"]);
        midiRouteInput->setMidiRouteClockTimeSig(getJson<double>( midiRouteClock["timeSig"]));
        midiRouteInput->setMidiRouteClockTimeSigDivBy(getJson<double>( midiRouteClock["timeSigDivBy"]));
        midiRouteInput->setMidiRouteClockFromSppPos(getJson<double>( midiRouteClock["fromSppPos"]));


        auto propegateInputs = getJsonArray(midiRouteClock["propegateInputs"]);
        QStringList propegateInputsList;
        for (const auto &propegateVal : propegateInputs) {
            propegateInputsList.push_back(propegateVal.toObject()["midiInputName"].toString());
        }
        midiRouteInput->setMidiRouteClockPropegateInputs(propegateInputsList);


        auto cc14bitAry = getJsonArray(midirouteInputJsonObj["cc14bitAry"]);
        midiRouteInput->clearList<MidiRouteInputCc14bit *>();
        for (const auto &cc14bit : cc14bitAry) {
            auto midiRouteInputCc14bit = new MidiRouteInputCc14bit();
            auto cc14bitObj = getJson<QJsonObject>(cc14bit);
            midiRouteInputCc14bit->setChannel(getJson<double>(cc14bitObj["channel"]));
            midiRouteInputCc14bit->setCc(getJson<double>(cc14bitObj["cc"]));
            midiRouteInput->addListItem(midiRouteInputCc14bit);
        }
        recreateSettings<MidiRouteInput, MidiRouterChain>(midiRouteInput,midirouteInputJsonObj, "midiRouterChains");
    }

    //- {fn}
    MidiRouteInput* createMidiRouteInputEntryDELTE(const QJsonObject &value)
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
            //now all midi Chains and Filters
            for (const auto &fval : midiRouterChains.toArray()) {
                auto midiRouterChain = new MidiRouterChain();
                auto val = fval.toObject();
                midiRouterChain->setName(val["name"].toString());
                midiRouterChain->setIsEasyConfig(val["isEasyConfig"].isBool());


                //now for filters
                updateMidiRoutersFilters(val["midiRoutersFilters"],midiRouterChain);


                midiRouteInputEntry->addListItem(midiRouterChain);
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
                easyConfigEntry->addListItem(easyConfigRoute);
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
            s.append(getJson<QString>(value));
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

    //-only-file header
    template<typename T>
    T getJson(QJsonValueRef obj);

    template<>
    QJsonObject getJson(QJsonValueRef obj){
        if (obj.isObject()){
            return obj.toObject();
        } else {
            throw std::runtime_error("Unexpected JSON format");
        }
    }

    template<>
    QString  getJson(QJsonValueRef obj){
        if(obj.isString()){
            return obj.toString();
        } else {
            throw std::runtime_error("Unexpected JSON format");
        }
    }

    template<>
    bool  getJson(QJsonValueRef obj){
        if(obj.isBool()){
            return obj.toBool();
        } else {
            throw std::runtime_error("Unexpected JSON format");
        }
    }

    template<>
    double  getJson(QJsonValueRef obj){
        if(obj.isDouble()){
            return obj.toDouble();
        } else {
            throw std::runtime_error("Unexpected JSON format");
        }
    }



    //-only-file header
};


