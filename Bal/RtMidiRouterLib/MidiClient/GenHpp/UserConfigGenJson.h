#pragma once
#include "UserDataConfig.h"
#include "../genPrpt/Dropdownlist.h"
#include <QtCore/qjsonobject.h>

class UserConfigGenJson
{
public:    
    UserConfigGenJson(){}

    QJsonObject getJson(UserDataConfig *userDataConfig,
                        int activePresetID,
                        QList<Dropdownlist *> dropdownlists,
                        QList<QString> virtualInPorts);
private:

    QJsonArray getDropdownList(QList<Dropdownlist *> dropdownlists);
    QJsonArray getListToJsonAry(const QStringList &sl);
    QJsonArray getListToJMidiInsonAry(const QStringList &sl);
    QJsonArray getMidiRoutePresets(UserDataConfig *userDataConfig);
    QJsonObject getEasyConfig(QList<EasyConfig *> easyConfigList);
    QJsonArray getEasyConfigRoutes(QList<EasyConfigRoute *> easyConfigRoutes,  QString midiInputName);
    QJsonArray getStringListToJsonAry(QStringList list );
    QJsonArray getKeyboardSplits(QList<int> keyboardSplits);
    QJsonObject getModiControlOnOff(PresetMidiControl *presetMidiControl);
    QJsonObject getMidiRouteInputs(QList<MidiRouteInput *> midiRouteInputs);
    QJsonArray getCc14bitAry(MidiRouteInput *midiRouteInput);
    QJsonObject getMidiRouteClock(MidiRouteInput *midiRouteInput);
    QJsonObject getIgnoreTypes(MidiRouteInput *midiRouteInput);
    QJsonObject getMonitor(MidiRouteInput *midiRouteInput);
    QJsonArray getMidiRouterChains(MidiRouteInput *midiRouteInput);
    QJsonObject getBaseMidiRouteInput(QString strMidiInputName);
    QJsonArray getMidiRoutersFilters(QList<QVariant> midiRoutersFilters);
    QJsonObject getMidiRouteInput(MidiRouteInput *midiRouteInput);
    QJsonArray getUserControls(QList<UserControl *> userControls);
    QList<MidiPresetControlEasyConfig> getMidiPresetControlEasyConfigs(UserDataConfig *userDataConfig);
};
