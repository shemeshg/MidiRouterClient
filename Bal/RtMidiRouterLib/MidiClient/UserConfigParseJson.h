#ifndef USERCONFIGPARSEJSON_H
#define USERCONFIGPARSEJSON_H


#include <QtCore/qjsonarray.h>
#include <QtCore/qjsondocument.h>
#include "GenHpp/UserDataConfig.h"
class UserConfigParseJson
{
public:
    UserConfigParseJson(){

    }

    void setChanges(UserDataConfig *userDataConfig, QJsonObject &jsonDoc);

private:
    void updateVirtualInPorts(UserDataConfig *userDataConfig, const QJsonValue &virtualInPorts);

    void updateDropdownlists(UserDataConfig *userDataConfig, const QJsonValue &dropdownlists);

    void updateMidiRoutePresets(UserDataConfig *userDataConfig, const QJsonValue &midiRoutePresets);

    MidiRoutePreset* createMidiRoutePreset(UserDataConfig *userDataConfig, const QJsonValue &value);

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

#endif // USERCONFIGPARSEJSON_H
