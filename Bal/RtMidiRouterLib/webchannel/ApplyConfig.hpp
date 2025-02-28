//-define-file body webchannel/ApplyConfig.cpp
//-define-file header webchannel/ApplyConfig.h
//-only-file header //-
#pragma once
#include "wcmidiin.h"
#include "wcmidiout.h"
#include <QJsonValueRef>
#include <QJsonObject>
#include <QJsonArray>
//-only-file body //-
//- #include "ApplyConfig.h"

//-only-file header
//-var {PRE} "ApplyConfig::"
class ApplyConfig {
public:
    explicit ApplyConfig(Webchannel::WcMidiIn *wcmidiin,
                         Webchannel::WcMidiOut *wcmidiout)
        : wcmidiin{wcmidiin}, wcmidiout{wcmidiout} {}

    struct DisCnctInPort {
        QString presetUuid;
        QString inPortName;
    };

    struct DisCnctOutPort {
        QString presetUuid;
        QString outPortName;
        QString originedInPort;
    };

    //- {fn}
    QJsonObject presetOnOff(QJsonObject &json, bool isMidiControlOn,
                            const QString &presetUuid)
    //-only-file body
    {
        auto midiRoutePresets = getJson<QJsonArray>(json["midiRoutePresets"]);

        for (int i = 0; i < midiRoutePresets.size(); ++i) {
            auto midiRoutePresetObj = getJson<QJsonObject>(midiRoutePresets[i]);
            if (getJson<QString>(midiRoutePresetObj["uuid"]) == presetUuid) {
                midiRoutePresetObj["isEnabled"] = isMidiControlOn;
                midiRoutePresets[i] =
                    midiRoutePresetObj; // Update the array with the modified object
            }
        }

        json["midiRoutePresets"] =
            midiRoutePresets; // Update the JSON object with the modified array
        return json;
    }

    //- {fn}
    QJsonObject applyConfig(QJsonObject &json)
    //-only-file body
    {
        wcmidiin->restart();
        wcmidiout->restart();

        QVariantMap inPortsMap = wcmidiin->getPorts();
        QVariantMap outPortMap = wcmidiout->getPorts();

        setVirtualPorts(inPortsMap, json);

        inPorts = getMapStringVal(wcmidiin->getPorts());
        outPorts = getMapStringVal(wcmidiout->getPorts());
        disCnctInPorts.clear();
        disCnctOutPorts.clear();

        setMidiRoutePresets(json);

        return createApplayConfigReturnObj();
    }

    //-only-file header
private:
    Webchannel::WcMidiIn *wcmidiin;
    Webchannel::WcMidiOut *wcmidiout;

    QStringList inPorts;
    QStringList outPorts;
    QList<DisCnctInPort> disCnctInPorts;
    QList<DisCnctOutPort> disCnctOutPorts;

    enum class FilterType {
        TO_MIDI_DESTINATION,
        TO_CONSOLE,
        TO_NETWORK,
        SCHEDULE_TO,
        FILTER_AND_TRANSFORM
    };

    //- {fn}
    QStringList getMapStringVal(QVariantMap map)
    //-only-file body
    {
        QStringList list;
        for (auto it = map.begin(); it != map.end(); ++it) {
            list.append(it.value().toString());
        }
        return list;
    }

    //- {fn}
    QStringList getInHwPortNames(const QVariantMap &inPortsMap)
    //-only-file body
    {
        QStringList inHwPortNames;
        for (auto it = inPortsMap.begin(); it != inPortsMap.end(); ++it) {
            QString val = it.value().toString();
            inHwPortNames.append(val.mid(val.indexOf("_") + 1));
        }

        return inHwPortNames;
    }

    //- {fn}
    void setVirtualPorts(const QVariantMap &inPortsMap, QJsonObject &json)
    //-only-file body
    {
        QStringList inHwPortNames = getInHwPortNames(inPortsMap);

        if (!json["virtualInPorts"].isArray()){return;}
        auto virtualInPorts = getJson<QJsonArray>(json["virtualInPorts"]);

        for (const auto &itm : virtualInPorts) {
            QString str = itm.toString();
            if (!inHwPortNames.contains(str)) {
                wcmidiin->openVirtualInOutPort(str);
            }
        }
    }

