//-define-file body GenHpp/UserConfigGenJson.cpp
//-define-file header GenHpp/UserConfigGenJson.h
//-only-file header //-
#pragma once
//- #include "UserDataConfig.h"
//-only-file null
//-only-file body //-
//- #include "UserConfigGenJson.h"
//- #include "UserConfigGenJson.h"
//- #include "GenHpp/MidiPresetControlEasyConfig.h"
//-only-file null
#include "UserDataConfig.hpp"
//-only-file header
#include <QtCore/qjsonobject.h>

//-var {PRE} "UserConfigGenJson::"
class UserConfigGenJson
{
public:    
    UserConfigGenJson(){}

    //- {function} 0 1
    QJsonObject getJson(UserDataConfig *userDataConfig)
    //-only-file body
    {
        QJsonObject objUserConfig;
        objUserConfig["_activePresetID"] = userDataConfig->activePresetID();
        objUserConfig["dropdownlists"]= getDropdownList(userDataConfig);
        objUserConfig["virtualInPorts"] = getListToJsonAry(userDataConfig->virtualInPorts());
        objUserConfig["midiRoutePresets"] = getMidiRoutePresets(userDataConfig);

        return objUserConfig;
    }

    //-only-file header
private:

    //- {function} 0 1
    QJsonArray getDropdownList(UserDataConfig *userDataConfig)
    //-only-file body
    {
        QJsonArray ary;
        for (const auto itm: userDataConfig->dropdownlists()){
            QJsonObject obj;
            obj["name"] = itm->name();
            obj["data"] = itm->data();
            ary.append(obj);
        }
        return ary;
    }

    //- {function} 0 1
    QJsonArray getListToJsonAry(const QStringList &sl)
    //-only-file body
    {
        QJsonArray ary;
        for (const auto &itm: sl){
            ary.append(itm);
        }
        return ary;
    }

    //- {function} 0 1
    QJsonArray getListToJMidiInsonAry(const QStringList &sl)
    //-only-file body
    {
        QJsonArray ary;
        for (const auto &itm: sl){
            QJsonObject obj;
            obj["midiInputName"] = itm;
            ary.append(obj);
        }
        return ary;
    }

    //- {function} 0 1
    QJsonArray getMidiRoutePresets(UserDataConfig *userDataConfig)
    //-only-file body
    {


        QJsonArray ary;
        for (const auto &itm: userDataConfig->midiRoutePresets()){
            QJsonObject obj;
            auto presetControlEasyConfigs = getMidiPresetControlEasyConfigs( userDataConfig);
            itm->recreateEasyConfig(presetControlEasyConfigs);
            obj["name"] = itm->name();
            obj["uuid"] = itm->uuid();
            obj["isEnabled"] = itm->isEnabled();
            obj["isSendAllUserControls"] = itm->isSendAllUserControls();
            obj["midiControlOn"] = getModiControlOnOff(itm->midiControlOn());
            obj["midiControlOff"] = getModiControlOnOff(itm->midiControlOff());
            obj["midiRouteInputs"] = getMidiRouteInputs(itm->midiRouteInputs());
            obj["userControls"] = getUserControls(itm->userControls());
            obj["easyConfig"] = getEasyConfig(itm->easyConfig());
            //DUMMY DELETE
            QJsonArray dummyAry;
            QJsonObject dummyObj;
            dummyObj["jsToServers"] = dummyAry;
            obj["jsRouter"] = dummyObj;
            //END DUMMY DELETE
            ary.append(obj);
        }
        return ary;
    }

