//-define-file body GenHpp/MidiRoutePreset.cpp
//-define-file header GenHpp/MidiRoutePreset.h
//-only-file header //-
#pragma once
//- #include "../genPrpt/MidiRoutePresetPrivate.h"
//- #include "MidiClientUtil.h"
//-only-file body //-
//- #include "MidiRoutePreset.h"
//-only-file null
#include "MidiClientUtil.hpp"
#include "../genPrpt/MidiRoutePresetPrivate.hpp"
//-only-file header


//-var {PRE} "MidiRoutePreset::"
class MidiRoutePreset : public MidiRoutePresetPrivate

{
    Q_OBJECT
    QML_ELEMENT
public:
    //- {function} 1 1
    explicit MidiRoutePreset(QObject *parent = nullptr)
        //-only-file body
        : MidiRoutePresetPrivate{parent}{

        setUuid(getUuId());

        clearList<UserControl *>();

    };



    //- {fn}
    void recreateEasyConfig(QList<MidiPresetControlEasyConfig> &midiPresetControlEasyConfigs,
                            const QString &presetUuid)
    //-only-file body
    {

        for (int i=midiRouteInputs().length()-1;i>=0;i--){
            auto input = midiRouteInputs().at(i);
            input->clearEasyConfigMidiRouterChains();
        }


        for (int i=midiRouteInputs().length()-1;i>=0;i--){
            auto input = midiRouteInputs().at(i);
            input->addMonitorEasyConfigIfRequired();
            input->addMidiPresetControlEasyConfigsIfRequired(midiPresetControlEasyConfigs, presetUuid);

            getInputOrCreateByName(input->midiInputName())->createEasyConfigChains(input->easyConfig());

        }

    }

    //- {fn}
    QJsonObject getJson(QList<MidiPresetControlEasyConfig> & presetControlEasyConfigs)
    //-only-file body
    {
        QJsonObject obj;
        qDebug()<<"For PRESET "<<name();
        for (auto in: midiRouteInputs()){
            qDebug()<<"For PRESET "<<name() <<" input "<<
                in->midiInputName();
        }

        recreateEasyConfig(presetControlEasyConfigs, uuid());
        obj["name"] = name();
        obj["uuid"] = uuid();
        obj["isEnabled"] = isEnabled();
        obj["midiControlOn"] = midiControlOn()->getJson();
        obj["midiControlOff"] = midiControlOff()->getJson();
        obj["midiRouteInputs"] = getJsonMidiRouteInputs();
        obj["userControls"] = getJsonUserControls();
        return obj;
    }




//-only-file header
public slots:
//- {fn}
MidiRouteInput* getInputOrCreateByName(QString midiInputName)
//-only-file body
{
    MidiRouteInput * input = getInputByName(midiInputName);
    if (input){
        return input;
    }
    MidiRouteInput *newInput = new MidiRouteInput(this);
    newInput->setMidiInputName(midiInputName);
    addListItem(newInput);
    return newInput;
}

//- {fn}
void addUserControl()
//-only-file body
{
    auto uc  = new UserControl(this);
    uc->setDescription("Description");
    uc->setMaxVal(127);
    uc->setMinVal(0);
    uc->setDropdownListId(-1);
    uc->setEventType(UserControl::EventType::CC);
    uc->setChannelId(1);
    uc->setCcId(0);
    uc->setNrpnControl(0);
    uc->setInputVal(0);
    uc->setIs64Mode(false);
    uc->setIsShowDropdown(false);
    uc->setIsSendOnPresetChange(false);
    addListItem(uc);
}


//- {fn}
void delUserControl(int id)
//-only-file body
{
    delListItem<UserControl*>(id);
}


//-only-file header
signals:


private:

//- {fn}
QJsonArray getJsonMidiRouteInputs()
//-only-file body
{
    QJsonArray obj;
    for (const auto &itm: midiRouteInputs()){
        obj.append( itm->getJson());
    }
    return obj;
}


//- {fn}
MidiRouteInput * getInputByName(QString midiInputName)
//-only-file body
{
    qDebug()<<" SIZE OF Unputs IS ";
    qDebug()<<" SIZE OF Unputs IS "<< midiRouteInputs().size();
    qDebug()<<" SIZE OF Unputs IS "<< (*m_midiRouteInputs).size();

    for (MidiRouteInput *input : midiRouteInputs()) {
        if (input->midiInputName() == midiInputName) {
            return input;
        }
    }

    return nullptr;
}

//- {fn}
QJsonArray getJsonUserControls()
//-only-file body
{
    QJsonArray ary;
    for (int i=0;i<userControls().length();i++){

        ary.append(userControls().at(i)->getJson());

    }
    return ary;
}

//-only-file header
};
