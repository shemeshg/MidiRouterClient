#pragma once
#include "EasyConfig.h"
#include "FilterAndTransform.h"
#include "FilterSchedule.h"
#include "FilterToConsle.h"
#include "MidiPresetControlEasyConfig.h"
#include "../genPrpt/MidiRouterChainPrivate.h"
#include <QtCore/qjsondocument.h>
#include <QtCore/qjsonobject.h>


class MidiRouterChain : public MidiRouterChainPrivate

{
    Q_OBJECT
    QML_ELEMENT
public:
#line 39 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiRouterChain.hpp"
    explicit MidiRouterChain(QObject *parent = nullptr);
public slots:
#line 49 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiRouterChain.hpp"
    void clearMidiRoutersFilters();
#line 64 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiRouterChain.hpp"
    void delMidiRoutersFilter(const int id);
#line 80 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiRouterChain.hpp"
    void addFilterMidiDestination(QString midiDestination);
#line 90 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiRouterChain.hpp"
    void addFilterToConsole(FilterToConsole::LogTo logTo, QString userData);
#line 100 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiRouterChain.hpp"
    void addFilterNetworkDestination(QString serverName, int serverPort, QString baseMidiRouteInput);
#line 110 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiRouterChain.hpp"
    void addFilterFilterSchedule(FilterSchedule::DefferedType defferedType, int defferedTo );
#line 120 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiRouterChain.hpp"
    void addFilterAndTransform(QString name, FilterAndTransform::ConditionAction conditionAction, QString filterChannel,
                               QString filterEvents, QString filterData1, QString filterData2 );
#line 132 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiRouterChain.hpp"
    void addEasyConfigMonitor();
#line 143 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiRouterChain.hpp"
    void addEasyConfigPresetFilter(const MidiPresetControlEasyConfig &m);
#line 178 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiRouterChain.hpp"
    void addEasyConfigPresetLogOnOff(QString presetUuid, bool isMidiControlOn);
#line 192 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiRouterChain.hpp"
    void setEasyConfigChain(EasyConfig *easyConfig,EasyConfigRoute *easyConfigRoute);
signals:


private:

};
