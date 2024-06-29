#include "MidiClientClass.h"
#include <QDebug>

MidiClientClass::MidiClientClass() {}

void MidiClientClass::start(const QString &serverName, int portNumber)
{
    qDebug() << "client " << serverName << " port " << portNumber;
}

void MidiClientClass::stop()
{
    qDebug() << "client stopped";
}