    //- {fn}
    void setMidiRoutePresets(QJsonObject &json)
    //-only-file body
    {
        if (!json["midiRoutePresets"].isArray()){return;}
        auto midiRoutePresetsObj = getJson<QJsonArray>(json["midiRoutePresets"]);

        for (auto const &midiRoutePreset : midiRoutePresetsObj) {
            auto midiRoutePresetObj = getJson<QJsonObject>(midiRoutePreset);
            bool isEnabled = midiRoutePresetObj["isEnabled"].toBool();
            setMidiRouteInputs(midiRoutePresetObj, isEnabled);
            // send user control if required
            if (isEnabled) {
                auto userControlsObj = getJson<QJsonArray>(midiRoutePresetObj["userControls"]);
                for (const auto &ctrl : userControlsObj) {
                    auto ctrlObj = ctrl.toObject();
                    if (getJson<bool>(ctrlObj["isSendOnPresetChange"])) {
                        QString outputPortnName = getJson<QString>(ctrlObj["outputPortnName"]);
                        if (outputPortnName.isEmpty()) {
                            continue;
                        }
                        int portNumber = wcmidiout->getPortNumber(outputPortnName);
                        if (portNumber == -1) {
                            continue;
                        }
                        wcmidiout->openPort(portNumber);
                        int eventType = getJson<int>(ctrlObj["eventType"]);
                        if (eventType == 0) {

                            wcmidiout->sendControlChange(portNumber,
                                                         getJson<int>(ctrlObj["ccId"]),
                                                         getJson<int>(ctrlObj["inputVal"]),
                                                         {getJson<QString>(ctrlObj["channelId"])});
                        } else if (eventType == 1) {
                            wcmidiout->sendProgramChange(portNumber,
                                                         getJson<int>(ctrlObj["inputVal"]),
                                                         {getJson<QString>(ctrlObj["channelId"])});
                        } else if (eventType == 2) {
                            wcmidiout->setNonRegisteredParameterInt(
                                portNumber,
                                getJson<int>(ctrlObj["nrpnControl"]),
                                getJson<int>(ctrlObj["inputVal"]),
                                {getJson<QString>(ctrlObj["channelId"])});
                        } else {
                            throw std::runtime_error("Unexpected JSON format");
                        }


                    }
                }
            }
        }
    }

    //- {fn}
    bool getBoolIgnoreTypes(QJsonObject &midiRouteInputObj, QString name)
    //-only-file body
    {
        auto obj = getJson<QJsonObject>(midiRouteInputObj["ignoreTypes"]);
        return getJson<bool>(obj[name]);
    }

    //- {fn}
    double getDoubleTimeSig(QJsonObject &midiRouteInputObj, QString name)
    //-only-file body
    {
        auto obj = getJson<QJsonObject>(midiRouteInputObj["midiRouteClock"]);
        return getJson<double>(obj[name]);
    }

    //- {fn}
    void setMidiRouteInputs(QJsonObject &midiRoutePresetObj, bool isEnabled)
    //-only-file body
    {

        auto midiRouteInputsObj = getJson<QJsonArray>(midiRoutePresetObj["midiRouteInputs"]);

        for (auto it = midiRouteInputsObj.begin(); it != midiRouteInputsObj.end();
             ++it) {
            auto midiRouteInputObj = it->toObject();
            auto midiInputName = getJson<QString>( midiRouteInputObj["midiInputName"]);

            QString presetUuid = getJson<QString>(midiRoutePresetObj["uuid"]);
            if (inPorts.contains(midiInputName)) {
                setInportSettings(midiRouteInputObj, midiInputName, isEnabled,
                                  presetUuid);
            } else if (!std::any_of(disCnctInPorts.begin(), disCnctInPorts.end(),
                                    [&midiInputName](const DisCnctInPort &port) {
                                        return port.inPortName == midiInputName;
                       })) {
                DisCnctInPort port;
                port.presetUuid = presetUuid;
                port.inPortName = midiInputName;
                disCnctInPorts.append(port);
            }
        }

    }

