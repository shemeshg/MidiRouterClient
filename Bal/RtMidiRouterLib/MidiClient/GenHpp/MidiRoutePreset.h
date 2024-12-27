#pragma once
#include "MidiClientUtil.h"
#include "../genPrpt/MidiRoutePresetPrivate.h"

class MidiRoutePreset : public MidiRoutePresetPrivate

{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit MidiRoutePreset(QString computerUuid, QObject *parent = nullptr);
    void recreateEasyConfig(QList<MidiPresetControlEasyConfig> &midiPresetControlEasyConfigs);
public slots:
     MidiRouteInput* getInputOrCreateByName(QString midiInputName);
signals:


private:


    std::optional<MidiRouteInput *> getInputByName(QString midiInputName);
};
