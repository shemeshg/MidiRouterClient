#ifndef APPLYCONFIG_H
#define APPLYCONFIG_H
#include "WcMidiIn.h"
#include "WcMidiOut.h"
class ApplyConfig {
public:
    ApplyConfig(Webchannel::WcMidiIn *wcmidiin, Webchannel::WcMidiOut *wcmidiout)
        : wcmidiin{wcmidiin}, wcmidiout{wcmidiout} {}

    struct DisCnctOutPort{
        QString outPortName;
        QString originedInPort;
    };



    void applyConfig(const QJsonObject &json) {
        qDebug()<<"Server will applay a config of "<<json;
        wcmidiin->restart();
        wcmidiout->restart();

        QVariantMap inPortsMap = wcmidiin->getPorts();
        QVariantMap outPortMap = wcmidiout->getPorts();

        setVirtualPorts(inPortsMap, json);

        inPorts=getMapStringVal(wcmidiin->getPorts());
        outPorts = getMapStringVal(wcmidiout->getPorts());
        disCnctInPorts.clear();
        disCnctOutPort.clear();

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
                        setMidiRouteInputs(midiRoutePresetObj);
                        setEasyConfig(midiRoutePresetObj);
                    } else {
                        qDebug()<<"TODO  midiControlOn, check ON activation port  exists";
                    }
                }

            }
        }
    }

    bool getBoolIgnoreTypes(QJsonObject &midiRouteInputObj, QString name){
        return midiRouteInputObj["ignoreTypes"].toObject()["name"].toBool();
    }

    double getDoubleTimeSig(QJsonObject &midiRouteInputObj, QString name){
        return midiRouteInputObj["midiRouteClock"].toObject()["name"].toBool();
    }




    void setMidiRouteInputs(QJsonObject &midiRoutePresetObj){
        auto midiRouteInputs = midiRoutePresetObj["midiRouteInputs"];

        if (midiRouteInputs.isObject()){
            auto midiRouteInputsObj = midiRouteInputs.toObject();

            for (auto it = midiRouteInputsObj.begin(); it != midiRouteInputsObj.end(); ++it) {
                auto midiRouteInputObj = it.value().toObject();
                auto midiInputName = midiRouteInputObj["midiInputName"].toString();

                if (inPorts.contains(midiInputName)){
                    setInportSettings(midiRouteInputObj, midiInputName);


                    qDebug()<<"TODO Inports chains and routes";
                } else if (!disCnctInPorts.contains(midiInputName)){
                    disCnctInPorts.append(midiInputName);
                }

            }
        }
    }


    inline void setInportSettings(QJsonObject &midiRouteInputObj, QString &midiInputName)
    {
        qDebug()<<"TODO Applay input to "<<midiRouteInputObj;
        int portNumber = wcmidiin->getPortNumber(midiInputName);

        wcmidiin->openPort(portNumber);

        wcmidiin->ignoreTypes(portNumber,
                              getBoolIgnoreTypes(midiRouteInputObj,"midiSysex"),
                              getBoolIgnoreTypes(midiRouteInputObj,"midiTime"),
                              getBoolIgnoreTypes(midiRouteInputObj,"midiSense"));

        wcmidiin->setTimeSig(portNumber,
                             getDoubleTimeSig(midiRouteInputObj,"timeSig"),
                             getDoubleTimeSig(midiRouteInputObj,"timeSigDivBy"),
                             getDoubleTimeSig(midiRouteInputObj,"fromSppPos")
                             );

        wcmidiin->clearPropegateClockPort(portNumber);
        auto propegateInputs = midiRouteInputObj["midiRouteClock"].toObject()["propegateInputs"];
        auto propegateInputsAry =  propegateInputs.toArray();
        for (const auto &propegateInput: propegateInputsAry){
            auto outPortName = propegateInput.toObject()["midiInputName"].toString();
            if (outPorts.contains(outPortName)){
                int outPortId = wcmidiout->getPortNumber(outPortName);
                wcmidiin->addPropegateClockPort(portNumber,outPortId);
            } else {
                DisCnctOutPort port;
                port.originedInPort = midiInputName;
                port.outPortName = outPortName;
                disCnctOutPort.append(port);
            }

        }


        auto cc14bitAry = midiRouteInputObj["cc14bitAry"].toArray();
        wcmidiin->clearCc14Bit(portNumber);
        for (const auto &cc14: cc14bitAry){
            auto cc14Obj = cc14.toObject();
            qDebug()<<"CHANNEL CC "<<cc14Obj;
            wcmidiin->addCc14Bit(portNumber, cc14Obj["channel"].toInt(),cc14Obj["cc"].toInt());

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


    QStringList inPorts;
    QStringList outPorts;
    QStringList disCnctInPorts;
    QList<DisCnctOutPort> disCnctOutPort;

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
