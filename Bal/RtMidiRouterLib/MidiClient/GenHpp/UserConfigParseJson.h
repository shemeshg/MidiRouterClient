#pragma once
#include <QtCore/qjsonarray.h>
#include <QtCore/qjsondocument.h>
#include "UserDataConfigItf.h"

class UserConfigParseJson
{
public:
    UserConfigParseJson(){
    }

    void setChanges(UserDataConfigItf *userDataConfigItf, QJsonObject &jsonDoc);
private:
    void updateVirtualInPorts(UserDataConfigItf *userDataConfig, const QJsonValue &virtualInPorts);
    void updateDropdownlists(UserDataConfigItf *userDataConfig, const QJsonValue &dropdownlists);
    void updateMidiRoutePresets(UserDataConfigItf *userDataConfig, const QJsonValue &midiRoutePresets);
    MidiRoutePreset* createMidiRoutePreset(UserDataConfigItf *userDataConfig, const QJsonValue &value);
    void updateMidiControl(PresetMidiControl *control, const QJsonValue &value, PresetMidiControl::PresetMidiType type);
    UserControl* createUserControl(const QJsonValue &userControlValue);
    void updateMidiRouteInputs(MidiRoutePreset *preset, const QJsonObject &midiRouteInputs);
    MidiRouteInput* createMidiRouteInputEntry(const QJsonObject &value);
    void updateMidiRoutersFilters(const QJsonValueRef &midiRoutersFilters, MidiRouterChain *midiRouterChain);
    void updateEasyConfig(MidiRoutePreset *preset, const QJsonObject &easyConfig);
    EasyConfig* createEasyConfigEntry(const QString &key, const QJsonObject &value);
    QList<int> extractKeyboardSplits(const QJsonArray &array);
    QStringList convertToQStringList(const QJsonArray &array);
    EasyConfigRoute* createEasyConfigRoute(const QJsonObject &value);
    QStringList stringListFromJsonAry(const QJsonValue &j);
};