    //- {function} 0 1
    QJsonObject getEasyConfig(QList<EasyConfig *> easyConfigList)
    //-only-file body
    {
        QJsonObject obj;
        //auto inputZonesAndRoutes = obj["inputZonesAndRoutes"].toObject();

        QJsonObject inputZonesAndRoutes;
        for (const auto &easyConfig: easyConfigList){

            QJsonObject  easyConfigInput;
            auto midiInputName = easyConfig->midiInputName();
            easyConfigInput["midiInputName"] = midiInputName;
            easyConfigInput["keyboardSplits"] = getKeyboardSplits(easyConfig->keyboardSplits());
            easyConfigInput["zoneNames"] = getStringListToJsonAry(easyConfig->zoneNames());
            easyConfigInput["easyConfigRoutes"] = getEasyConfigRoutes(easyConfig->easyConfigRoutes(),midiInputName);

            inputZonesAndRoutes[midiInputName] = easyConfigInput;
        }
        obj["inputZonesAndRoutes"] = inputZonesAndRoutes;
        return obj;
    }

    //- {function} 0 1
    QJsonArray getEasyConfigRoutes(QList<EasyConfigRoute *> easyConfigRoutes,  QString midiInputName)
    //-only-file body
    {
        QJsonArray ary;
        for (const auto &easyConfigRoute: easyConfigRoutes){
            QJsonObject obj;
            obj["midiInputName"] = midiInputName;
            obj["splitRangeId"] = easyConfigRoute->splitRangeId();
            obj["fromSelectedMidiEventTypeId"] = easyConfigRoute->fromSelectedMidiEventTypeId();
            obj["fromChannel"] = easyConfigRoute->fromChannel();
            obj["fromData1"] = easyConfigRoute->fromData1();
            obj["transpose"] = easyConfigRoute->transpose();
            obj["fromCcOrNrpnStart"] = easyConfigRoute->fromCcOrNrpnStart();
            obj["fromCcOrNrpnEnd"] = easyConfigRoute->fromCcOrNrpnEnd();
            obj["toCcOrNrpnStart"] = easyConfigRoute->toCcOrNrpnStart();
            obj["toCcOrNrpnEnd"] = easyConfigRoute->toCcOrNrpnEnd();
            obj["toSelectedMidiEventTypeId"] = easyConfigRoute->toSelectedMidiEventTypeId();
            obj["toChannel"] = easyConfigRoute->toChannel();
            obj["toData1"] = easyConfigRoute->toData1();
            obj["toDestinationName"] = easyConfigRoute->toDestinationName();

            ary.append(obj);
        }
        return ary;

    }

    //- {function} 0 1
    QJsonArray getStringListToJsonAry(QStringList list )
    //-only-file body
    {
        QJsonArray ary;
        for (const auto &str: list){
            ary.append(str);
        }
        return ary;
    }

    //- {function} 0 1
    QJsonArray getKeyboardSplits(QList<int> keyboardSplits)
    //-only-file body
    {
        QJsonArray ary;
        for (const auto &keyboardSplit: keyboardSplits){
            QJsonObject obj;
            obj["splitPosition"] = keyboardSplit;
            ary.append(obj);
        }
        return ary;
    }

    //- {function} 0 1
    QJsonObject getModiControlOnOff(PresetMidiControl *presetMidiControl)
    //-only-file body
    {
        QJsonObject obj;
        obj["presetUuid"] = presetMidiControl->presetUuid();
        obj["presetMidiType"] = static_cast<int>(presetMidiControl->presetMidiType());
        obj["portName"] = presetMidiControl->portName();
        obj["eventTypeId"] = presetMidiControl->eventTypeId();
        obj["channel"] = presetMidiControl->channel();
        obj["data1"] = presetMidiControl->data1();
        obj["data2"] = presetMidiControl->data2();
        return obj;
    }

    //- {function} 0 1
    QJsonObject getMidiRouteInputs(QList<MidiRouteInput *> midiRouteInputs)
    //-only-file body
    {
        QJsonObject obj;
        for (const auto &itm: midiRouteInputs){
            obj[itm->midiInputName()] = getMidiRouteInput(itm);
        }
        return obj;
    }

    //- {function} 0 1
    QJsonArray getCc14bitAry(MidiRouteInput *midiRouteInput)
    //-only-file body
    {
        QJsonArray cc14bitAry;
        for (const auto &cc14bit: midiRouteInput->midiRouteInputCc14bit()){
            QJsonObject cc14bitObj;
            cc14bitObj["channel"] = cc14bit->channel();
            cc14bitObj["cc"] = cc14bit->cc();
            cc14bitAry.append(cc14bitObj);
        }

        return cc14bitAry;
    }

