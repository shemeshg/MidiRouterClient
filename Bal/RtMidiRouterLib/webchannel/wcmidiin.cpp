#include "wcmidiin.h"


namespace Webchannel{
WcMidiIn::WcMidiIn(QObject *parent) : QObject(parent)
{
    midiin = std::unique_ptr<WcMidiInListener>(new WcMidiInListener(*this));
}

bool WcMidiIn::msgToServer(const QString &msg){
    emit msgToClient("Just received msg from client of " + msg);
    return true;
}

int WcMidiIn::getPortCount(){

    return (int)midiin->getPortCount();
};

QString WcMidiIn::getPortName(int i){
    return  QString::fromStdString(  midiin->getPortName(i) );
}

int WcMidiIn::getPortNumber(const QString &s){
    return midiin->getPortNumber(s.toStdString());
}

QVariantMap WcMidiIn::getPorts(){
    QVariantMap qm;
    int nPorts = (int)midiin->getPortCount();

    for ( int i=0; i<nPorts; i++ ) {
        qm[QString::number(i)] = QString::fromStdString( midiin->getPortName(i));
    }
    return qm;
}

QVariantMap WcMidiIn::getOpenedPorts(){
    QVariantMap qm;

    for(auto const& imap: openedMidiInObj){
        qm[QString::number(imap.first)] = QString::fromStdString(imap.second->midiin->getOpenedPortName());
    }

    return qm;
}


void WcMidiIn::openPort( int portNumber){
    if ( openedMidiInObj.find(portNumber) == openedMidiInObj.end() ) {
        // not found
        openedMidiInObj[portNumber] = std::unique_ptr<WcMidiInListener>(new WcMidiInListener(*this));
        openedMidiInObj[portNumber]->openPort(portNumber);
    } else {
        // found
        return;
    }
}

void WcMidiIn::openVirtualPort(const QString &s){
    return midiin->openVirtualPort(s.toStdString());
}

void WcMidiIn::msgSend(RtMidiWrap::MidiEvent &m, LOG_TO logto, std::string userdata){
    if (logto == LOG_TO::CLIENT){
        QJsonObject qvm;
        qvm["portName"] = QString::fromStdString(m.portName);

        qvm["portNumber"] = m.portNumber;
        qvm["deltatime"] = m.deltatime;
        qvm["channel"] = m.channel;
        qvm["msgtype"] = m.msgtype;
        qvm["command"] = m.command;
        qvm["commandStr"] = QString::fromStdString(m.commandStr);
        qvm["data1"] = m.data1;
        qvm["data2"] = m.data2;
        qvm["userdata"] = QString::fromStdString(userdata);
        qvm["nrpnControl"] = m.nrpnControl;
        qvm["nrpnData"] = m.nrpnData;

        QJsonArray dataArray;
        foreach (const int data, m.data) {
            dataArray.append(data);
        }
        qvm["data"] = dataArray;

        QJsonDocument doc;
        doc.setObject(qvm);
        emit dataToClient(doc.toJson());
    } else {
        qDebug()<<"It is server intercepted MidiEvent";
        QJsonDocument jsonDoc = QJsonDocument::fromJson(QString::fromStdString(userdata).toUtf8());
        if (!jsonDoc.isNull() ||
            !jsonDoc.isObject()
            ) {
            auto obj = jsonDoc.object();
            if (obj["action"].isString() && obj["action"].toString()=="presetOnOff"){
                emit presetOnOff(obj["presetMidiType"].toInt(),
                                 obj["presetUuid"].toString());
            }

        }


        std::cout<<m.portName<<" ";
        std::cout<<m.portNumber<<" ";
        std::cout<<m.deltatime<<" ";
        std::cout<<m.channel<<" ";
        std::cout<<m.commandStr<<" ";
        std::cout<<m.data1<<" ";
        std::cout<<m.data2<<" "<<std::endl;
        std::cout<<userdata<<std::endl;

        unsigned int nBytes = (unsigned int)m.data.size();
        for ( unsigned int i=0; i<nBytes; i++ )
            std::cout << "Byte " << i << " = " << (int)m.data.at(i) << ", ";
        std::cout<<std::endl;


    }
}

bool WcMidiIn::isPortOpen( int portNumber){
    bool isOpened = openedMidiInObj[portNumber]->midiin->isPortOpen();
    return isOpened;
}





}
