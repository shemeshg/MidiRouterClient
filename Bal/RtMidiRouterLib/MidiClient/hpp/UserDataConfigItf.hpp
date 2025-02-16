//-define-file header GenHpp/UserDataConfigItf.h
//-only-file header //-
#pragma once
#include <QStringList>
//- #include "MidiRoutePreset.h"
//-only-file null
#include "MidiRoutePreset.hpp"
//-only-file header


//-var {PRE} "UserDataConfigItf::"
class UserDataConfigItf
{
public:
    virtual int activePresetID() const = 0;
    virtual void setActivePresetID(const int newActivePresetID) = 0;
    virtual void setConnectedInPorts(const QStringList &newConnectedInPorts) = 0;
    virtual void setConnectedOutPorts(const QStringList &newConnectedOutPorts) = 0;
    virtual void clearDropdownlists()  = 0;
    virtual void addDropdownList(QString name, QString data) =0;
    virtual void clearVirtualPorts() = 0;
    virtual void addVirtualPort(QString port) = 0;

    virtual void clearMidiRoutePresets() = 0;
    virtual void addMidiRoutePresets(MidiRoutePreset * item) = 0;
    virtual void addPreset() = 0;
    virtual QString getUniqueId() = 0;
    virtual void setActivePreset(int id)  = 0;
    virtual QString computerUuid() const = 0;
    virtual QList<MidiRoutePreset *> midiRoutePresets() const = 0;

private:
    /* data */
};

