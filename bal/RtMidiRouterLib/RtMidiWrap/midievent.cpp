#include "midievent.h"
//#include "common.h"
namespace RtMidiWrap {



MidiEvent::MidiEvent(double deltatime, std::vector< BYTE> &data,
                     int portNumber, std::string &portName):data(data),deltatime(deltatime),portNumber(portNumber), portName(portName){
    updateProperties();
}

void MidiEvent::updateProperties(){
    if (eventStatus == EVENT_STATUS::DELETED) {return;}
    constexpr int sysMsgLowBound=240;
    if (data[0]<sysMsgLowBound){
        msgtype = MIDI_MSG_TYPE::MIDI_CHANNEL_MESSAGES;

        int l_command = data[0] >> 4;
        constexpr int channelMask = 0xf;
        int i_channel = (data[0] & channelMask) + 1;
        int l_data1 =0, l_data2 =0;
        if (data.size() >1){l_data1 = data[1];}
        if (data.size() >2){l_data2 = data[2];}
            channel = i_channel;
            command = l_command;
            commandStr = mapMIDI_CHANNEL_MESSAGES[l_command];
            data1 = l_data1;
            data2 = l_data2;
        } else {
            msgtype = MIDI_MSG_TYPE::MIDI_SYSTEM_MESSAGES;
            command = data[0];
            commandStr = mapMIDI_SYSTEM_MESSAGES[command];
        }
}

}
