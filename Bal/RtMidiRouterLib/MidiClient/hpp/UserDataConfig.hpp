//-define-file body GenHpp/UserDataConfig.cpp
//-define-file header GenHpp/UserDataConfig.h
//-only-file header //-
#pragma once
//- #include "../genPrpt/UserDataConfigPrivate.h"
//-only-file body //-
//- #include "UserDataConfig.h"
#include <QSettings>
//- #include "MidiClientUtil.h"
//- #include "UserConfigParseJson.h"
//-only-file null
#include "../genPrpt/UserDataConfigPrivate.hpp"
#include "MidiClientUtil.hpp"
#include "UserConfigParseJson.hpp"
//-only-file header

#include <QJsonValue>
#include <QtCore/qjsonarray.h>
#include <QtCore/qjsondocument.h>
#include <QtCore/qjsonobject.h>

//-var {PRE} "UserDataConfig::"
class UserDataConfig : public UserDataConfigPrivate

{
    Q_OBJECT
    Q_PROPERTY(MidiRoutePreset * activePreset READ activePreset  NOTIFY activePresetChanged )
    QML_ELEMENT
public:

    MidiRoutePreset * activePreset() const{return m_activePreset;}

    //- {fn}
    explicit UserDataConfig(QObject *parent = nullptr)
        //-only-file body
        : UserDataConfigPrivate{parent} {

        m_uniqueId = getUuId();

        clearList<Dropdownlist *>();
        m_virtualInPorts = {};

        clearList<MidiRoutePreset *>();
        emit addPreset();
        emit setActivePreset(0, true);
    }



    //- {fn}
    void clearVirtualPorts()
    //-only-file body
    {
        m_virtualInPorts.clear();
        emit virtualInPortsChanged();
    }



    //- {fn}
    virtual ~UserDataConfig()
    //-only-file body
    {
        clearList<Dropdownlist *>();
    }

    //- {fn}
    void resetUserDataConfig(const QJsonValue &jsonData)
    //-only-file body
    {



        UserConfigParseJson userConfigParseJson;
        QJsonObject j;
        if (jsonData.isArray()) {
            QJsonArray a = jsonData.toArray();
            j = a[0].toObject();
        } else {
            j = jsonData.toObject();
        }


        //if (j["uniqueId"].toString() == uniqueId()){
        //    qDebug()<<"RETURN IGNORE";
        //    return;
        //}

        if (j["criticalError"].isBool() &&
            j["criticalError"].toBool()) {
            qDebug() << "Server JSON critical error";
            setCriticalErrorMsg("Server JSON critical error");
            return;
        }

        try {
            userConfigParseJson.setChanges(this, j);
        }
        catch (const std::runtime_error &e) {
            setCriticalErrorMsg("Server JSON critical error");
            qDebug() << "Server JSON critical error"<<e.what();
        }
        catch (...) {
            setCriticalErrorMsg("Server JSON critical error");
            qDebug() << "Server JSON critical error";
        }

    }

    //-only-file header
public slots:
    //- {fn}
    QJsonObject getJson()
    //-only-file body
    {
        openMidiControlOffInputsForEasyConfig();
        QJsonObject objUserConfig;
        objUserConfig["uniqueId"] = uniqueId();
        objUserConfig["_activePresetID"] = activePresetID();
        objUserConfig["dropdownlists"] = getDropdownList(dropdownlists());
        objUserConfig["virtualInPorts"] = getListToJsonAry(virtualInPorts());
        objUserConfig["midiRoutePresets"] = getJsonMidiRoutePresets(midiRoutePresets());
        return objUserConfig;

    }

    //- {fn}
    void setActivePreset(int id, bool setEnable)
    //-only-file body
    {
        setActivePresetID(id);

        for (int i = 0; i < midiRoutePresets().size(); i++) {
            if (i != id) {
                if (setEnable) {
                    midiRoutePresets().at(i)->setIsEnabled(false);
                }
            } else {

                m_activePreset = m_midiRoutePresets->at(i);
                if (setEnable) {
                    midiRoutePresets().at(i)->setIsEnabled(true);
                }
            }
        }

        emit activePresetChanged();
    }

