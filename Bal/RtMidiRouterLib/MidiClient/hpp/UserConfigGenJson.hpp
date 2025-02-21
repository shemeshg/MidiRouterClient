//-define-file body GenHpp/UserConfigGenJson.cpp
//-define-file header GenHpp/UserConfigGenJson.h
//-only-file header //-
#pragma once
#include <QJsonValue>
#include <QtCore/qjsonarray.h>
#include <QtCore/qjsondocument.h>
#include <QtCore/qjsonobject.h>
//- #include "../genPrpt/Dropdownlist.h"
//- #include "MidiRoutePreset.h"

//-only-file null
#include "MidiRoutePreset.hpp"
#include "../genPrpt/Dropdownlist.hpp"
//-only-file body //-
//- #include "UserConfigGenJson.h"
//- #include "GenHpp/MidiPresetControlEasyConfig.h"
//- #include "FilterMidiDestination.h"
//- #include "FilterNetworkDestination.h"
//-only-file header


//-var {PRE} "UserConfigGenJson::"
class UserConfigGenJson
{
public:    
    UserConfigGenJson(){}

    //- {fn}
    QJsonObject getJson(
                        QString uniqueId,
                        int activePresetID,
                        QList<Dropdownlist *> dropdownlists,
                        QList<QString> virtualInPorts,
                        QList<MidiRoutePreset *> midiRoutePresets)
    //-only-file body
    {
        QJsonObject objUserConfig;
        objUserConfig["uniqueId"] = uniqueId;
        objUserConfig["_activePresetID"] = activePresetID;
        objUserConfig["dropdownlists"]= getDropdownList(dropdownlists);
        objUserConfig["virtualInPorts"] = getListToJsonAry(virtualInPorts);
        objUserConfig["midiRoutePresets"] = getMidiRoutePresets(midiRoutePresets);

        return objUserConfig;
    }

    //-only-file header
private:

    //- {fn}
    QJsonArray getDropdownList(QList<Dropdownlist *> dropdownlists)
    //-only-file body
    {
        QJsonArray ary;
        for (const auto itm: dropdownlists){
            QJsonObject obj;
            obj["name"] = itm->name();
            obj["data"] = itm->data();
            ary.append(obj);
        }
        return ary;
    }

    //- {fn}
    QJsonArray getListToJsonAry(const QStringList &sl)
    //-only-file body
    {
        QJsonArray ary;
        for (const auto &itm: sl){
            ary.append(itm);
        }
        return ary;
    }

    //- {fn}
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

