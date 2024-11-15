#pragma once
#include "UserDataConfigPrivate.h"
#include <QJsonValue>
#include <QtCore/qjsonarray.h>
#include <QtCore/qjsondocument.h>
#include <QtCore/qjsonobject.h>

class UserDataConfig : public UserDataConfigPrivate

{
    Q_OBJECT    
    QML_ELEMENT
public:
    explicit UserDataConfig(QObject *parent = nullptr);

    virtual ~UserDataConfig() { clearDropdownlists(); }

    void resetUserDataConfig(const QJsonValue &jsonData){
        QJsonDocument jsonDoc = QJsonDocument::fromVariant(jsonData.toVariant());        
        if (jsonDoc["uniqueId"].isString() && jsonDoc["uniqueId"].toString() != computerUuid()){
            setChanges(jsonDoc);
        }
    }


public slots:

private:
    void loadComputerUuid();
    void clearDropdownlists();
    void clearMidiRoutePreset();

    void  setChanges(QJsonDocument &jsonDoc);
    void updateVirtualInPorts(const QJsonArray &array);
    void updateDropdownlists(const QJsonArray &array);
    void updateMidiRoutePresets(const QJsonArray &array);
    void updateMidiControl(PresetMidiControl *control, const QJsonValue &value, PresetMidiControl::PresetMidiType type);


    QList<int> extractKeyboardSplits(const QJsonArray &array);
    MidiRoutePreset *createMidiRoutePreset(const QJsonValue &value);
    void updateEasyConfig(MidiRoutePreset *preset, const QJsonObject &easyConfig);
    EasyConfig *createEasyConfigEntry(const QString &key, const QJsonObject &value);
    EasyConfigRoute *createEasyConfigRoute(const QJsonObject &value);
    QStringList convertToQStringList(const QJsonArray &array);
    UserControl *createUserControl(const QJsonValue &userControlValue);
};