    //- {fn}
    void addPreset()
    //-only-file body
    {        
        MidiRoutePreset *p =addListItem( new MidiRoutePreset());
        p->setName(QString{"Preset %0"}.arg(midiRoutePresets().size()));

    }

    //- {fn}
    void deletePreset(int idx)
    //-only-file body
    {
        delListItem<MidiRoutePreset *>(idx);
    }

    //- {fn}
    void addVirtualPort(QString port)
    //-only-file body
    {
        m_virtualInPorts.append(port);
        emit virtualInPortsChanged();
    }

    //- {fn}
    void delVirtualPort(int idx)
    //-only-file body
    {
        m_virtualInPorts.remove(idx);
        emit virtualInPortsChanged();
    }

    //- {fn}
    void addDropdownList(QString name, QString data)
    //-only-file body
    {
        Dropdownlist *d = new Dropdownlist(this);
        d->setName(name);
        d->setData(data);
        addListItem(d);
    }

    //- {fn}
    void delDropdownList(int idx)
    //-only-file body
    {
        delListItem<Dropdownlist *>(idx);
    }

    //-only-file header
signals:
    void activePresetChanged();
private:
    MidiRoutePreset * m_activePreset = nullptr;
    //- {fn}
    void openMidiControlOffInputsForEasyConfig()
    //-only-file body
    {
        QStringList midiControlOffNames;
        for (auto prst : midiRoutePresets()) {
            QString s;
            s = prst->midiControlOff()->portName();
            if (!s.isEmpty()) {
                midiControlOffNames.append(s);
            }
            s = prst->midiControlOn()->portName();
            if (!s.isEmpty()) {
                midiControlOffNames.append(s);
            }
        }
        for (const auto &inputStr : midiControlOffNames) {
            activePreset()->getInputOrCreateByName(inputStr);
        }
    }

    //- {fn}
    QJsonArray getDropdownList(QList<Dropdownlist *> dropdownlists)
    //-only-file body
    {
        QJsonArray ary;
        for (int i=0;i<dropdownlists.length();i++){
            auto itm = dropdownlists.at(i);
            QJsonObject obj;
            obj["name"] = itm->name();
            obj["data"] = itm->data();
            ary.append(obj);
        }
        return ary;
    }

    //- {fn}
    QJsonArray getListToJsonAry(const QStringList &sl)
    //-only-file body
    {
        QJsonArray ary;
        for (const auto &itm: sl){
            ary.append(itm);
        }
        return ary;
    }


    //- {fn}
    QJsonArray getJsonMidiRoutePresets(QList<MidiRoutePreset *> midiRoutePresets)
    //-only-file body
    {


        QJsonArray ary;
        auto presetControlEasyConfigs = getMidiPresetControlEasyConfigs( midiRoutePresets);
        for (int i=0;i<midiRoutePresets.length();i++){
            const auto itm = midiRoutePresets.at(i);

            ary.append(itm->getJson(presetControlEasyConfigs));
        }
        return ary;
    }

    //- {fn}
    QList<MidiPresetControlEasyConfig> getMidiPresetControlEasyConfigs(QList<MidiRoutePreset *> midiRoutePresets)
    //-only-file body
    {
        QList<MidiPresetControlEasyConfig> midiPresetControlEasyConfigs;
        for (int i=0;i<midiRoutePresets.length();i++){
            const auto itm = midiRoutePresets.at(i);
            MidiPresetControlEasyConfig mOff;
            mOff.pmc = itm->midiControlOff();
            mOff.isMidiControlOn = false;
            midiPresetControlEasyConfigs.append(mOff);
            MidiPresetControlEasyConfig mOn;
            mOn.pmc = itm->midiControlOn();
            mOn.isMidiControlOn = true;
            midiPresetControlEasyConfigs.append(mOn);

        }
        return midiPresetControlEasyConfigs;
    }

    //-only-file header
};
