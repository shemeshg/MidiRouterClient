#include "UserDataConfig.h"
#include <QSettings>
#include "MidiClientUtil.h"
#include "UserConfigGenJson.h"
#include "../UserConfigParseJson.h"
     UserDataConfig::UserDataConfig(QObject *parent) 
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

     UserDataConfig::~UserDataConfig() 
    {
        clearDropdownlists();
    }

    void UserDataConfig::resetUserDataConfig(const QJsonValue &jsonData) 
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

    void UserDataConfig::clearVirtualPorts() 
    {
        m_virtualInPorts.clear();
        emit virtualInPortsChanged();
    }

    void UserDataConfig::addVirtualPort(QString port) 
    {
        m_virtualInPorts.append(port);
        emit virtualInPortsChanged();
    }

    void UserDataConfig::addDropdownList(QString name, QString data) 
    {
        Dropdownlist *d = new Dropdownlist();
        d->setName(name);
        d->setData(data);
        addDropdownlists(d);
    }




    QJsonObject UserDataConfig::getJson() 
    {
        UserConfigGenJson userConfigGenJson;
        return userConfigGenJson.getJson(this);
    }

    void UserDataConfig::setActivePreset(int id) 
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

    void UserDataConfig::addPreset() 
    {
        MidiRoutePreset *p = new MidiRoutePreset(m_computerUuid);
        p->setName(QString{"Preset %0"}.arg(m_midiRoutePresets.size()));
        addMidiRoutePresets(p);
    }

    void UserDataConfig::deletePreset(int id) 
    {
        delMidiRoutePresets(id);
    }

    void UserDataConfig::loadComputerUuid() 
    {
        QSettings settings;
        QString s = settings.value("computerUuid", "").toString();
        if (s.isEmpty()) {
            s = getUuId();
            settings.setValue("computerUuid", s);
        }
        m_computerUuid = s;
    }
