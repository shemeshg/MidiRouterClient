#pragma once
#include "common.h"




namespace RtMidiWrap {
enum EVENT_STATUS {
    OK,
    DELETED,
    DEFFERED
};

enum DEFFERED_EVENT_TYPE {
    IN_SPP,
    IN_BAR,
    AT_SPP,
    AT_BAR,
    QUANTIZE_SPP,
    QUANTIZE_BAR
};

class MidiEvent:public CommonStatic
{
public:
    MidiEvent(double deltatime, std::vector< BYTE> &data,int portNumber, std::string &portName);

    EVENT_STATUS eventStatus = EVENT_STATUS::OK;

    int cc14bitLsb = 0;

    std::vector< BYTE> &data;
    double deltatime;
    const int channel() const {
        int i_channel = 0;
        if (msgtype() == MIDI_MSG_TYPE::MIDI_CHANNEL_MESSAGES) {
            constexpr int channelMask = 0xf;
            i_channel = (data[0] & channelMask) + 1;
        }
        return i_channel;
    }


    const std::string commandStr() const {
       if (msgtype() == MIDI_MSG_TYPE::MIDI_CHANNEL_MESSAGES &&
            mapMIDI_CHANNEL_MESSAGES.count(command()) > 0
            ) {

            return mapMIDI_CHANNEL_MESSAGES.at(command());
       } else if (msgtype() == MIDI_MSG_TYPE::MIDI_SYSTEM_MESSAGES &&
                  mapMIDI_SYSTEM_MESSAGES.count(command()) > 0
                  )  {
           return mapMIDI_SYSTEM_MESSAGES.at(command());
       } else {
           return "";
       }
    }
    const int command() const{
        int l_command = 0;
        if (msgtype() == MIDI_MSG_TYPE::MIDI_CHANNEL_MESSAGES) {
            l_command = data[0] >> 4;
        } else if (msgtype() == MIDI_MSG_TYPE::MIDI_SYSTEM_MESSAGES)  {
            l_command = data[0];
        }
        return l_command;
    }

    const int data1() const {
        int l_data1 =0;
        if (msgtype() == MIDI_MSG_TYPE::MIDI_CHANNEL_MESSAGES) {
            if (data.size() >1){l_data1 = data[1];}
        }
        return l_data1;
    }

    const int data2() const {
        int l_data2 =0;
        if (msgtype() == MIDI_MSG_TYPE::MIDI_CHANNEL_MESSAGES) {
            if (data.size() >2){l_data2 = data[2];}
        }
        return l_data2;
    }


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
    void resetNrpnParams(){
        nrpnControl = -1;
        nrpnData = -1;
        processNrpn = false;
    }

    bool hasNrpn(){
        return nrpnControl != -1;
    }

    const MIDI_MSG_TYPE msgtype() const{
        if (eventStatus == EVENT_STATUS::DELETED) {
            return MIDI_MSG_TYPE::DELETED;
        }
        constexpr int sysMsgLowBound=240;
        if (data[0]<sysMsgLowBound){
            return MIDI_MSG_TYPE::MIDI_CHANNEL_MESSAGES;
        } else {
            return MIDI_MSG_TYPE::MIDI_SYSTEM_MESSAGES;
        }

    }
};
}

