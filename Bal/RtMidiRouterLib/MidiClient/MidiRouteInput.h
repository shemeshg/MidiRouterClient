

#pragma once
#include "EasyConfig.h"
#include "MidiRouteInputPrivate.h"
#include "MidiPresetControlEasyConfig.h"

class MidiRouteInput : public MidiRouteInputPrivate

{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit MidiRouteInput(QObject *parent = nullptr)
        : MidiRouteInputPrivate{parent} {
        clearMidiRouteInputCc14bit();
        clearMidiRouterChains();
    };

    void addMidiRouteInputCc14bit(MidiRouteInputCc14bit *entry) {
        m_midiRouteInputCc14bit.push_back(entry);
        emit midiRouteInputCc14bitChanged();
    }

    void clearMidiRouteInputCc14bit() {
        for (MidiRouteInputCc14bit *item : m_midiRouteInputCc14bit) {
            delete item;
        }
        // Clear the outer list

        m_midiRouteInputCc14bit.clear();
        emit midiRouteInputCc14bitChanged();
    }

    void addMidiRouterChains(MidiRouterChain *entry) {
        m_midiRouterChains.push_back(entry);
        emit midiRouterChainsChanged();
    }

    void clearEasyConfigMidiRouterChains() {
        for (int i = m_midiRouterChains.size() - 1; i >= 0; --i) {
            if (m_midiRouterChains[i]->isEasyConfig()) {
                delete m_midiRouterChains[i];
                m_midiRouterChains.removeAt(i);
            }
        }
        emit midiRouterChainsChanged();
    }

    void createEasyConfigChains(EasyConfig *easyConfig) {
        for (auto easyConfigRoute : easyConfig->easyConfigRoutes()) {
            MidiRouterChain *midiRouterChain = new MidiRouterChain();
            midiRouterChain->setEasyConfigChain(easyConfig, easyConfigRoute);


            addMidiRouterChains(midiRouterChain);
        }
    }

    void addMonitorEasyConfigIfRequired(){
        if (monitor()->isMonitored()){
            MidiRouterChain *midiRouterChain = new MidiRouterChain();
            midiRouterChain->addEasyConfigMonitor();
            addMidiRouterChains(midiRouterChain);
        }
    }

    void addMidiPresetControlEasyConfigsIfRequired(QList<MidiPresetControlEasyConfig> &midiPresetControlEasyConfigs){
        for (const auto &m: midiPresetControlEasyConfigs){
            if (m.pmc->portName() == midiInputName()){
                MidiRouterChain *midiRouterChain = new MidiRouterChain();
                midiRouterChain->setName("EasyConfig");
                midiRouterChain->setIsEasyConfig(true);
                EasyConfigRoute ecr{};
                ecr.setFromChannel(m.pmc->channel());
                ecr.setToChannel(m.pmc->channel());
                ecr.setFromSelectedMidiEventTypeId(m.pmc->eventTypeId());
                ecr.setToSelectedMidiEventTypeId(m.pmc->eventTypeId());
                ecr.setFromData1(m.pmc->data1());
                if (m.pmc->data2()!= -1){
                    ecr.setFromCcOrNrpnStart(m.pmc->data2());
                    ecr.setFromCcOrNrpnEnd(m.pmc->data2());
                    ecr.setToCcOrNrpnStart(m.pmc->data2());
                    ecr.setToCcOrNrpnEnd(m.pmc->data2());
                }
                auto easyConfigRouteFilter = ecr.getEasyConfigRouteFilter({});

                if (!easyConfigRouteFilter.isAllDefault) {
                    midiRouterChain->addFilterAndTransform(
                        "EasyConfig",
                        FilterAndTransform::ConditionAction::
                        DELETE_IF_NOT_MET_CONDITION,
                        easyConfigRouteFilter.channelFilter,
                        easyConfigRouteFilter.eventFilter,
                        easyConfigRouteFilter.data1Filter,
                        easyConfigRouteFilter.data2Filter
                        );

                }

                ADD Preset change
                addMidiRouterChains(midiRouterChain);
            }
        }
    }

    void clearMidiRouterChains() {
        for (MidiRouterChain *item : m_midiRouterChains) {
            delete item;
        }
        // Clear the outer list

        m_midiRouterChains.clear();
        emit midiRouterChainsChanged();
    }

public slots:

private:

};