    //- {fn}
    void setInputPortParams(int portNumber, QJsonObject &midiRouteInputObj,
                            QString &midiInputName, QString presetUuid)
    //-only-file body
    {
        wcmidiin->ignoreTypes(portNumber,
                              getBoolIgnoreTypes(midiRouteInputObj, "midiSysex"),
                              getBoolIgnoreTypes(midiRouteInputObj, "midiTime"),
                              getBoolIgnoreTypes(midiRouteInputObj, "midiSense"));

        wcmidiin->setTimeSig(portNumber,
                             getDoubleTimeSig(midiRouteInputObj, "timeSig"),
                             getDoubleTimeSig(midiRouteInputObj, "timeSigDivBy"),
                             getDoubleTimeSig(midiRouteInputObj, "fromSppPos"));

        wcmidiin->clearPropegateClockPort(portNumber);

        auto midiRouteClockObj = getJson<QJsonObject>(midiRouteInputObj["midiRouteClock"]);
        auto propegateInputsAry = getJson<QJsonArray>(midiRouteClockObj["propegateInputs"]);
        for (const auto &propegateInput : propegateInputsAry) {
            auto propegateInputObj = getJson<QJsonObject>(propegateInput);
            auto outPortName = getJson<QString>(propegateInputObj["midiInputName"]);
            if (outPorts.contains(outPortName)) {
                int outPortId = wcmidiout->getPortNumber(outPortName);
                wcmidiin->addPropegateClockPort(portNumber, outPortId);
            } else {
                DisCnctOutPort port;
                port.presetUuid = presetUuid;
                port.originedInPort = midiInputName;
                port.outPortName = outPortName;
                disCnctOutPorts.append(port);
            }
        }

        auto cc14bitAry = getJson<QJsonArray>(midiRouteInputObj["cc14bitAry"]);
        wcmidiin->clearCc14Bit(portNumber);
        for (const auto &cc14 : cc14bitAry) {
            auto cc14Obj = getJson<QJsonObject>(cc14);
            wcmidiin->addCc14Bit(portNumber,
                                 getJson<int>( cc14Obj["channel"]),
                                 getJson<int>(cc14Obj["cc"]));
        }
    }

    //- {fn}
    QJsonArray stringToJsonArray(const QString &qString)
    //-only-file body
    {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(qString.toUtf8());
        QJsonArray jsonArray;
        if (jsonDoc.isNull() || !jsonDoc.isArray()) {
            return jsonArray;
        }
        jsonArray = jsonDoc.array();
        return jsonArray;
    }

    //- {fn}
    void setInputChainFilters(QString &midiInputName,
                              QJsonArray &midiRoutersFilters, int portNumber,
                              QJsonObject &midiRouterChainObj)
    //-only-file body
    {
        int chainId = wcmidiin->routingMidiChainsAaddChain(portNumber);
        for (const auto &midiRoutersFilter : midiRoutersFilters) {
            auto filter = getJson<QJsonObject>(midiRoutersFilter);
            if (getJson<int>(filter["filterType"]) ==
                static_cast<int>(FilterType::TO_MIDI_DESTINATION)) {
                int outPortNumber =
                    wcmidiout->getPortNumber(getJson<QString>(filter["midiInputName"]));


                if (outPortNumber >= 0) {
                    wcmidiin->routingActionAddSendPortByNumber(portNumber, chainId,
                                                               outPortNumber);
                } else {
                    qDebug() << "Could not find out port";
                }

            } else if (getJson<int>(filter["filterType"]) ==
                       static_cast<int>(FilterType::TO_CONSOLE)) {
                wcmidiin->routingActionAddLogData(portNumber, chainId,
                                                  getJson<int>(filter["logTo"]),
                                                  getJson<QString>(filter["userdata"]));
            } else if (getJson<int>(filter["filterType"]) ==
                       static_cast<int>(FilterType::SCHEDULE_TO)) {

                wcmidiin->routingActionAddDeferedEvent(portNumber, chainId,
                                                       getJson<int>(filter["defferedType"]),
                                                       getJson<double>(filter["defferedTo"]));
            } else if (getJson<int>(filter["filterType"]) ==
                       static_cast<int>(FilterType::TO_NETWORK)) {
                QString remotePortName = getJson<QString>(filter["midiInputName"]);
                auto ok = wcmidiin->routingActionAddSendRemoteServerByRemotePortName(
                    portNumber, chainId,
                    getJson<QString>(filter["serverName"]),
                    getJson<int>(filter["serverPort"]),
                    remotePortName);
                if (ok == -1) {
                    qDebug() << "Could not add remote Port for some reason";
                }
            } else if (getJson<int>(filter["filterType"]) ==
                       static_cast<int>(FilterType::FILTER_AND_TRANSFORM)) {
                wcmidiin->routingActionAddFilterMidiChannelMsg(
                    portNumber, chainId,
                    stringToJsonArray(getJson<QString>(filter["filterChannel"])),
                    stringToJsonArray(getJson<QString>(filter["filterEvents"])),
                    stringToJsonArray(getJson<QString>(filter["filterData1"])),
                    stringToJsonArray(getJson<QString>(filter["filterData2"])),
                    getJson<int>(filter["conditionAction"]));
            }
        }
    }

