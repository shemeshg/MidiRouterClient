#pragma once
#include <QtCore/qjsonarray.h>
#include <QtCore/qjsondocument.h>
#include "UserDataConfigItf.h"

class UserConfigParseJson
{
public:
    UserConfigParseJson(){
    }

#line 22 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigParseJson.hpp"
    void setChanges(UserDataConfigItf *userDataConfigItf, QJsonObject &jsonDoc);
private:
#line 44 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigParseJson.hpp"
    void updateVirtualInPorts(UserDataConfigItf *userDataConfig, const QJsonValue &virtualInPorts);
#line 58 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigParseJson.hpp"
    void updateDropdownlists(UserDataConfigItf *userDataConfig, const QJsonValue &dropdownlists);
#line 71 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigParseJson.hpp"
    void updateMidiRoutePresets(UserDataConfigItf *userDataConfig, const QJsonValue &midiRoutePresets);
#line 91 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigParseJson.hpp"
    MidiRoutePreset* createMidiRoutePreset(UserDataConfigItf *userDataConfig, const QJsonValue &value);
#line 119 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigParseJson.hpp"
    void updateMidiControl(PresetMidiControl *control, const QJsonValue &value, PresetMidiControl::PresetMidiType type);
#line 132 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigParseJson.hpp"
    UserControl* createUserControl(const QJsonValue &userControlValue);
#line 153 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigParseJson.hpp"
    void updateMidiRouteInputs(MidiRoutePreset *preset, const QJsonObject &midiRouteInputs);
#line 169 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigParseJson.hpp"
    MidiRouteInput* createMidiRouteInputEntry(const QJsonObject &value);
#line 230 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigParseJson.hpp"
    void updateMidiRoutersFilters(const QJsonValueRef &midiRoutersFilters, MidiRouterChain *midiRouterChain);
#line 273 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigParseJson.hpp"
    void createEasyConfigEntry(EasyConfig *easyConfigEntry ,const QJsonObject &value);
#line 301 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigParseJson.hpp"
    QList<int> extractKeyboardSplits(const QJsonArray &array);
#line 312 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigParseJson.hpp"
    QStringList convertToQStringList(const QJsonArray &array);
#line 323 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigParseJson.hpp"
    EasyConfigRoute* createEasyConfigRoute(const QJsonObject &value);
#line 345 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigParseJson.hpp"
    QStringList stringListFromJsonAry(const QJsonValue &j);
};


