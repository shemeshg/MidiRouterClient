#pragma once
#include "../genPrpt/MidiRoutePresetPrivate.h"
#include "MidiClientUtil.h"


class MidiRoutePreset : public MidiRoutePresetPrivate

{
    Q_OBJECT
    QML_ELEMENT
public:
#line 23 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiRoutePreset.hpp"
    explicit MidiRoutePreset(QString computerUuid, QObject *parent = nullptr);
#line 40 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiRoutePreset.hpp"
    void recreateEasyConfig(QList<MidiPresetControlEasyConfig> &midiPresetControlEasyConfigs);
public slots:
#line 63 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiRoutePreset.hpp"
     MidiRouteInput* getInputOrCreateByName(QString midiInputName);
#line 77 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiRoutePreset.hpp"
     void addUserControl();
#line 89 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiRoutePreset.hpp"
     void delUserControl(int id);
#line 97 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiRoutePreset.hpp"
     void sendAllUserControls();
signals:


private:


#line 111 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiRoutePreset.hpp"
    std::optional<MidiRouteInput *> getInputByName(QString midiInputName);
};
