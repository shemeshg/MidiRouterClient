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
    explicit UserDataConfig(QObject *parent = nullptr);
    void clearDropdownlists()  override;
    int activePresetID() const override;
    QString computerUuid() const override;
    QList<MidiRoutePreset*> midiRoutePresets() const override;
    void clearMidiRoutePresets() override;
    void addMidiRoutePresets(MidiRoutePreset * item) override;
    void setActivePresetID(const int newActivePresetID) override;
    void setConnectedInPorts(const QStringList &newConnectedInPorts) override;
    void setConnectedOutPorts(const QStringList &newConnectedOutPorts) override;
    virtual ~UserDataConfig();
    void resetUserDataConfig(const QJsonValue &jsonData);
    void clearVirtualPorts() override;
    void addVirtualPort(QString port) override;
    void addDropdownList(QString name, QString data) override;
public slots:
    QJsonObject getJson();
    void setActivePreset(int id) override;
    void addPreset() override;
    void deletePreset(int id);
private:
    void loadComputerUuid();
};