    //- {fn}
    void setInputRouterChains(bool isEnabled, int portNumber,
                              QJsonObject &midiRouteInputObj,
                              QString &midiInputName)
    //-only-file body
    {
        auto midiRouterChains = getJson<QJsonArray>( midiRouteInputObj["midiRouterChains"]);
        for (const auto &midiRouterChain : midiRouterChains) {

            //
            QJsonObject midiRouterChainObj = getJson<QJsonObject>(midiRouterChain);
            if (isEnabled || getJson<bool>(midiRouterChainObj["isRunForPresetOnAndOff"])) {
                QJsonArray midiRoutersFilters =
                    getJson<QJsonArray>( midiRouterChainObj["midiRoutersFilters"]);
                if (midiRoutersFilters.size() > 0) {
                    setInputChainFilters(midiInputName, midiRoutersFilters, portNumber,
                                         midiRouterChainObj);
                }
            }
        }
    }

    //- {fn}
    void setInportSettings(QJsonObject &midiRouteInputObj, QString &midiInputName,
                           bool isEnabled, QString presetUuid)
    //-only-file body
    {
        int portNumber = wcmidiin->getPortNumber(midiInputName);

        wcmidiin->openPort(portNumber);

        if (isEnabled) {
            setInputPortParams(portNumber, midiRouteInputObj, midiInputName,
                               presetUuid);
        }

        setInputRouterChains(isEnabled, portNumber, midiRouteInputObj,
                             midiInputName);
    }

    //- {fn}
    QJsonObject createApplayConfigReturnObj()
    //-only-file body
    {
        QJsonObject json;

        // Create JSON array for disCnctInPorts
        QJsonArray inPortsArray;
        for (const auto &inPort : disCnctInPorts) {
            QJsonObject inPortObj;
            inPortObj["presetUuid"] = inPort.presetUuid;
            inPortObj["inPortName"] = inPort.inPortName;
            inPortsArray.append(inPortObj);
        }
        json["disCnctInPorts"] = inPortsArray;

        // Create JSON array for disCnctOutPorts
        QJsonArray outPortsArray;
        for (const auto &outPort : disCnctOutPorts) {
            QJsonObject outPortObj;
            outPortObj["presetUuid"] = outPort.presetUuid;
            outPortObj["outPortName"] = outPort.outPortName;
            outPortObj["originedInPort"] = outPort.originedInPort;
            outPortsArray.append(outPortObj);
        }
        json["disCnctOutPorts"] = outPortsArray;

        return json;
    }

    //-only-file header
    template<typename T>
    T getJson(QJsonValueRef obj);



    template<>
    QJsonArray getJson(QJsonValueRef obj)
    {
        if (obj.isArray()){
            return obj.toArray();
        } else {
            QJsonArray tmp;
            qDebug()<<"Critical AppConfig json error";
            return tmp;
        }
    }


    template<>
    QJsonObject getJson(QJsonValueRef obj)
    {
        if (obj.isObject()){
            return obj.toObject();
        } else {
            QJsonObject tmp;
            qDebug()<<"Critical AppConfig json error";
            return tmp;
        }
    }


    template<>
    QString  getJson(QJsonValueRef obj)
    {
        if(obj.isString()){
            return obj.toString();
        } else {
            qDebug()<<"Critical AppConfig json error";
            return "";
        }
    }

    template<>
    bool  getJson(QJsonValueRef obj)
    {
        if(obj.isBool()){
            return obj.toBool();
        } else {
            qDebug()<<"Critical AppConfig json error";
            return false;
        }
    }

    template<>
    double  getJson(QJsonValueRef obj)
    {
        if(obj.isDouble()){
            return obj.toDouble();
        } else {
            qDebug()<<"Critical AppConfig json error";
            return 0;
        }
    }

    template<>
    int  getJson(QJsonValueRef obj)
    {
        if(obj.isDouble()){
            return obj.toDouble();
        } else {
            qDebug()<<"Critical AppConfig json error";
            return 0;
        }
    }

    //-only-file header
};
