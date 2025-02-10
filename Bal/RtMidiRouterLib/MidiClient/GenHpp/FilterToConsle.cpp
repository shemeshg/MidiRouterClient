#line 7 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/FilterToConsle.hpp"
#include "FilterToConsle.h"
     FilterToConsole::FilterToConsole(QObject * parent) 
#line 24 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/FilterToConsle.hpp"
    : FilterToConslePrivate{parent}
    {
         setFilterType( FilterType::TO_CONSOLE);
         setUserdata("{}");
    }

    void FilterToConsole::setFilter(LogTo logTo, QString userData) 
#line 35 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/FilterToConsle.hpp"
    {
        setLogTo(logTo);
        setUserdata(userData);
        QString logToString = logTo == LogTo::CLIENT ? "Client" : "Server";
        setName("Log to " + logToString);
    }

