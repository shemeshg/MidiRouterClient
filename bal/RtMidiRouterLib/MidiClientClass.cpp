#include "MidiClientClass.h"
#include <QDebug>

MidiClientClass::MidiClientClass() {}

void MidiClientClass::start(int portNumber)
{
    qDebug() << "client starting at" << portNumber;
}

void MidiClientClass::stop()
{
    qDebug() << "client stopped";
}
