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

    void resetUserDataConfig(const QJsonValue &jsonData);

    void clearVirtualPorts()
    {
        m_virtualInPorts.clear();
        emit virtualInPortsChanged();
    }

    void addVirtualPort(QString port)
    {
        m_virtualInPorts.append(port);
        emit virtualInPortsChanged();
    }

    void addDropdownList(QString name, QString data)
    {
        Dropdownlist *d = new Dropdownlist();
        d->setName(name);
        d->setData(data);
        m_dropdownlists.push_back(d);
        emit dropdownlistsChanged();
    }


    void clearDropdownlists();


public slots:
    QJsonObject getJson();
    void setActivePreset(int id)
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

    void addPreset()
    {
        MidiRoutePreset *p = new MidiRoutePreset(m_computerUuid);
        p->setName(QString{"Preset %0"}.arg(m_midiRoutePresets.size()));
        addMidiRoutePresets(p);
    }

    void deletePreset(int id)
    {
        delMidiRoutePresets(id);
    }

private:
    void loadComputerUuid();
};
