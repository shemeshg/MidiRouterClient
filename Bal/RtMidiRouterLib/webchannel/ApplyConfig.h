#ifndef APPLYCONFIG_H
#define APPLYCONFIG_H
#include "WcMidiIn.h"
#include "WcMidiOut.h"
class ApplyConfig
{
public:
    ApplyConfig(Webchannel::WcMidiIn *wcmidiin,
                Webchannel::WcMidiOut *wcmidiout): wcmidiin{wcmidiin},
        wcmidiout{wcmidiout}{

    }

     void applyConfig(const QJsonObject &json){
         //qDebug()<<"Server will applay a config of "<<json;
         wcmidiin->restart();
         wcmidiout->restart();

         auto inPortsMap = wcmidiin->getPorts();
         auto outPortMap = wcmidiout->getPorts();
         qDebug()<<inPortsMap<<outPortMap;
     }

private:
    Webchannel::WcMidiIn *wcmidiin;
    Webchannel::WcMidiOut *wcmidiout;
};

#endif // APPLYCONFIG_H
