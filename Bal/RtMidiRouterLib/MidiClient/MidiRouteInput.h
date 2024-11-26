

#pragma once
#include "EasyConfig.h"
#include "MidiRouteInputPrivate.h"

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
            midiRouterChain->setName("EasyConfig");
            midiRouterChain->setIsEasyConfig(true);

            auto const toDestinationName = easyConfigRoute->toDestinationName();
            if (toDestinationName.isEmpty()) {
                return;
            }
            bool isAllDefault = true;
            QString channelFilter = "[[0, 16, 0]]";
            if (easyConfigRoute->fromChannel() != -1) {
                isAllDefault = false;
                channelFilter = QString{"[[{0}, {1}]]"}
                                    .arg(easyConfigRoute->fromChannel())
                                    .arg(easyConfigRoute->toChannel());
            }
            QString eventFilter = "[[0, 16, 0]]";
            if (easyConfigRoute->fromSelectedMidiEventTypeId() != 0) {
                isAllDefault = false;
                if (easyConfigRoute->fromSelectedMidiEventTypeId() ==
                        easyConfigRoute->toSelectedMidiEventTypeId() &&
                    easyConfigRoute->toSelectedMidiEventTypeId() ==
                                                                                                                          (int)EasyConfig::DropdownMidiEventTypeEnum::noteOnOf) {
                    eventFilter = QString{"[[{0}], [{1}]]"}
                                      .arg((int)EasyConfig::EventTypes::noteoff)
                                      .arg((int)EasyConfig::EventTypes::noteon);
                } else {
                    eventFilter =
                        QString{"[[{0}], [{1}]]"}
                                      .arg((int)easyConfig->dropdownMidiEventTypeEnum
                                               [(EasyConfig::DropdownMidiEventTypeEnum)
                                                easyConfigRoute->fromSelectedMidiEventTypeId()])
                                      .arg((int)easyConfig->dropdownMidiEventTypeEnum
                                               [(EasyConfig::DropdownMidiEventTypeEnum)
                                                easyConfigRoute->toSelectedMidiEventTypeId()]);
                }
            }

            QString data1Filter = "[[0, 127, 0]]";
            QString data2Filter = "[[0, 127, 0]]";
            int splitRangeId = easyConfigRoute->splitRangeId();
            if (splitRangeId != -1) {

                QList<int> keyboardSplits = easyConfig->keyboardSplits();
                if (!keyboardSplits.contains(8)) {
                    keyboardSplits.append(8);
                    splitRangeId++;
                }
                if (!keyboardSplits.contains(98)) {
                    keyboardSplits.append(98);
                    splitRangeId++;
                }
                sortUniq(keyboardSplits);
                int fromKey = keyboardSplits.at(splitRangeId);
                int toKey = keyboardSplits.at(splitRangeId + 1);
                data1Filter = QString{"[[{0}, {1}, {2}]]"}.arg(
                    fromKey, toKey, fromKey + easyConfigRoute->transpose());
            } else {
                data1Filter =
                    QString{"[[0, 127, {0}]]"}.arg(0 + easyConfigRoute->transpose());
            }

            if (easyConfigRoute->fromData1() != -1) {
                if (easyConfigRoute->toData1() == -1) {
                    data1Filter = QString{"[[{0}]]"}.arg(easyConfigRoute->fromData1());
                } else {
                    data1Filter = QString{"[[{0}, {1}]]"}
                                      .arg(easyConfigRoute->fromData1())
                                      .arg(easyConfigRoute->toData1());
                }
            }
            if (easyConfigRoute->fromData1() != -1 &&
                easyConfigRoute->toData1() != -1) {
                data1Filter = QString{"[[{0} {1}]]"}
                                  .arg(easyConfigRoute->fromData1())
                                  .arg(easyConfigRoute->toData1());
            }
            if (easyConfigRoute->fromData1() != -1 ||
                easyConfigRoute->toData1() != -1) {
                data2Filter = QString{"[[{0}, {1}, {2}, {3}]]"}
                                  .arg(easyConfigRoute->fromCcOrNrpnStart())
                                  .arg(easyConfigRoute->fromCcOrNrpnEnd())
                                  .arg(easyConfigRoute->toCcOrNrpnStart())
                                  .arg(easyConfigRoute->toCcOrNrpnEnd());
            }

            if (!isAllDefault) {
                midiRouterChain->addFilterAndTransform(
                    "EasyConfig",
                    FilterAndTransform::ConditionAction::
                    DELETE_IF_NOT_MET_CONDITION,
                    channelFilter, eventFilter, data1Filter, data2Filter
                    );
            }

            midiRouterChain->addFilterMidiDestination(toDestinationName);
            addMidiRouterChains(midiRouterChain);
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
    void sortUniq(QList<int> &list) {
        QSet<int> set(list.begin(), list.end());
        list = QList<int>(set.begin(), set.end());
        std::sort(list.begin(), list.end()); // Sort the list
    }
};
