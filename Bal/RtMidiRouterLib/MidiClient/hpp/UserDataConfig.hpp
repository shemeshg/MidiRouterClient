//-define-file body GenHpp/UserDataConfig.cpp
//-define-file header GenHpp/UserDataConfig.h
//-only-file header //-
#pragma once
//- #include "UserDataConfigItf.h"
//- #include "../genPrpt/UserDataConfigPrivate.h"
//-only-file body //-
//- #include "UserDataConfig.h"
#include <QSettings>
//- #include "MidiClientUtil.h"
//- #include "UserConfigGenJson.h"
//- #include "UserConfigParseJson.h"
//-only-file null
#include "MidiClientUtil.hpp"
#include "UserConfigGenJson.hpp"
#include "UserDataConfigItf.hpp"
#include "UserConfigParseJson.hpp"
#include "../genPrpt/UserDataConfigPrivate.hpp"
//-only-file header

#include <QJsonValue>
#include <QtCore/qjsonarray.h>
#include <QtCore/qjsondocument.h>
#include <QtCore/qjsonobject.h>

//-var {PRE} "UserDataConfig::"
class UserDataConfig : public UserDataConfigPrivate, public UserDataConfigItf

{
    Q_OBJECT
    QML_ELEMENT
public:
    //- {function} 1 1
    explicit UserDataConfig(QObject *parent = nullptr)
    //-only-file body
        : UserDataConfigPrivate{parent}
    {

        loadComputerUuid();
        m_uniqueId = getUuId();

        clearDropdownlists();
        m_virtualInPorts = {};

        clearMidiRoutePresets();
        addPreset();
        setActivePreset(0);
    }

    //- {function} 0 1
    void clearDropdownlists()  override  
    //-only-file body
    {
        return UserDataConfigPrivate::clearDropdownlists();
    }



    //- {function} 0 1
    int activePresetID() const override
    //-only-file body
    {
        return UserDataConfigPrivate::activePresetID(); // Call the parent class's function
    }

    //- {function} 0 1
    QString computerUuid() const override
    //-only-file body
    {
        return UserDataConfigPrivate::computerUuid();
    }

    //- {function} 0 1
    QList<MidiRoutePreset*> midiRoutePresets() const override
    //-only-file body
    {
        return UserDataConfigPrivate::midiRoutePresets();
    }

    //- {function} 0 1
    void clearMidiRoutePresets() override
    //-only-file body
    {
        UserDataConfigPrivate::clearMidiRoutePresets();
    }

    //- {function} 0 1
    void addMidiRoutePresets(MidiRoutePreset * item) override
    //-only-file body
    {
        UserDataConfigPrivate::addMidiRoutePresets(item);
    }

    //- {function} 0 1
    void setActivePresetID(const int newActivePresetID) override
    //-only-file body
    {
        UserDataConfigPrivate::setActivePresetID(newActivePresetID);
    }

    //- {function} 0 1
    void setConnectedInPorts(const QStringList &newConnectedInPorts) override
    //-only-file body
    {
        UserDataConfigPrivate::setConnectedInPorts(newConnectedInPorts);
    }

    //- {function} 0 1
    void setConnectedOutPorts(const QStringList &newConnectedOutPorts) override
    //-only-file body
    {
        UserDataConfigPrivate::setConnectedOutPorts(newConnectedOutPorts);
    }

    //- {function} 1 1
    virtual ~UserDataConfig()
    //-only-file body
    {
        clearDropdownlists();
    }

    //- {function} 0 1
    void resetUserDataConfig(const QJsonValue &jsonData)
    //-only-file body
    {

        //QJsonDocument jsonDoc = QJsonDocument::fromVariant(jsonData.toVariant());
         //if (jsonDoc["uniqueId"].isString() && jsonDoc["uniqueId"].toString() != computerUuid()){

        UserConfigParseJson userConfigParseJson;
        QJsonObject j;
        if (jsonData.isArray()){
            QJsonArray a = jsonData.toArray();
            j = a[0].toObject();
        } else {

            j = jsonData.toObject();
        }
        userConfigParseJson.setChanges(this, j);

    }

    //- {function} 0 1
    void clearVirtualPorts() override
    //-only-file body
    {
        m_virtualInPorts.clear();
        emit virtualInPortsChanged();
    }

    //- {function} 0 1
    void addVirtualPort(QString port) override
    //-only-file body
    {
        m_virtualInPorts.append(port);
        emit virtualInPortsChanged();
    }

    //- {function} 0 1
    void addDropdownList(QString name, QString data) override
    //-only-file body
    {
        Dropdownlist *d = new Dropdownlist();
        d->setName(name);
        d->setData(data);
        addDropdownlists(d);
    }




    //-only-file header
public slots:
    //- {function} 0 1
    QJsonObject getJson()
    //-only-file body
    {
        UserConfigGenJson userConfigGenJson;
        return userConfigGenJson.getJson(
                 activePresetID(),
                 dropdownlists(),
                virtualInPorts(),
                midiRoutePresets());
    }

    //- {function} 0 1
    void setActivePreset(int id) override
    //-only-file body
    {
        setActivePresetID(id);        
        m_activePreset = m_midiRoutePresets.at(id);        
        m_activePreset->setIsEnabled(true);
        
        for (int i = 0; i < m_midiRoutePresets.size(); i++)
        {
            if (i != id)
            {
                m_midiRoutePresets.at(i)->setIsEnabled(false);
            }
        }
        emit activePresetChanged();
    }

    //- {function} 0 1
    void addPreset() override
    //-only-file body
    {
        MidiRoutePreset *p = new MidiRoutePreset(m_computerUuid);
        p->setName(QString{"Preset %0"}.arg(m_midiRoutePresets.size()));
        addMidiRoutePresets(p);
    }

    //- {function} 0 1
    void deletePreset(int id)
    //-only-file body
    {
        delMidiRoutePresets(id);
    }

    //-only-file header
private:
    //- {function} 0 1
    void loadComputerUuid()
    //-only-file body
    {
        QSettings settings;
        QString s = settings.value("computerUuid", "").toString();
        if (s.isEmpty()) {
            s = getUuId();
            settings.setValue("computerUuid", s);
        }
        m_computerUuid = s;
    }
    //-only-file header
};
