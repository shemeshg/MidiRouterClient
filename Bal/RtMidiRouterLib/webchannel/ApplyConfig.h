#ifndef APPLYCONFIG_H
#define APPLYCONFIG_H
#include "WcMidiIn.h"
#include "WcMidiOut.h"
class ApplyConfig {
public:
    ApplyConfig(Webchannel::WcMidiIn *wcmidiin, Webchannel::WcMidiOut *wcmidiout)
        : wcmidiin{wcmidiin}, wcmidiout{wcmidiout} {}

    void applyConfig(const QJsonObject &json) {
        // qDebug()<<"Server will applay a config of "<<json;
        wcmidiin->restart();
        wcmidiout->restart();

        QVariantMap inPortsMap = wcmidiin->getPorts();
        // QVariantMap outPortMap = wcmidiout->getPorts();

        setVirtualPorts(inPortsMap, json);
    }

private:
    Webchannel::WcMidiIn *wcmidiin;
    Webchannel::WcMidiOut *wcmidiout;

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
