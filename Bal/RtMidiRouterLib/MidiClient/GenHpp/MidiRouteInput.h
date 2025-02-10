#pragma once
#include "../genPrpt/MidiRouteInputPrivate.h"




class MidiRouteInput : public MidiRouteInputPrivate

{
    Q_OBJECT
    QML_ELEMENT
public:
#line 23 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiRouteInput.hpp"
    explicit MidiRouteInput(QObject *parent = nullptr);
#line 44 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiRouteInput.hpp"
    void clearEasyConfigMidiRouterChains();
#line 55 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiRouteInput.hpp"
    void createEasyConfigChains(EasyConfig *easyConfig);
#line 68 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiRouteInput.hpp"
    void addMonitorEasyConfigIfRequired();
#line 79 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiRouteInput.hpp"
    void addMidiPresetControlEasyConfigsIfRequired(QList<MidiPresetControlEasyConfig> &midiPresetControlEasyConfigs);
#line 94 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiRouteInput.hpp"
    void clearMidiRouterChains();
public slots:
#line 109 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiRouteInput.hpp"
    void addMidiRouterChain(const QString name);
#line 118 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiRouteInput.hpp"
    void delMidiRouterChain(const int idx);
#line 124 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiRouteInput.hpp"
    void clear14BitCc();
#line 131 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/MidiRouteInput.hpp"
    void add14BitCc(int channel, int cc);
private:

};
