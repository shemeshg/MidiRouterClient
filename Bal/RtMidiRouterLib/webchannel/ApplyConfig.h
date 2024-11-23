#ifndef APPLYCONFIG_H
#define APPLYCONFIG_H
#include "WcMidiIn.h"
#include "WcMidiOut.h"
class ApplyConfig {
public:
    ApplyConfig(Webchannel::WcMidiIn *wcmidiin, Webchannel::WcMidiOut *wcmidiout)
        : wcmidiin{wcmidiin}, wcmidiout{wcmidiout} {}

    struct DisCnctOutPort{
        std::string outPortName;
        std::string originedInPort;
    };



    void applyConfig(const QJsonObject &json) {
        qDebug()<<"Server will applay a config of "<<json;
        wcmidiin->restart();
        wcmidiout->restart();

        QVariantMap inPortsMap = wcmidiin->getPorts();
        QVariantMap outPortMap = wcmidiout->getPorts();

        setVirtualPorts(inPortsMap, json);

        QStringList inPorts=getMapStringVal(wcmidiin->getPorts());
        QStringList outPorts = getMapStringVal(wcmidiout->getPorts());
        QStringList disCnctInPorts;
        QList<DisCnctOutPort> disCnctOutPort;

        setMidiRoutePresets(json);
    }



    void setMidiRoutePresets(const QJsonObject &json)
    {
        auto midiRoutePresets = json["midiRoutePresets"];
        if (midiRoutePresets.isArray()){
            auto midiRoutePresetsObj = midiRoutePresets.toArray();

            for (auto const &midiRoutePreset: midiRoutePresetsObj){
                if (midiRoutePreset.isObject()){
                    auto midiRoutePresetObj = midiRoutePreset.toObject();
                    bool isEnabled = midiRoutePresetObj["isEnabled"].toBool();
                    if (isEnabled){
                        qDebug()<<"TODO midiControlOff, check OFF iNports exists";
                        qDebug()<<"TODO midiControlOff, check OFF activation port  exists";
                        setEasyConfig(midiRoutePresetObj);
                    } else {
                        qDebug()<<"TODO  midiControlOn, check ON activation port  exists";
                    }
                }

            }
        }
    }

    void setMidiRouteInputs(QJsonObject &midiRoutePresetObj){
        auto midiRouteInputs = midiRoutePresetObj["midiRouteInputs"];
        if (midiRouteInputs.isObject()){
            auto midiRouteInputsObj = midiRouteInputs.toObject();
            for (auto it = midiRouteInputsObj.begin(); it != midiRouteInputsObj.end(); ++it) {
                qDebug()<<"Check if "<<it.key()<<" Exists";

            }
        }
    }

    void setEasyConfig(QJsonObject &midiRoutePresetObj)
    {
        auto easyConfig = midiRoutePresetObj["easyConfig"];
        if (easyConfig.isObject()){
            auto easyConfigObj = easyConfig.toObject();
            auto inputZonesAndRoutes = easyConfigObj["inputZonesAndRoutes"];
            qDebug()<<"inputZonesAndRoutes :";
            if (inputZonesAndRoutes.isObject()){
                auto inputZonesAndRoutesObj= inputZonesAndRoutes.toObject();
                for (auto it = inputZonesAndRoutesObj.begin(); it != inputZonesAndRoutesObj.end(); ++it) {
                    qDebug()<<"ZoneRoute input :"<< it.key();
                    qDebug()<<"TODO if inport exists, and outport exists";
                }
            }
        }
    }
private:
    Webchannel::WcMidiIn *wcmidiin;
    Webchannel::WcMidiOut *wcmidiout;

    QStringList getMapStringVal(QVariantMap map){
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
};

#endif // APPLYCONFIG_H
