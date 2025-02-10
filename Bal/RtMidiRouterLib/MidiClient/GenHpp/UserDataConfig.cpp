#line 8 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserDataConfig.hpp"
#include "UserDataConfig.h"
#include <QSettings>
#include "MidiClientUtil.h"
#include "UserConfigGenJson.h"
#include "UserConfigParseJson.h"
   UserDataConfig::UserDataConfig(QObject * parent) 
#line 36 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserDataConfig.hpp"
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

    void UserDataConfig::clearDropdownlists()
#line 53 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserDataConfig.hpp"
    {
        return UserDataConfigPrivate::clearDropdownlists();
    }


    int UserDataConfig::activePresetID() const
#line 61 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserDataConfig.hpp"
    {
        return UserDataConfigPrivate::activePresetID(); // Call the parent class's function
    }

    QString UserDataConfig::computerUuid() const
#line 68 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserDataConfig.hpp"
    {
        return UserDataConfigPrivate::computerUuid();
    }

    QList<MidiRoutePreset*> UserDataConfig::midiRoutePresets() const
#line 75 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserDataConfig.hpp"
    {
        return UserDataConfigPrivate::midiRoutePresets();
    }

    void UserDataConfig::clearMidiRoutePresets()
#line 82 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserDataConfig.hpp"
    {
        UserDataConfigPrivate::clearMidiRoutePresets();
    }

    void UserDataConfig::addMidiRoutePresets(MidiRoutePreset *  item)
#line 89 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserDataConfig.hpp"
    {
        UserDataConfigPrivate::addMidiRoutePresets(item);
    }

    void UserDataConfig::setActivePresetID(const int newActivePresetID)
#line 96 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserDataConfig.hpp"
    {
        UserDataConfigPrivate::setActivePresetID(newActivePresetID);
    }

    void UserDataConfig::setConnectedInPorts(const QStringList &newConnectedInPorts)
#line 103 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserDataConfig.hpp"
    {
        UserDataConfigPrivate::setConnectedInPorts(newConnectedInPorts);
    }

    void UserDataConfig::setConnectedOutPorts(const QStringList &newConnectedOutPorts)
#line 110 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserDataConfig.hpp"
    {
        UserDataConfigPrivate::setConnectedOutPorts(newConnectedOutPorts);
    }

   UserDataConfig::~UserDataConfig() 
#line 117 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserDataConfig.hpp"
    {
        clearDropdownlists();
    }

    void UserDataConfig::resetUserDataConfig(const QJsonValue &jsonData) 
#line 124 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserDataConfig.hpp"
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
#line 145 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserDataConfig.hpp"
    {
        m_virtualInPorts.clear();
        emit virtualInPortsChanged();
    }

    void UserDataConfig::addVirtualPort(QString port)
#line 153 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserDataConfig.hpp"
    {
        m_virtualInPorts.append(port);
        emit virtualInPortsChanged();
    }

    void UserDataConfig::addDropdownList(QString name, QString data)
#line 161 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserDataConfig.hpp"
    {
        Dropdownlist *d = new Dropdownlist();
        d->setName(name);
        d->setData(data);
        addDropdownlists(d);
    }




    QJsonObject UserDataConfig::getJson() 
#line 176 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserDataConfig.hpp"
    {
        UserConfigGenJson userConfigGenJson;
        return userConfigGenJson.getJson(
                 activePresetID(),
                 dropdownlists(),
                virtualInPorts(),
                midiRoutePresets());
    }

    void UserDataConfig::setActivePreset(int id)
#line 188 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserDataConfig.hpp"
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
#line 206 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserDataConfig.hpp"
    {
        MidiRoutePreset *p = new MidiRoutePreset(m_computerUuid);
        p->setName(QString{"Preset %0"}.arg(m_midiRoutePresets.size()));
        addMidiRoutePresets(p);
    }

    void UserDataConfig::deletePreset(int id) 
#line 215 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserDataConfig.hpp"
    {
        delMidiRoutePresets(id);
    }

    void UserDataConfig::addDropdownList() 
#line 222 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserDataConfig.hpp"
    {
        auto d = new Dropdownlist();
        addDropdownlists(d);
    }

    void UserDataConfig::delDropdownList(int id) 
#line 230 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserDataConfig.hpp"
    {
        delDropdownlists(id);
    }


    void UserDataConfig::loadComputerUuid() 
#line 240 "/Volumes/RAM_Disk_4G/MidiRouterClient/Bal/RtMidiRouterLib/MidiClient/hpp/UserDataConfig.hpp"
    {
        QSettings settings;
        QString s = settings.value("computerUuid", "").toString();
        if (s.isEmpty()) {
            s = getUuId();
            settings.setValue("computerUuid", s);
        }
        m_computerUuid = s;
    }
