#pragma once
#include <QJsonValue>
#include <QtCore/qjsonarray.h>
#include <QtCore/qjsondocument.h>
#include <QtCore/qjsonobject.h>
#include "../genPrpt/Dropdownlist.h"
#include "MidiRoutePreset.h"



class UserConfigGenJson
{
public:    
    UserConfigGenJson(){}

#line 30 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigGenJson.hpp"
    QJsonObject getJson(
                        int activePresetID,
                        QList<Dropdownlist *> dropdownlists,
                        QList<QString> virtualInPorts,
                        QList<MidiRoutePreset *> midiRoutePresets);
private:

#line 50 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigGenJson.hpp"
    QJsonArray getDropdownList(QList<Dropdownlist *> dropdownlists);
#line 64 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigGenJson.hpp"
    QJsonArray getListToJsonAry(const QStringList &sl);
#line 75 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigGenJson.hpp"
    QJsonArray getListToJMidiInsonAry(const QStringList &sl);
#line 88 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigGenJson.hpp"
    QJsonArray getMidiRoutePresets(QList<MidiRoutePreset *> midiRoutePresets);
#line 119 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigGenJson.hpp"
    QJsonObject getEasyConfig(EasyConfig * easyConfig);
#line 140 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigGenJson.hpp"
    QJsonArray getEasyConfigRoutes(QList<EasyConfigRoute *> easyConfigRoutes);
#line 168 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigGenJson.hpp"
    QJsonArray getStringListToJsonAry(QStringList list );
#line 179 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigGenJson.hpp"
    QJsonArray getKeyboardSplits(QList<int> keyboardSplits);
#line 192 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigGenJson.hpp"
    QJsonObject getModiControlOnOff(PresetMidiControl *presetMidiControl);
#line 207 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigGenJson.hpp"
    QJsonObject getMidiRouteInputs(QList<MidiRouteInput *> midiRouteInputs);
#line 218 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigGenJson.hpp"
    QJsonArray getCc14bitAry(MidiRouteInput *midiRouteInput);
#line 233 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigGenJson.hpp"
    QJsonObject getMidiRouteClock(MidiRouteInput *midiRouteInput);
#line 246 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigGenJson.hpp"
    QJsonObject getIgnoreTypes(MidiRouteInput *midiRouteInput);
#line 258 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigGenJson.hpp"
    QJsonObject getMonitor(MidiRouteInput *midiRouteInput);
#line 267 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigGenJson.hpp"
    QJsonArray getMidiRouterChains(MidiRouteInput *midiRouteInput);
#line 284 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigGenJson.hpp"
    QJsonObject getBaseMidiRouteInput(QString strMidiInputName);
#line 293 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigGenJson.hpp"
    QJsonArray getMidiRoutersFilters(QList<QVariant> midiRoutersFilters);
#line 343 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigGenJson.hpp"
    QJsonObject getMidiRouteInput(MidiRouteInput *midiRouteInput);
#line 360 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigGenJson.hpp"
    QJsonArray getUserControls(QList<UserControl *> userControls);
#line 387 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigGenJson.hpp"
    QList<MidiPresetControlEasyConfig> getMidiPresetControlEasyConfigs(QList<MidiRoutePreset *> midiRoutePresets);
};
