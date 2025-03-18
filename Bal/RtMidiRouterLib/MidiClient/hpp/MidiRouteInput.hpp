//-define-file body GenHpp/MidiRouteInput.cpp
//-define-file header GenHpp/MidiRouteInput.h
//-only-file header //-
#pragma once
//-only-file body //-
//- #include "MidiRouteInput.h"

//- {include-header}
#include "../genPrpt/MidiRouteInputPrivate.hpp" //- #include "../genPrpt/MidiRouteInputPrivate.h"
//- {include-header}
#include "MidiClientUtil.hpp" //- #include "MidiClientUtil.h"
//-only-file header




//-var {PRE} "MidiRouteInput::"
class MidiRouteInput : public MidiRouteInputPrivate

{
    Q_OBJECT
    QML_ELEMENT
public:
    //- {function} 1 1
    explicit MidiRouteInput(QObject *parent)
        //-only-file body
        : MidiRouteInputPrivate{parent} {
        clearList<MidiRouteInputCc14bit *>();
        clearMidiRouterChains();

        setIgnoreTypesMidiSysex(true);
        setIgnoreTypesMidiTime( true);
        setIgnoreTypesMidiSense(true);
        setMidiRouteClockTimeSig( 4);
        setMidiRouteClockTimeSigDivBy(4);
        setMidiRouteClockFromSppPos(0);
        m_monitor = new Monitor(this);
        m_easyConfig = new EasyConfig(this);
        setUuid(getUuId());
    };

    //- {function} 1 1
    virtual ~MidiRouteInput()
    //-only-file body
    {
    }

    //- {fn}
    QJsonObject genJson()
    //-only-file body
    {
        QJsonObject obj;
        obj["uuid"] = uuid();
        obj["midiInputName"] = midiInputName();
        obj["ignoreTypes"] = getJsonIgnoreTypes();
        obj["midiRouteClock"] = getJsonMidiRouteClock();
        obj["cc14bitAry"] = getJsonCc14bitAry();
        obj["monitor"] = monitor()->genJson();
        obj["easyConfig"] = easyConfig()->genJson();

        obj["midiRouterChains"] = getJsonMidiRouterChains();

        return obj;
    }

    //- {fn}
    void clearEasyConfigMidiRouterChains()
    //-only-file body
    {
        for (int i = midiRouterChains().size() - 1; i >= 0; --i) {
            if (midiRouterChains().at(i)->isEasyConfig()) {
                delListItem<MidiRouterChain *>(i);
            }
        }
    }

    //- {fn}
    void createEasyConfigChains(EasyConfig *easyConfig)
    //-only-file body
    {
        for (int i=0;i<easyConfig->easyConfigRoutes().length();i++){
            auto easyConfigRoute = easyConfig->easyConfigRoutes().at(i);
            MidiRouterChain *midiRouterChain = new MidiRouterChain(this);
            midiRouterChain->setEasyConfigChain(easyConfig, easyConfigRoute);


            addListItem(midiRouterChain);
        }
    }

    //- {fn}
    void addMonitorEasyConfigIfRequired()
    //-only-file body
    {
        if (monitor()->isMonitored()){
            MidiRouterChain *midiRouterChain = new MidiRouterChain(this);
            midiRouterChain->addEasyConfigMonitor();
            addListItem(midiRouterChain);
        }
    }

    //- {fn}
    void addMidiPresetControlEasyConfigsIfRequired(
        QList<MidiPresetControlEasyConfig> &midiPresetControlEasyConfigs,
        const QString &presetUuid)
    //-only-file body
    {
        for (int i=0;i<midiPresetControlEasyConfigs.length();i++){
            auto m = midiPresetControlEasyConfigs.at(i);
            if (m.pmc->portName() == midiInputName()){
                MidiRouterChain *midiRouterChain = new MidiRouterChain(this);
                midiRouterChain->addEasyConfigPresetFilter(m);
                midiRouterChain->addEasyConfigPresetLogOnOff((int)m.pmc->presetMidiType(), presetUuid);
                addListItem(midiRouterChain);


            }
        }
    }



    //- {fn}
    void clearMidiRouterChains()
    //-only-file body
    {
        for (MidiRouterChain *item : midiRouterChains()) {
            delete item;
        }
        // Clear the outer list

        midiRouterChains().clear();
        emit midiRouterChainsChanged();
    }

    //-only-file header
public slots:
    //- {fn}
    void addMidiRouterChain(const QString name)
    //-only-file body
    {
        MidiRouterChain *midiRouterChain = new MidiRouterChain(this);
        midiRouterChain->setName(name);
        addListItem(midiRouterChain);
    }

    //- {fn}
    void delMidiRouterChain(const int idx)
    //-only-file body
    {
        delListItem<MidiRouterChain *>(idx);
    }
    //- {fn}
    void clear14BitCc()
    //-only-file body
    {
        clearList<MidiRouteInputCc14bit *>();
    }

    //- {fn}
    void add14BitCc(int channel, int cc)
    //-only-file body
    {
        MidiRouteInputCc14bit *item = new MidiRouteInputCc14bit(this);
        item->setChannel(channel);
        item->setCc(cc);
        addListItem(item);
    }

    //-only-file header
private:

    //- {fn}
    QJsonObject getJsonIgnoreTypes()
    //-only-file body
    {
        QJsonObject ignoreTypes;
        ignoreTypes["midiSysex"] = ignoreTypesMidiSysex();
        ignoreTypes["midiTime"] = ignoreTypesMidiTime();
        ignoreTypes["midiSense"] = ignoreTypesMidiSense();

        return ignoreTypes;
    }

    //- {fn}
    QJsonObject getJsonMidiRouteClock()
    //-only-file body
    {
        QJsonObject midiRouteClock;
        midiRouteClock["timeSig"] = midiRouteClockTimeSig();
        midiRouteClock["timeSigDivBy"] = midiRouteClockTimeSigDivBy();
        midiRouteClock["fromSppPos"] = midiRouteClockFromSppPos();
        midiRouteClock["propegateInputs"] = getListToJMidiInsonAry(midiRouteClockPropegateInputs());

        return midiRouteClock;
    }

    //- {fn}
    QJsonArray getListToJMidiInsonAry(const QStringList &sl)
    //-only-file body
    {
        QJsonArray ary;
        for (const auto &itm: sl){
            QJsonObject obj;
            obj["midiInputName"] = itm;
            ary.append(obj);
        }
        return ary;
    }

    //- {fn}
    QJsonArray getJsonCc14bitAry()
    //-only-file body
    {
        QJsonArray cc14bitAry;
        for (int i=0;i< midiRouteInputCc14bit().length();i++){
            auto cc14bit = midiRouteInputCc14bit().at(i);
            QJsonObject cc14bitObj;
            cc14bitObj["channel"] = cc14bit->channel();
            cc14bitObj["cc"] = cc14bit->cc();
            cc14bitAry.append(cc14bitObj);
        }

        return cc14bitAry;
    }

    //- {fn}
    QJsonArray getJsonMidiRouterChains()
    //-only-file body
    {
        QJsonArray ary;
        for (int i=0;i< midiRouterChains().length();i++){
            auto midiRouterChain = midiRouterChains().at(i);
            ary.append(midiRouterChain->genJson());
        }
        return ary;
    }

    //-only-file header
};
