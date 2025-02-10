#pragma once
#include "UserDataConfigItf.h"
#include "../genPrpt/UserDataConfigPrivate.h"

#include <QJsonValue>
#include <QtCore/qjsonarray.h>
#include <QtCore/qjsondocument.h>
#include <QtCore/qjsonobject.h>

class UserDataConfig : public UserDataConfigPrivate, public UserDataConfigItf

{
    Q_OBJECT
    QML_ELEMENT
public:
#line 34 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserDataConfig.hpp"
    explicit UserDataConfig(QObject *parent = nullptr);
#line 51 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserDataConfig.hpp"
    void clearDropdownlists()  override;
#line 59 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserDataConfig.hpp"
    int activePresetID() const override;
#line 66 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserDataConfig.hpp"
    QString computerUuid() const override;
#line 73 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserDataConfig.hpp"
    QList<MidiRoutePreset*> midiRoutePresets() const override;
#line 80 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserDataConfig.hpp"
    void clearMidiRoutePresets() override;
#line 87 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserDataConfig.hpp"
    void addMidiRoutePresets(MidiRoutePreset * item) override;
#line 94 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserDataConfig.hpp"
    void setActivePresetID(const int newActivePresetID) override;
#line 101 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserDataConfig.hpp"
    void setConnectedInPorts(const QStringList &newConnectedInPorts) override;
#line 108 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserDataConfig.hpp"
    void setConnectedOutPorts(const QStringList &newConnectedOutPorts) override;
#line 115 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserDataConfig.hpp"
    virtual ~UserDataConfig();
#line 122 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserDataConfig.hpp"
    void resetUserDataConfig(const QJsonValue &jsonData);
#line 143 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserDataConfig.hpp"
    void clearVirtualPorts() override;
#line 151 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserDataConfig.hpp"
    void addVirtualPort(QString port) override;
#line 159 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserDataConfig.hpp"
    void addDropdownList(QString name, QString data) override;
public slots:
#line 174 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserDataConfig.hpp"
    QJsonObject getJson();
#line 186 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserDataConfig.hpp"
    void setActivePreset(int id) override;
#line 204 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserDataConfig.hpp"
    void addPreset() override;
#line 213 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserDataConfig.hpp"
    void deletePreset(int id);
#line 220 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserDataConfig.hpp"
    void addDropdownList();
#line 228 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserDataConfig.hpp"
    void delDropdownList(int id);
private:
#line 238 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserDataConfig.hpp"
    void loadComputerUuid();
};
