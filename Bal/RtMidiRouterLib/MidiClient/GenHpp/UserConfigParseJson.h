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
#line 120 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigParseJson.hpp"
    void updateMidiControl(PresetMidiControl *control, const QJsonValue &value, PresetMidiControl::PresetMidiType type);
#line 133 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigParseJson.hpp"
    UserControl* createUserControl(const QJsonValue &userControlValue);
#line 154 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigParseJson.hpp"
    void updateMidiRouteInputs(MidiRoutePreset *preset, const QJsonObject &midiRouteInputs);
#line 170 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigParseJson.hpp"
    MidiRouteInput* createMidiRouteInputEntry(const QJsonObject &value);
#line 231 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigParseJson.hpp"
    void updateMidiRoutersFilters(const QJsonValueRef &midiRoutersFilters, MidiRouterChain *midiRouterChain);
#line 274 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigParseJson.hpp"
    void createEasyConfigEntry(EasyConfig *easyConfigEntry ,const QJsonObject &value);
#line 302 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigParseJson.hpp"
    QList<int> extractKeyboardSplits(const QJsonArray &array);
#line 313 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigParseJson.hpp"
    QStringList convertToQStringList(const QJsonArray &array);
#line 324 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigParseJson.hpp"
    EasyConfigRoute* createEasyConfigRoute(const QJsonObject &value);
#line 346 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserConfigParseJson.hpp"
    QStringList stringListFromJsonAry(const QJsonValue &j);
};


