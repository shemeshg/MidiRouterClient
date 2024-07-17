

#pragma once

#include "PresetMidiControlPrivate.h"

class PresetMidiControl : public PresetMidiControlPrivate

{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit PresetMidiControl(QObject *parent = nullptr)
        : PresetMidiControlPrivate{parent} {};

public slots:

private:
};
