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
    explicit MidiRouterChain(QObject *parent = nullptr);
public slots:
    void clearMidiRoutersFilters();
    void delMidiRoutersFilter(const int id);
    void addFilterMidiDestination(QString midiDestination);
    void addFilterToConsole(FilterToConsole::LogTo logTo, QString userData);
    void addFilterNetworkDestination(QString serverName, int serverPort, QString baseMidiRouteInput);
    void addFilterFilterSchedule(FilterSchedule::DefferedType defferedType, int defferedTo );
    void addFilterAndTransform(QString name, FilterAndTransform::ConditionAction conditionAction, QString filterChannel,
                               QString filterEvents, QString filterData1, QString filterData2 );
    void addEasyConfigMonitor();
    void addEasyConfigPresetFilter(const MidiPresetControlEasyConfig &m);
    void addEasyConfigPresetLogOnOff(QString presetUuid, bool isMidiControlOn);
    void setEasyConfigChain(EasyConfig *easyConfig,EasyConfigRoute *easyConfigRoute);
signals:


private:

};
