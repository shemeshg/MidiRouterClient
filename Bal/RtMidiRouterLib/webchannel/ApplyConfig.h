#ifndef APPLYCONFIG_H
#define APPLYCONFIG_H
#include "WcMidiIn.h"
#include "WcMidiOut.h"
class ApplyConfig {
public:
    ApplyConfig(Webchannel::WcMidiIn *wcmidiin, Webchannel::WcMidiOut *wcmidiout)
        : wcmidiin{wcmidiin}, wcmidiout{wcmidiout} {}

    struct DisCnctOutPort {
        QString outPortName;
        QString originedInPort;
    };

    void applyConfig(const QJsonObject &json) {
        qDebug() << "Server will applay a config of " << json;
        wcmidiin->restart();
        wcmidiout->restart();

        QVariantMap inPortsMap = wcmidiin->getPorts();
        QVariantMap outPortMap = wcmidiout->getPorts();

        setVirtualPorts(inPortsMap, json);

        inPorts = getMapStringVal(wcmidiin->getPorts());
        outPorts = getMapStringVal(wcmidiout->getPorts());
        disCnctInPorts.clear();
        disCnctOutPort.clear();

        setMidiRoutePresets(json);
    }

private:
    Webchannel::WcMidiIn *wcmidiin;
    Webchannel::WcMidiOut *wcmidiout;

    QStringList inPorts;
    QStringList outPorts;
    QStringList disCnctInPorts;
    QList<DisCnctOutPort> disCnctOutPort;

    enum class FilterType {
        TO_MIDI_DESTINATION,
        TO_CONSOLE,
        TO_NETWORK,
        SCHEDULE_TO,
        FILTER_AND_TRANSFORM
    };

    QStringList getMapStringVal(QVariantMap map) {
        QStringList list;
        for (auto it = map.begin(); it != map.end(); ++it) {
            list.append(it.value().toString());
        }
        return list;
    }

    QStringList getInHwPortNames(const QVariantMap &inPortsMap) {
        QStringList inHwPortNames;
        for (auto it = inPortsMap.begin(); it != inPortsMap.end(); ++it) {
            QString val = it.value().toString();
            inHwPortNames.append(val.mid(val.indexOf("_") + 1));
        }

        return inHwPortNames;
    }

