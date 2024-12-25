//-define-file body GenHpp/UserDataConfig.cpp
//-define-file header GenHpp/UserDataConfig.h
//-only-file header //-
#pragma once
//-only-file body //-
//- #include "UserDataConfig.h"
#include <QSettings>
//- #include "MidiClientUtil.h"
#include "../UserConfigGenJson.h"
#include "../UserConfigParseJson.h"
//-only-file null
#include "MidiClientUtil.hpp"
//-only-file header
#include "../genPrpt/UserDataConfigPrivate.h"
#include <QJsonValue>
#include <QtCore/qjsonarray.h>
#include <QtCore/qjsondocument.h>
#include <QtCore/qjsonobject.h>

//-var {PRE} "UserDataConfig::"
class UserDataConfig : public UserDataConfigPrivate

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
    void clearVirtualPorts()
    //-only-file body
    {
        m_virtualInPorts.clear();
        emit virtualInPortsChanged();
    }

    //- {function} 0 1
    void addVirtualPort(QString port)
    //-only-file body
    {
        m_virtualInPorts.append(port);
        emit virtualInPortsChanged();
    }

    //- {function} 0 1
    void addDropdownList(QString name, QString data)
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
        return userConfigGenJson.getJson(this);
    }

    //- {function} 0 1
    void setActivePreset(int id)
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
    void addPreset()
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
