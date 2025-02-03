#pragma once
#include "../genPrpt/MidiRoutePresetPrivate.h"
#include "MidiClientUtil.h"


class MidiRoutePreset : public MidiRoutePresetPrivate

{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit MidiRoutePreset(QString computerUuid, QObject *parent = nullptr);
    void recreateEasyConfig(QList<MidiPresetControlEasyConfig> &midiPresetControlEasyConfigs);
public slots:
     MidiRouteInput* getInputOrCreateByName(QString midiInputName);
     void addUserControl();
     void delUserControl(int id);
     void sendAllUserControls();
signals:


private:


    std::optional<MidiRouteInput *> getInputByName(QString midiInputName);
};