    void setVirtualPorts(const QVariantMap &inPortsMap, const QJsonObject &json) {
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

    void setMidiRoutePresets(const QJsonObject &json) {
        auto midiRoutePresets = json["midiRoutePresets"];
        if (midiRoutePresets.isArray()) {
            auto midiRoutePresetsObj = midiRoutePresets.toArray();

            for (auto const &midiRoutePreset : midiRoutePresetsObj) {
                if (midiRoutePreset.isObject()) {
                    auto midiRoutePresetObj = midiRoutePreset.toObject();
                    bool isEnabled = midiRoutePresetObj["isEnabled"].toBool();
                    if (isEnabled) {
                        qDebug() << "TODO midiControlOff, check OFF iNports exists";
                        setMidiRouteInputs(midiRoutePresetObj);

                    } else {
                        qDebug() << "TODO  midiControlOn, check ON activation port  exists";
                    }
                }
            }
        }
    }

    bool getBoolIgnoreTypes(QJsonObject &midiRouteInputObj, QString name) {
        return midiRouteInputObj["ignoreTypes"].toObject()["name"].toBool();
    }

    double getDoubleTimeSig(QJsonObject &midiRouteInputObj, QString name) {
        return midiRouteInputObj["midiRouteClock"].toObject()["name"].toBool();
    }

    void setMidiRouteInputs(QJsonObject &midiRoutePresetObj) {
        auto midiRouteInputs = midiRoutePresetObj["midiRouteInputs"];

        if (midiRouteInputs.isObject()) {
            auto midiRouteInputsObj = midiRouteInputs.toObject();

            for (auto it = midiRouteInputsObj.begin(); it != midiRouteInputsObj.end();
                 ++it) {
                auto midiRouteInputObj = it.value().toObject();
                auto midiInputName = midiRouteInputObj["midiInputName"].toString();

                if (inPorts.contains(midiInputName)) {
                    setInportSettings(midiRouteInputObj, midiInputName);

                } else if (!disCnctInPorts.contains(midiInputName)) {
                    disCnctInPorts.append(midiInputName);
                }
            }
        }
    }

    void setInportSettings(QJsonObject &midiRouteInputObj,
                           QString &midiInputName) {
        qDebug() << "TODO Applay input to " << midiRouteInputObj;
        int portNumber = wcmidiin->getPortNumber(midiInputName);

        wcmidiin->openPort(portNumber);

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
                port.originedInPort = midiInputName;
                port.outPortName = outPortName;
                disCnctOutPort.append(port);
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

        qDebug() << "TODO Inports chains and routes";
        auto midiRouterChains = midiRouteInputObj["midiRouterChains"].toArray();
        for (const auto &midiRouterChain : midiRouterChains) {
            auto midiRouterChainObj = midiRouterChain.toObject();
            auto midiRoutersFilters =
                midiRouterChainObj["midiRoutersFilters"].toArray();
            if (midiRoutersFilters.size() > 0) {
                qDebug() << "TODO CREATE CHAIN AND PARSE FILTER " << midiInputName
                         << midiRouterChainObj["name"].toString();
                int chainId = wcmidiin->routingMidiChainsAaddChain(portNumber);
                for (const auto &midiRoutersFilter : midiRoutersFilters) {
                    auto filter = midiRoutersFilter.toObject();
                    qDebug() << "Add to chain " << chainId << filter;
                    if (filter["filterType"].toInt() ==
                        static_cast<int>(FilterType::TO_MIDI_DESTINATION)) {
                        qDebug()<<"** SENDING "<< filter["baseMidiRouteInput"]
                                                         .toObject()["midiInputName"]
                                                         .toString();
                        int outPortNumber = wcmidiout->getPortNumber(                            filter["baseMidiRouteInput"]
                                                                         .toObject()["midiInputName"]
                                                                         .toString());


                        qDebug()<<"** id "<< outPortNumber;
                        wcmidiin->routingActionAddSendPortByNumber(
                            portNumber, chainId,
                            outPortNumber);

                    } else if (filter["filterType"].toInt() ==
                               static_cast<int>(FilterType::TO_CONSOLE)) {
                        wcmidiin->routingActionAddLogData(portNumber, chainId,
                                                          filter["logTo"].toInt(),
                                                          filter["userdata"].toString());
                    }  else if (filter["filterType"].toInt() == static_cast<int>(FilterType::SCHEDULE_TO)){


                        wcmidiin->routingActionAddDeferedEvent(portNumber, chainId,
                            filter["defferedType"].toInt(),
                            filter["defferedTo"].toDouble()
                            );
                    } else if (filter["filterType"].toInt() == static_cast<int>(FilterType::TO_NETWORK)){
                        QString remotePortName = filter["baseMidiRouteInput"].toObject()["midiInputName"].toString();
                        wcmidiin->routingActionAddSendRemoteServerByRemotePortName(portNumber, chainId,
                                                                   filter["serverName"].toString(),
                                                                     filter["serverPort"].toInt(),
                                                                     remotePortName
                                                                     );
                    } else if (filter["filterType"].toInt() == static_cast<int>(FilterType::FILTER_AND_TRANSFORM)) {
                        wcmidiin->routingActionAddFilterMidiChannelMsg(portNumber, chainId,
                                    filter["filterChannel"].toArray(),
                                   filter["filterEvents"].toArray(),
                                   filter["filterData1"].toArray(),
                                   filter["filterData2"].toArray(),
                                    filter["conditionAction"].toInt()
                                   );
                    }
                }
            }
        }
    }
};

#endif // APPLYCONFIG_H
