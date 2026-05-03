#include "midievent.h"
//#include "common.h"
namespace RtMidiWrap {



MidiEvent::MidiEvent(double deltatime, std::vector< BYTE> &data,
                     int portNumber, std::string &portName):data(data),deltatime(deltatime),portNumber(portNumber), portName(portName){
}

const int MidiEvent::channel() const {
    int i_channel = 0;
    if (msgtype() == MIDI_MSG_TYPE::MIDI_CHANNEL_MESSAGES) {
        constexpr int channelMask = 0xf;
        i_channel = (data[0] & channelMask) + 1;
    }
    return i_channel;
}

const std::string MidiEvent::commandStr() const {
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

const int MidiEvent::command() const{
    int l_command = 0;
    if (msgtype() == MIDI_MSG_TYPE::MIDI_CHANNEL_MESSAGES) {
        l_command = data[0] >> 4;
    } else if (msgtype() == MIDI_MSG_TYPE::MIDI_SYSTEM_MESSAGES)  {
        l_command = data[0];
    }
    return l_command;
}

const int MidiEvent::data1() const {
    int l_data1 =0;
    if (msgtype() == MIDI_MSG_TYPE::MIDI_CHANNEL_MESSAGES) {
        if (data.size() >1){l_data1 = data[1];}
    }
    return l_data1;
}

const int MidiEvent::data2() const {
    int l_data2 =0;
    if (msgtype() == MIDI_MSG_TYPE::MIDI_CHANNEL_MESSAGES) {
        if (data.size() >2){l_data2 = data[2];}
    }
    return l_data2;
}

void MidiEvent::resetNrpnParams(){
    nrpnControl = -1;
    nrpnData = -1;
    processNrpn = false;
}

const bool MidiEvent::hasNrpn() const {
    return nrpnControl != -1;
}

const MIDI_MSG_TYPE MidiEvent::msgtype() const{
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



}
