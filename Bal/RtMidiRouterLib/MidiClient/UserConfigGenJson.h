#ifndef USERCONFIGGENJSON_H
#define USERCONFIGGENJSON_H

#include "UserDataConfig.h"

#include <QtCore/qjsonobject.h>
class UserConfigGenJson
{
public:
    UserConfigGenJson(){}


    QJsonObject getJson(UserDataConfig *userDataConfig){
        QJsonObject objUserConfig;
        objUserConfig["_activePresetID"] = userDataConfig->activePresetID();
        objUserConfig["dropdownlists"]= getDropdownList(userDataConfig);
        objUserConfig["virtualInPorts"] = getListToJsonAry(userDataConfig->virtualInPorts());
        objUserConfig["midiRoutePresets"] = getMidiRoutePresets(userDataConfig);


        return objUserConfig;
    }

private:
    QJsonArray getDropdownList(UserDataConfig *userDataConfig)
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

    QJsonArray getListToJsonAry(const QStringList &sl){
        QJsonArray ary;
        for (const auto &itm: sl){
            ary.append(itm);
        }
        return ary;
    }

    QJsonArray getListToJMidiInsonAry(const QStringList &sl){
        QJsonArray ary;
        for (const auto &itm: sl){
            QJsonObject obj;
            obj["midiInputName"] = itm;
            ary.append(obj);
        }
        return ary;
    }

    QJsonArray getMidiRoutePresets(UserDataConfig *userDataConfig){
        QJsonArray ary;
        int i=0;
        for (const auto &itm: userDataConfig->midiRoutePresets()){
            QJsonObject obj;
            obj["name"] = itm->name();
            obj["uuid"] = itm->uuid();
            obj["isEnabled"] = (i == userDataConfig->activePresetID());
            obj["isSendAllUserControls"] = itm->isSendAllUserControls();
            obj["midiControlOn"] = getModiControlOnOff(itm->midiControlOn());
            obj["midiControlOff"] = getModiControlOnOff(itm->midiControlOff());
            obj["midiRouteInputs"] = getMidiRouteInputs(itm->midiRouteInputs());
            obj["userControls"] = getUserControls(itm->userControls());
            i++;
        }
        return ary;
    }

    QJsonObject getModiControlOnOff(PresetMidiControl *presetMidiControl){
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
    QJsonObject getMidiRouteInputs(QList<MidiRouteInput *> midiRouteInputs){
        QJsonObject obj;
        for (const auto &itm: midiRouteInputs){
            obj[itm->midiInputName()] = getMidiRouteInput(itm);
        }
        return obj;
    }

    QJsonArray getCc14bitAry(MidiRouteInput *midiRouteInput)
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

    QJsonObject getMidiRouteClock(MidiRouteInput *midiRouteInput)
    {
        QJsonObject midiRouteClock;
        midiRouteClock["timeSig"] = midiRouteInput->midiRouteClockTimeSig();
        midiRouteClock["timeSigDivBy"] = midiRouteInput->midiRouteClockTimeSigDivBy();
        midiRouteClock["fromSppPos"] = midiRouteInput->midiRouteClockFromSppPos();
        midiRouteClock["propegateInputs"] = getListToJMidiInsonAry(midiRouteInput->midiRouteClockPropegateInputs());

        return midiRouteClock;
    }

    QJsonObject getIgnoreTypes(MidiRouteInput *midiRouteInput)
    {
        QJsonObject ignoreTypes;
        ignoreTypes["midiSysex"] = midiRouteInput->ignoreTypesMidiSysex();
        ignoreTypes["midiTime"] = midiRouteInput->ignoreTypesMidiTime();
        ignoreTypes["midiSense"] = midiRouteInput->ignoreTypesMidiSense();

        return ignoreTypes;
    }

    QJsonArray getMidiRouterChains(MidiRouteInput *midiRouteInput)
    {
        QJsonArray midiRouterChains;
        for (const auto midiRouterChain: midiRouteInput->midiRouterChains()){
            QJsonObject midiRouterChainObj;
            midiRouterChainObj["name"] = midiRouterChain->name();
            midiRouterChainObj["isEasyConfig"] = midiRouterChain->isEasyConfig();
            midiRouterChainObj["midiRoutersFilters"] = getMidiRoutersFilters(midiRouterChain->midiRoutersFilters());
            midiRouterChains.append(midiRouterChainObj);
        }

        return midiRouterChains;
    }

    QJsonObject getBaseMidiRouteInput(QString strMidiInputName){
        QJsonObject obj, midiInputName;
        midiInputName["midiInputName"] = strMidiInputName;
        obj["baseMidiRouteInput"] = midiInputName;
        return obj;
    }

    QJsonArray getMidiRoutersFilters(QList<QVariant> midiRoutersFilters){
        QJsonArray ary;
        for (const auto &midiRoutersFilter: midiRoutersFilters ){
            QJsonObject filterObj;
            if (midiRoutersFilter.canConvert<FilterMidiDestination*>()) {
                auto filter = midiRoutersFilter.value<FilterMidiDestination*>();
                filterObj["filterType"] = static_cast<int>(filter->filterType());
                filterObj["baseMidiRouteInput"]= getBaseMidiRouteInput(filter->name());
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
                filterObj["baseMidiRouteInput"]= getBaseMidiRouteInput(filter->name());

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

    QJsonValue getMidiRouteInput(MidiRouteInput *midiRouteInput){
        QJsonObject obj;
        obj["midiInputName"] = midiRouteInput->midiInputName();
        obj["ignoreTypes"] = getIgnoreTypes(midiRouteInput);
        obj["midiRouteClock"] = getMidiRouteClock(midiRouteInput);
        obj["cc14bitAry"] = getCc14bitAry(midiRouteInput);


        obj["midiRouterChains"] = getMidiRouterChains(midiRouteInput);

        return obj;
    }

    QJsonArray getUserControls(QList<UserControl *> userControls) {
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
};

#endif // USERCONFIGGENJSON_H
