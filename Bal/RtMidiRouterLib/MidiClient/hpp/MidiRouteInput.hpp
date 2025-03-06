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
    explicit MidiRouteInput(QObject *parent = nullptr)
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


        setUuid(getUuId());
    };

    //- {function} 1 1
    virtual ~MidiRouteInput()
    //-only-file body
    {
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
            MidiRouterChain *midiRouterChain = new MidiRouterChain();
            midiRouterChain->setEasyConfigChain(easyConfig, easyConfigRoute);


            addListItem(midiRouterChain);
        }
    }

    //- {fn}
    void addMonitorEasyConfigIfRequired()
    //-only-file body
    {
        if (monitor()->isMonitored()){
            MidiRouterChain *midiRouterChain = new MidiRouterChain();
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
                MidiRouterChain *midiRouterChain = new MidiRouterChain();
                midiRouterChain->addEasyConfigPresetFilter(m);
                midiRouterChain->addEasyConfigPresetLogOnOff(m.isMidiControlOn, presetUuid);
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
        MidiRouterChain *midiRouterChain = new MidiRouterChain();
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
        MidiRouteInputCc14bit *item = new MidiRouteInputCc14bit();
        item->setChannel(channel);
        item->setCc(cc);
        addListItem(item);
    }

    //-only-file header
private:

};
