#line 16 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigGenJson.hpp"
#include "UserConfigGenJson.h"
#include "GenHpp/MidiPresetControlEasyConfig.h"
#include "FilterMidiDestination.h"
#include "FilterNetworkDestination.h"
    QJsonObject UserConfigGenJson::getJson( int activePresetID, QList<Dropdownlist *> dropdownlists, QList<QString> virtualInPorts, QList<MidiRoutePreset *> midiRoutePresets) 
#line 36 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigGenJson.hpp"
    {
        QJsonObject objUserConfig;
        objUserConfig["_activePresetID"] = activePresetID;
        objUserConfig["dropdownlists"]= getDropdownList(dropdownlists);
        objUserConfig["virtualInPorts"] = getListToJsonAry(virtualInPorts);
        objUserConfig["midiRoutePresets"] = getMidiRoutePresets(midiRoutePresets);

        return objUserConfig;
    }

    QJsonArray UserConfigGenJson::getDropdownList(QList<Dropdownlist *> dropdownlists) 
#line 52 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigGenJson.hpp"
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

    QJsonArray UserConfigGenJson::getListToJsonAry(const QStringList &sl) 
#line 66 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigGenJson.hpp"
    {
        QJsonArray ary;
        for (const auto &itm: sl){
            ary.append(itm);
        }
        return ary;
    }

    QJsonArray UserConfigGenJson::getListToJMidiInsonAry(const QStringList &sl) 
#line 77 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigGenJson.hpp"
    {
        QJsonArray ary;
        for (const auto &itm: sl){
            QJsonObject obj;
            obj["midiInputName"] = itm;
            ary.append(obj);
        }
        return ary;
    }

    QJsonArray UserConfigGenJson::getMidiRoutePresets(QList<MidiRoutePreset *> midiRoutePresets) 
#line 90 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigGenJson.hpp"
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

    QJsonObject UserConfigGenJson::getEasyConfig(EasyConfig *  easyConfig) 
#line 121 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigGenJson.hpp"
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

    QJsonArray UserConfigGenJson::getEasyConfigRoutes(QList<EasyConfigRoute *> easyConfigRoutes) 
#line 142 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigGenJson.hpp"
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

    QJsonArray UserConfigGenJson::getStringListToJsonAry(QStringList list ) 
#line 170 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigGenJson.hpp"
    {
        QJsonArray ary;
        for (const auto &str: list){
            ary.append(str);
        }
        return ary;
    }

    QJsonArray UserConfigGenJson::getKeyboardSplits(QList<int> keyboardSplits) 
#line 181 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigGenJson.hpp"
    {
        QJsonArray ary;
        for (const auto &keyboardSplit: keyboardSplits){
            QJsonObject obj;
            obj["splitPosition"] = keyboardSplit;
            ary.append(obj);
        }
        return ary;
    }

    QJsonObject UserConfigGenJson::getModiControlOnOff(PresetMidiControl * presetMidiControl) 
#line 194 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigGenJson.hpp"
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

    QJsonObject UserConfigGenJson::getMidiRouteInputs(QList<MidiRouteInput *> midiRouteInputs) 
#line 209 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigGenJson.hpp"
    {
        QJsonObject obj;
        for (const auto &itm: midiRouteInputs){
            obj[itm->midiInputName()] = getMidiRouteInput(itm);
        }
        return obj;
    }

    QJsonArray UserConfigGenJson::getCc14bitAry(MidiRouteInput * midiRouteInput) 
#line 220 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigGenJson.hpp"
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

    QJsonObject UserConfigGenJson::getMidiRouteClock(MidiRouteInput * midiRouteInput) 
#line 235 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigGenJson.hpp"
    {
        QJsonObject midiRouteClock;
        midiRouteClock["timeSig"] = midiRouteInput->midiRouteClockTimeSig();
        midiRouteClock["timeSigDivBy"] = midiRouteInput->midiRouteClockTimeSigDivBy();
        midiRouteClock["fromSppPos"] = midiRouteInput->midiRouteClockFromSppPos();
        midiRouteClock["propegateInputs"] = getListToJMidiInsonAry(midiRouteInput->midiRouteClockPropegateInputs());

        return midiRouteClock;
    }

    QJsonObject UserConfigGenJson::getIgnoreTypes(MidiRouteInput * midiRouteInput) 
#line 248 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigGenJson.hpp"
    {
        QJsonObject ignoreTypes;
        ignoreTypes["midiSysex"] = midiRouteInput->ignoreTypesMidiSysex();
        ignoreTypes["midiTime"] = midiRouteInput->ignoreTypesMidiTime();
        ignoreTypes["midiSense"] = midiRouteInput->ignoreTypesMidiSense();

        return ignoreTypes;
    }

    QJsonObject UserConfigGenJson::getMonitor(MidiRouteInput * midiRouteInput) 
#line 260 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigGenJson.hpp"
    {
        QJsonObject monitor;
        monitor["isMonitored"] = midiRouteInput->monitor()->isMonitored();
        return monitor;
    }

    QJsonArray UserConfigGenJson::getMidiRouterChains(MidiRouteInput * midiRouteInput) 
#line 269 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigGenJson.hpp"
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

    QJsonObject UserConfigGenJson::getBaseMidiRouteInput(QString strMidiInputName) 
#line 286 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigGenJson.hpp"
    {
        QJsonObject obj;
        obj["midiInputName"] = strMidiInputName;
        return obj;
    }

    QJsonArray UserConfigGenJson::getMidiRoutersFilters(QList<QVariant> midiRoutersFilters) 
#line 295 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigGenJson.hpp"
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

    QJsonObject UserConfigGenJson::getMidiRouteInput(MidiRouteInput * midiRouteInput) 
#line 345 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigGenJson.hpp"
    {
        QJsonObject obj;
        obj["midiInputName"] = midiRouteInput->midiInputName();
        obj["ignoreTypes"] = getIgnoreTypes(midiRouteInput);
        obj["midiRouteClock"] = getMidiRouteClock(midiRouteInput);
        obj["cc14bitAry"] = getCc14bitAry(midiRouteInput);
        obj["monitor"] = getMonitor(midiRouteInput);
        obj["easyConfig"] = getEasyConfig(midiRouteInput->easyConfig());

        obj["midiRouterChains"] = getMidiRouterChains(midiRouteInput);

        return obj;
    }

    QJsonArray UserConfigGenJson::getUserControls(QList<UserControl *> userControls) 
#line 362 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigGenJson.hpp"
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


    QList<MidiPresetControlEasyConfig> UserConfigGenJson::getMidiPresetControlEasyConfigs(QList<MidiRoutePreset *> midiRoutePresets) 
#line 389 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigGenJson.hpp"
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