    //- {function} 0 1
    QJsonObject getMidiRouteClock(MidiRouteInput *midiRouteInput)
    //-only-file body
    {
        QJsonObject midiRouteClock;
        midiRouteClock["timeSig"] = midiRouteInput->midiRouteClockTimeSig();
        midiRouteClock["timeSigDivBy"] = midiRouteInput->midiRouteClockTimeSigDivBy();
        midiRouteClock["fromSppPos"] = midiRouteInput->midiRouteClockFromSppPos();
        midiRouteClock["propegateInputs"] = getListToJMidiInsonAry(midiRouteInput->midiRouteClockPropegateInputs());

        return midiRouteClock;
    }

    //- {function} 0 1
    QJsonObject getIgnoreTypes(MidiRouteInput *midiRouteInput)
    //-only-file body
    {
        QJsonObject ignoreTypes;
        ignoreTypes["midiSysex"] = midiRouteInput->ignoreTypesMidiSysex();
        ignoreTypes["midiTime"] = midiRouteInput->ignoreTypesMidiTime();
        ignoreTypes["midiSense"] = midiRouteInput->ignoreTypesMidiSense();

        return ignoreTypes;
    }

    //- {function} 0 1
    QJsonObject getMonitor(MidiRouteInput *midiRouteInput)
    //-only-file body
    {
        QJsonObject monitor;
        monitor["isMonitored"] = midiRouteInput->monitor()->isMonitored();
        return monitor;
    }

    //- {function} 0 1
    QJsonArray getMidiRouterChains(MidiRouteInput *midiRouteInput)
    //-only-file body
    {
        QJsonArray midiRouterChains;
        for (const auto midiRouterChain: midiRouteInput->midiRouterChains()){
            QJsonObject midiRouterChainObj;
            midiRouterChainObj["name"] = midiRouterChain->name();
            midiRouterChainObj["isEasyConfig"] = midiRouterChain->isEasyConfig();
            midiRouterChainObj["isRunForPresetOnAndOff"] = midiRouterChain->isRunForPresetOnAndOff();
            midiRouterChainObj["midiRoutersFilters"] = getMidiRoutersFilters(midiRouterChain->midiRoutersFilters());
            midiRouterChains.append(midiRouterChainObj);
        }

        return midiRouterChains;
    }

    //- {function} 0 1
    QJsonObject getBaseMidiRouteInput(QString strMidiInputName)
    //-only-file body
    {
        QJsonObject obj;
        obj["midiInputName"] = strMidiInputName;
        return obj;
    }

