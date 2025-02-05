#pragma once
#include "../genPrpt/MidiRouteInputPrivate.h"




class MidiRouteInput : public MidiRouteInputPrivate

{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit MidiRouteInput(QObject *parent = nullptr);
    void clearEasyConfigMidiRouterChains();
    void createEasyConfigChains(EasyConfig *easyConfig);
    void addMonitorEasyConfigIfRequired();
    void addMidiPresetControlEasyConfigsIfRequired(QList<MidiPresetControlEasyConfig> &midiPresetControlEasyConfigs);
    void clearMidiRouterChains();
public slots:
    void addMidiRouterChain(const QString name);
    void delMidiRouterChain(const int idx);
    void clear14BitCc();
    void add14BitCc(int channel, int cc);
private:

};
