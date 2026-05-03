#include "midievent.h"
//#include "common.h"
namespace RtMidiWrap {



MidiEvent::MidiEvent(double deltatime, std::vector< BYTE> &data,
                     int portNumber, std::string &portName):data(data),deltatime(deltatime),portNumber(portNumber), portName(portName){
    updateProperties();
}

void MidiEvent::updateProperties(){

    if (msgtype() == MIDI_MSG_TYPE::MIDI_CHANNEL_MESSAGES) {
        constexpr int channelMask = 0xf;
        int i_channel = (data[0] & channelMask) + 1;
        int l_data1 =0, l_data2 =0;
        if (data.size() >1){l_data1 = data[1];}
        if (data.size() >2){l_data2 = data[2];}

        channel = i_channel;
        data1 = l_data1;
        data2 = l_data2;
    }
}

}