    //- {fn}
    QJsonArray getMidiRoutePresets(QList<MidiRoutePreset *> midiRoutePresets)
    //-only-file body
    {


        QJsonArray ary;
        for (const auto &itm: midiRoutePresets){
            QJsonObject obj;
            auto presetControlEasyConfigs = getMidiPresetControlEasyConfigs( midiRoutePresets);
            itm->recreateEasyConfig(presetControlEasyConfigs);
            obj["name"] = itm->name();
            obj["uuid"] = itm->uuid();
            obj["isEnabled"] = itm->isEnabled();
            obj["isSendAllUserControls"] = itm->isSendAllUserControls();
            obj["midiControlOn"] = getModiControlOnOff(itm->midiControlOn());
            obj["midiControlOff"] = getModiControlOnOff(itm->midiControlOff());
            obj["midiRouteInputs"] = getMidiRouteInputs(itm->midiRouteInputs());
            obj["userControls"] = getUserControls(itm->userControls());

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

    //- {fn}
    QJsonObject getEasyConfig(EasyConfig * easyConfig)
    //-only-file body
    {
        QJsonObject obj;
        //auto inputZonesAndRoutes = obj["inputZonesAndRoutes"].toObject();

        QJsonArray inputZonesAndRoutes;


        QJsonObject  easyConfigInput;
        easyConfigInput["keyboardSplits"] = getKeyboardSplits(easyConfig->keyboardSplits());
        easyConfigInput["zoneNames"] = getStringListToJsonAry(easyConfig->zoneNames());
        easyConfigInput["easyConfigRoutes"] = getEasyConfigRoutes(easyConfig->easyConfigRoutes());

        inputZonesAndRoutes.append(easyConfigInput);

        obj["inputZonesAndRoutes"] = inputZonesAndRoutes;
        return obj;
    }

    //- {fn}
    QJsonArray getEasyConfigRoutes(QList<EasyConfigRoute *> easyConfigRoutes)
    //-only-file body
    {
        QJsonArray ary;
        for (const auto &easyConfigRoute: easyConfigRoutes){
            QJsonObject obj;

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

    //- {fn}
    QJsonArray getStringListToJsonAry(QStringList list )
    //-only-file body
    {
        QJsonArray ary;
        for (const auto &str: list){
            ary.append(str);
        }
        return ary;
    }

    //- {fn}
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

    //- {fn}
    QJsonObject getModiControlOnOff(PresetMidiControl *presetMidiControl)
    //-only-file body
    {
        QJsonObject obj;
        obj["presetMidiType"] = static_cast<int>(presetMidiControl->presetMidiType());
        obj["portName"] = presetMidiControl->portName();
        obj["eventTypeId"] = presetMidiControl->eventTypeId();
        obj["channel"] = presetMidiControl->channel();
        obj["data1"] = presetMidiControl->data1();
        obj["data2"] = presetMidiControl->data2();
        return obj;
    }

    //- {fn}
    QJsonArray getMidiRouteInputs(QList<MidiRouteInput *> midiRouteInputs)
    //-only-file body
    {
        QJsonArray obj;
        for (const auto &itm: midiRouteInputs){
            obj.append( getMidiRouteInput(itm));
        }
        return obj;
    }

    //- {fn}
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

    //- {fn}
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

    //- {fn}
    QJsonObject getIgnoreTypes(MidiRouteInput *midiRouteInput)
    //-only-file body
    {
        QJsonObject ignoreTypes;
        ignoreTypes["midiSysex"] = midiRouteInput->ignoreTypesMidiSysex();
        ignoreTypes["midiTime"] = midiRouteInput->ignoreTypesMidiTime();
        ignoreTypes["midiSense"] = midiRouteInput->ignoreTypesMidiSense();

        return ignoreTypes;
    }

    //- {fn}
    QJsonObject getMonitor(MidiRouteInput *midiRouteInput)
    //-only-file body
    {
        QJsonObject monitor;
        monitor["isMonitored"] = midiRouteInput->monitor()->isMonitored();
        return monitor;
    }

    //- {fn}
    QJsonArray getMidiRouterChains(MidiRouteInput *midiRouteInput)
    //-only-file body
    {
        QJsonArray midiRouterChains;
        for (const auto midiRouterChain: midiRouteInput->midiRouterChains()){
            QJsonObject midiRouterChainObj;
            midiRouterChainObj["uuid"] = midiRouteInput->uuid();
            midiRouterChainObj["name"] = midiRouterChain->name();
            midiRouterChainObj["isEasyConfig"] = midiRouterChain->isEasyConfig();
            midiRouterChainObj["isRunForPresetOnAndOff"] = midiRouterChain->isRunForPresetOnAndOff();
            midiRouterChainObj["midiRoutersFilters"] = getMidiRoutersFilters(midiRouterChain->midiRoutersFilters());
            midiRouterChains.append(midiRouterChainObj);
        }

        return midiRouterChains;
    }

    //- {fn}
    QJsonObject getBaseMidiRouteInput(QString strMidiInputName)
    //-only-file body
    {
        QJsonObject obj;
        obj["midiInputName"] = strMidiInputName;
        return obj;
    }

    //- {fn}
    QJsonArray getMidiRoutersFilters(QList<QVariant> midiRoutersFilters)
    //-only-file body
    {
        QJsonArray ary;
        for (const auto &midiRoutersFilter: midiRoutersFilters ){
            QJsonObject filterObj;

            if (midiRoutersFilter.canConvert<FilterMidiDestination*>()) {
                auto filter = midiRoutersFilter.value<FilterMidiDestination*>();
                filterObj["uuid"] = filter->uuid();
                filterObj["filterType"] = static_cast<int>(filter->filterType());
                filterObj["baseMidiRouteInput"]= getBaseMidiRouteInput(filter->baseMidiRouteInput());
                ary.append(filterObj);
            } else if (midiRoutersFilter.canConvert<FilterToConsole*>()) {
                auto filter = midiRoutersFilter.value<FilterToConsole*>();
                filterObj["uuid"] = filter->uuid();
                filterObj["filterType"] = static_cast<int>(filter->filterType());
                filterObj["logTo"] = static_cast<int>(filter->logTo());
                filterObj["userdata"] = filter->userdata();

                ary.append(filterObj);
            } else if (midiRoutersFilter.canConvert<FilterSchedule*>()) {                
                auto filter = midiRoutersFilter.value<FilterSchedule*>();
                filterObj["uuid"] = filter->uuid();
                filterObj["filterType"] = static_cast<int>(filter->filterType());
                filterObj["defferedType"] = static_cast<int>(filter->defferedType());
                filterObj["defferedTo"] = static_cast<int>(filter->defferedTo());

                ary.append(filterObj);
            } else if (midiRoutersFilter.canConvert<FilterNetworkDestination*>()) {
                auto filter = midiRoutersFilter.value<FilterNetworkDestination*>();
                filterObj["uuid"] = filter->uuid();
                filterObj["filterType"] = static_cast<int>(filter->filterType());
                filterObj["serverName"] = filter->serverName();
                filterObj["serverPort"] = filter->serverPort();
                filterObj["baseMidiRouteInput"]= getBaseMidiRouteInput(filter->baseMidiRouteInput());

                ary.append(filterObj);
            } else if (midiRoutersFilter.canConvert<FilterAndTransform*>()) {
                auto filter = midiRoutersFilter.value<FilterAndTransform*>();
                filterObj["uuid"] = filter->uuid();
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

    //- {fn}
    QJsonObject getMidiRouteInput(MidiRouteInput *midiRouteInput)
    //-only-file body
    {
        QJsonObject obj;
        obj["uuid"] = midiRouteInput->uuid();
        obj["midiInputName"] = midiRouteInput->midiInputName();
        obj["ignoreTypes"] = getIgnoreTypes(midiRouteInput);
        obj["midiRouteClock"] = getMidiRouteClock(midiRouteInput);
        obj["cc14bitAry"] = getCc14bitAry(midiRouteInput);
        obj["monitor"] = getMonitor(midiRouteInput);
        obj["easyConfig"] = getEasyConfig(midiRouteInput->easyConfig());

        obj["midiRouterChains"] = getMidiRouterChains(midiRouteInput);

        return obj;
    }

    //- {fn}
    QJsonArray getUserControls(QList<UserControl *> userControls)
    //-only-file body
    {
        QJsonArray ary;
        for (const auto &userControl: userControls){
            QJsonObject userControlObj;
            userControlObj["uuid"] = userControl->uuid();
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


    //- {fn}
    QList<MidiPresetControlEasyConfig> getMidiPresetControlEasyConfigs(QList<MidiRoutePreset *> midiRoutePresets)
    //-only-file body
    {
        QList<MidiPresetControlEasyConfig> midiPresetControlEasyConfigs;
        for (const auto &itm: midiRoutePresets){
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
