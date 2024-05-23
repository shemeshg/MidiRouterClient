#include "wcuserdata.h"
#include <QJsonDocument>

WcUserData::WcUserData(QObject *parent) : QObject(parent)
{

    QString str = "{}";

    QByteArray br = str.toUtf8();

    QJsonDocument doc = QJsonDocument::fromJson(br);

    userdata = doc.object();




}
