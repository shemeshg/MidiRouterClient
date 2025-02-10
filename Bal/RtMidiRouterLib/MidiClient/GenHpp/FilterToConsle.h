#pragma once
#include "../genPrpt/FilterToConslePrivate.h"



class FilterToConsole : public FilterToConslePrivate

{
    Q_OBJECT
    QML_ELEMENT
public:
#line 22 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/FilterToConsle.hpp"
    explicit FilterToConsole(QObject *parent = nullptr);
public slots:
#line 33 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/FilterToConsle.hpp"
    void setFilter(LogTo logTo, QString userData);
private:

};

