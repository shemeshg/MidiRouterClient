#pragma once
#include "MidiRoutePresetPrivate.h"

class MidiRoutePreset : public MidiRoutePresetPrivate

{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit MidiRoutePreset(QObject *parent = nullptr)
        : MidiRoutePresetPrivate{parent} {};

public slots:

private:
};
