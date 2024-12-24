#include "MidiClientUtil.h"
#include <QUuid>
    QString getUuId() 
{
    return QUuid::createUuid().toString().replace("{", "").replace("}", "");
}