    //- {function} 0 1
    QJsonArray getMidiRoutersFilters(QList<QVariant> midiRoutersFilters)
    //-only-file body
    {
        QJsonArray ary;
        for (const auto &midiRoutersFilter: midiRoutersFilters ){
            QJsonObject filterObj;
            if (midiRoutersFilter.canConvert<FilterMidiDestination*>()) {
                auto filter = midiRoutersFilter.value<FilterMidiDestination*>();
                filterObj["filterType"] = static_cast<int>(filter->filterType());
                filterObj["baseMidiRouteInput"]= getBaseMidiRouteInput(filter->baseMidiRouteInput());
                ary.append(filterObj);
            } else if (midiRoutersFilter.canConvert<FilterToConsole*>()) {
                auto filter = midiRoutersFilter.value<FilterToConsole*>();
                filterObj["filterType"] = static_cast<int>(filter->filterType());
                filterObj["logTo"] = static_cast<int>(filter->logTo());
                filterObj["userdata"] = filter->userdata();

                ary.append(filterObj);
            } else if (midiRoutersFilter.canConvert<FilterSchedule*>()) {
                auto filter = midiRoutersFilter.value<FilterSchedule*>();
                filterObj["filterType"] = static_cast<int>(filter->filterType());
                filterObj["defferedType"] = static_cast<int>(filter->defferedType());
                filterObj["defferedTo"] = static_cast<int>(filter->defferedTo());

                ary.append(filterObj);
            } else if (midiRoutersFilter.canConvert<FilterNetworkDestination*>()) {
                auto filter = midiRoutersFilter.value<FilterNetworkDestination*>();
                filterObj["filterType"] = static_cast<int>(filter->filterType());
                filterObj["serverName"] = filter->serverName();
                filterObj["serverPort"] = filter->serverPort();
                filterObj["baseMidiRouteInput"]= getBaseMidiRouteInput(filter->baseMidiRouteInput());

                ary.append(filterObj);
            } else if (midiRoutersFilter.canConvert<FilterAndTransform*>()) {
                auto filter = midiRoutersFilter.value<FilterAndTransform*>();
                filterObj["filterType"] = static_cast<int>(filter->filterType());
                filterObj["name"] = filter->name();
                filterObj["conditionAction"] = static_cast<int>(filter->conditionAction());
                filterObj["filterChannel"] = filter->filterChannel();
                filterObj["filterEvents"] = filter->filterEvents();
                filterObj["filterData1"] = filter->filterData1();
                filterObj["filterData2"] = filter->filterData2();

                ary.append(filterObj);
            }
        }
        return ary;
    }

    //- {function} 0 1
    QJsonObject getMidiRouteInput(MidiRouteInput *midiRouteInput)
    //-only-file body
    {
        QJsonObject obj;
        obj["midiInputName"] = midiRouteInput->midiInputName();
        obj["ignoreTypes"] = getIgnoreTypes(midiRouteInput);
        obj["midiRouteClock"] = getMidiRouteClock(midiRouteInput);
        obj["cc14bitAry"] = getCc14bitAry(midiRouteInput);
        obj["monitor"] = getMonitor(midiRouteInput);

        obj["midiRouterChains"] = getMidiRouterChains(midiRouteInput);

        return obj;
    }

    //- {function} 0 1
    QJsonArray getUserControls(QList<UserControl *> userControls)
    //-only-file body
    {
        QJsonArray ary;
        for (const auto &userControl: userControls){
            QJsonObject userControlObj;
            userControlObj["eventType"] = static_cast<int>(userControl->eventType());
            userControlObj["description"] = userControl->description();
            userControlObj["inputVal"] = userControl->inputVal();
            userControlObj["minVal"] = userControl->minVal();
            userControlObj["maxVal"] = userControl->maxVal();
            userControlObj["is64Mode"] = userControl->is64Mode();
            userControlObj["isEditMode"] = userControl->isEditMode();
            userControlObj["channelId"] = userControl->channelId();
            userControlObj["ccId"] = userControl->ccId();
            userControlObj["nrpnControl"] = userControl->nrpnControl();
            userControlObj["outputPortnName"] = userControl->outputPortnName();
            userControlObj["isShowDropdown"] = userControl->isShowDropdown();
            userControlObj["dropdownListId"] = userControl->dropdownListId();
            ary.append(userControlObj);

        }
        return ary;
    }


    //- {function} 0 1
    QList<MidiPresetControlEasyConfig> getMidiPresetControlEasyConfigs(UserDataConfig *userDataConfig)
    //-only-file body
    {
        QList<MidiPresetControlEasyConfig> midiPresetControlEasyConfigs;
        for (const auto &itm: userDataConfig->midiRoutePresets()){
            MidiPresetControlEasyConfig m;
            if (itm->isEnabled()){
                m.pmc = itm->midiControlOff();
                m.isMidiControlOn = false;
                midiPresetControlEasyConfigs.append(m);
            } else {
                m.pmc = itm->midiControlOn();
                m.isMidiControlOn = true;
                midiPresetControlEasyConfigs.append(m);
            }
        }
        return midiPresetControlEasyConfigs;
    }

    //-only-file header
};
