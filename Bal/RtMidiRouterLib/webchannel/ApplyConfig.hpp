//-define-file body webchannel/ApplyConfig.cpp
//-define-file header webchannel/ApplyConfig.h
//-only-file header //-
#pragma once
#include "wcmidiin.h"
#include "wcmidiout.h"
//-only-file body //-
//- #include "ApplyConfig.h"

//-only-file header
//-var {PRE} "ApplyConfig::"
class ApplyConfig {
public:
    ApplyConfig(Webchannel::WcMidiIn *wcmidiin, Webchannel::WcMidiOut *wcmidiout)
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
        QJsonArray midiRoutePresets = json["midiRoutePresets"].toArray();

        for (int i = 0; i < midiRoutePresets.size(); ++i) {
            QJsonObject midiRoutePresetObj = midiRoutePresets[i].toObject();
            if (midiRoutePresetObj["uuid"].toString() == presetUuid) {
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
    QJsonObject applyConfig(const QJsonObject &json)
    //-only-file body
    {
        qDebug() << "Server will applay a config of " << json;
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
    void setVirtualPorts(const QVariantMap &inPortsMap, const QJsonObject &json)
    //-only-file body
    {
        QStringList inHwPortNames = getInHwPortNames(inPortsMap);

        QJsonArray virtualInPorts;
        if (json["virtualInPorts"].isArray()) {
            virtualInPorts = json["virtualInPorts"].toArray();
        }

        for (const auto &itm : virtualInPorts) {
            QString str = itm.toString();
            if (!inHwPortNames.contains(str)) {
                wcmidiin->openVirtualInOutPort(str);
            }
        }
    }

    //- {fn}
    void setMidiRoutePresets(const QJsonObject &json)
    //-only-file body
    {
        auto midiRoutePresets = json["midiRoutePresets"];
        if (midiRoutePresets.isArray()) {
            auto midiRoutePresetsObj = midiRoutePresets.toArray();

            for (auto const &midiRoutePreset : midiRoutePresetsObj) {
                if (midiRoutePreset.isObject()) {
                    auto midiRoutePresetObj = midiRoutePreset.toObject();
                    bool isEnabled = midiRoutePresetObj["isEnabled"].toBool();
                    setMidiRouteInputs(midiRoutePresetObj, isEnabled);
                    // send user control if required
                    if (isEnabled) {
                        auto userControlsObj = midiRoutePresetObj["userControls"].toArray();
                        for (const auto &ctrl : userControlsObj) {
                            auto ctrlObj = ctrl.toObject();
                            if (ctrlObj["isSendOnPresetChange"].toBool()) {
                                QString outputPortnName = ctrlObj["outputPortnName"].toString();
                                if (outputPortnName.isEmpty()) {
                                    continue;
                                }
                                int portNumber = wcmidiout->getPortNumber(outputPortnName);
                                if (portNumber == -1) {
                                    continue;
                                }
                                wcmidiout->openPort(portNumber);
                                int eventType = ctrlObj["eventType"].toInt();
                                if (eventType == 0) {

                                    wcmidiout->sendControlChange(
                                        portNumber, ctrlObj["ccId"].toInt(),
                                        ctrlObj["inputVal"].toInt(),
                                        {ctrlObj["channelId"].toString()});
                                } else if (eventType == 1) {
                                    wcmidiout->sendProgramChange(
                                        portNumber, ctrlObj["inputVal"].toInt(),
                                        {ctrlObj["channelId"].toString()});
                                } else if (eventType == 2) {
                                    wcmidiout->setNonRegisteredParameterInt(
                                        portNumber, ctrlObj["nrpnControl"].toInt(),
                                        ctrlObj["inputVal"].toInt(),
                                        {ctrlObj["channelId"].toString()});
                                } else {
                                    qDebug() << "Bad JSON";
                                }

                                qDebug() << "TODO send userControls for enabled preset";
                            }
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
        return midiRouteInputObj["ignoreTypes"].toObject()["name"].toBool();
    }

    //- {fn}
    double getDoubleTimeSig(QJsonObject &midiRouteInputObj, QString name)
    //-only-file body
    {
        return midiRouteInputObj["midiRouteClock"].toObject()["name"].toBool();
    }

    //- {fn}
    void setMidiRouteInputs(QJsonObject &midiRoutePresetObj, bool isEnabled)
    //-only-file body
    {
        auto midiRouteInputs = midiRoutePresetObj["midiRouteInputs"];

        if (midiRouteInputs.isArray()) {
            auto midiRouteInputsObj = midiRouteInputs.toArray();

            for (auto it = midiRouteInputsObj.begin(); it != midiRouteInputsObj.end();
                 ++it) {
                auto midiRouteInputObj = it->toObject();
                auto midiInputName = midiRouteInputObj["midiInputName"].toString();

                QString presetUuid = midiRoutePresetObj["uuid"].toString();
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
        auto propegateInputs =
            midiRouteInputObj["midiRouteClock"].toObject()["propegateInputs"];
        auto propegateInputsAry = propegateInputs.toArray();
        for (const auto &propegateInput : propegateInputsAry) {
            auto outPortName = propegateInput.toObject()["midiInputName"].toString();
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

        auto cc14bitAry = midiRouteInputObj["cc14bitAry"].toArray();
        wcmidiin->clearCc14Bit(portNumber);
        for (const auto &cc14 : cc14bitAry) {
            auto cc14Obj = cc14.toObject();
            qDebug() << "CHANNEL CC " << cc14Obj;
            wcmidiin->addCc14Bit(portNumber, cc14Obj["channel"].toInt(),
                                 cc14Obj["cc"].toInt());
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
                                     QJsonArray &midiRoutersFilters,
                                     int portNumber,
                                     QJsonObject &midiRouterChainObj)
    //-only-file body
    {
        qDebug() << "TODO CREATE CHAIN AND PARSE FILTER " << midiInputName
                 << midiRouterChainObj["name"].toString();
        int chainId = wcmidiin->routingMidiChainsAaddChain(portNumber);
        for (const auto &midiRoutersFilter : midiRoutersFilters) {
            auto filter = midiRoutersFilter.toObject();
            qDebug() << "Add to chain " << chainId << filter;
            if (filter["filterType"].toInt() ==
                static_cast<int>(FilterType::TO_MIDI_DESTINATION)) {
                qDebug() << "** SENDING " << filter["midiInputName"].toString();
                int outPortNumber =
                    wcmidiout->getPortNumber(filter["midiInputName"].toString());

                qDebug() << "** id " << outPortNumber;
                if (outPortNumber >= 0) {
                    wcmidiin->routingActionAddSendPortByNumber(portNumber, chainId,
                                                               outPortNumber);
                } else {
                    qDebug() << "Could not find out port";
                }

            } else if (filter["filterType"].toInt() ==
                       static_cast<int>(FilterType::TO_CONSOLE)) {
                wcmidiin->routingActionAddLogData(portNumber, chainId,
                                                  filter["logTo"].toInt(),
                                                  filter["userdata"].toString());
            } else if (filter["filterType"].toInt() ==
                       static_cast<int>(FilterType::SCHEDULE_TO)) {

                wcmidiin->routingActionAddDeferedEvent(portNumber, chainId,
                                                       filter["defferedType"].toInt(),
                                                       filter["defferedTo"].toDouble());
            } else if (filter["filterType"].toInt() ==
                       static_cast<int>(FilterType::TO_NETWORK)) {
                QString remotePortName = filter["midiInputName"].toString();
                auto ok = wcmidiin->routingActionAddSendRemoteServerByRemotePortName(
                    portNumber, chainId, filter["serverName"].toString(),
                    filter["serverPort"].toInt(), remotePortName);
                if (ok == -1) {
                    qDebug() << "Could not add remote Port for some reason";
                }
            } else if (filter["filterType"].toInt() ==
                       static_cast<int>(FilterType::FILTER_AND_TRANSFORM)) {
                wcmidiin->routingActionAddFilterMidiChannelMsg(
                    portNumber, chainId,
                    stringToJsonArray(filter["filterChannel"].toString()),
                    stringToJsonArray(filter["filterEvents"].toString()),
                    stringToJsonArray(filter["filterData1"].toString()),
                    stringToJsonArray(filter["filterData2"].toString()),
                    filter["conditionAction"].toInt());
            }
        }
    }

    //- {fn}
    void setInputRouterChains(bool isEnabled, int portNumber,
                                     QJsonObject &midiRouteInputObj,
                                     QString &midiInputName)
    //-only-file body
    {
        qDebug() << "TODO Inports chains and routes";
        auto midiRouterChains = midiRouteInputObj["midiRouterChains"].toArray();
        for (const auto &midiRouterChain : midiRouterChains) {

            //
            QJsonObject midiRouterChainObj = midiRouterChain.toObject();
            if (isEnabled || midiRouterChainObj["isRunForPresetOnAndOff"].toBool()) {
                QJsonArray midiRoutersFilters =
                    midiRouterChainObj["midiRoutersFilters"].toArray();
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
};
