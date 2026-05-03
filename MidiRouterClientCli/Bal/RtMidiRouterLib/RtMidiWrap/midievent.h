#pragma once
#include "common.h"

namespace RtMidiWrap {
enum EVENT_STATUS { OK, DELETED, DEFFERED };

enum DEFFERED_EVENT_TYPE {
    IN_SPP,
    IN_BAR,
    AT_SPP,
    AT_BAR,
    QUANTIZE_SPP,
    QUANTIZE_BAR
};

class MidiEvent : public CommonStatic {
public:
    MidiEvent(double deltatime, std::vector<BYTE> &data, int portNumber,
              std::string &portName);

    EVENT_STATUS eventStatus = EVENT_STATUS::OK;

    int cc14bitLsb = 0;

    std::vector<BYTE> &data;
    double deltatime;

    int portNumber;
    std::string &portName;

    DEFFERED_EVENT_TYPE defferedEventType = DEFFERED_EVENT_TYPE::IN_SPP;
    double defferedSubmittedAt = 0;
    double defferedTo = 0;
    int defferedFilterChainId = 0;
    int defferedFilterId = 0;

    int nrpnControl = -1;
    int nrpnData = -1;
    bool processNrpn = false;
    bool passedThrouFilter = false;

    void resetNrpnParams();

    const bool hasNrpn() const;
    const MIDI_MSG_TYPE msgtype() const;
    const int channel() const;
    const std::string commandStr() const;
    const int command() const;
    const int data1() const;
    const int data2() const;
};
} // namespace RtMidiWrap
