#include "wcuserdata.h"
#include <QJsonDocument>

WcUserData::WcUserData(Webchannel::WcMidiIn *wcmidiin,
                       Webchannel::WcMidiOut *wcmidiout,
                       QObject *parent) :wcmidiin{wcmidiin},
                        wcmidiout{wcmidiout},
                        QObject(parent)
{

    QString str = "{}";

    QByteArray br = str.toUtf8();

    QJsonDocument doc = QJsonDocument::fromJson(br);

    userdata = doc.object();




}
