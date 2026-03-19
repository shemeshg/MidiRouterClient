//#include "RtMidiWrap/RtMidiWrap.h"
//#include "RtMidiWrap/midievent.h"
#include "MidiRoute/midiroute.h"
//#include "MidiRoute/routfilter.h"
//#include "MidiRoute/rangemap.h"

namespace MidiRoute {
void filterMidiChannelMsg(RtMidiWrap::MidiEvent &in, RangeMap &fromChannel, RangeMap &fromCommand, RangeMap &fromData1, RangeMap &fromData2,
                           MIDI_FILTER_ACTION_IF_NOT deleteIfNot
                          ){
    constexpr int nrpnCommand = 100;
    in.passedThrouFilter = true;

    bool passedFromFilter = true;
    if (in.msgtype == RtMidiWrap::MIDI_MSG_TYPE::MIDI_SYSTEM_MESSAGES){
        in.eventStatus = RtMidiWrap::EVENT_STATUS::DELETED;
        return;
    }
    if (in.msgtype == RtMidiWrap::MIDI_MSG_TYPE::MIDI_CHANNEL_MESSAGES ){
        std::vector<BYTE> sndVector{};
        for (unsigned i=0; i<in.data.size(); i++)
                sndVector.push_back(in.data[i]);


        int old_command = in.data[0] >> 4;
        if (in.processNrpn){
            old_command = nrpnCommand;
        }
        int new_command = old_command;
        passedFromFilter = passedFromFilter && fromCommand.isInRange( old_command);

        if (fromCommand.isInRange( old_command)){
            new_command = fromCommand.getVal((float)old_command);
        }

        int old_channel = in.channel;
        int new_channel = old_channel;
        passedFromFilter = passedFromFilter && fromChannel.isInRange( old_channel);
        if ( fromChannel.isInRange( old_channel) ){new_channel = fromChannel.getVal((float)old_channel);}


        int old_data1 = in.data[1];
        if (in.processNrpn){
             old_data1 = in.nrpnControl;
        }

        int new_data1 = old_data1;
        passedFromFilter = passedFromFilter && fromData1.isInRange(old_data1);
        if (fromData1.isInRange(old_data1)){new_data1 = fromData1.getVal((float)old_data1);}


        int old_data2 = 0;
        int new_data2 = 0;
        if (in.processNrpn){
            old_data2 = in.nrpnData;
            new_data2 = old_data2;
            passedFromFilter = passedFromFilter && fromData2.isInRange(old_data2);
            if (fromData2.isInRange(old_data2)){new_data2 = fromData2.getVal((float)old_data2);}
        } else {
            if (2 <= in.data.size()){
                old_data2 = in.data[2];
                new_data2 = old_data2;
                passedFromFilter = passedFromFilter && fromData2.isInRange(old_data2);
                if (fromData2.isInRange(old_data2)){
                    if (new_command == nrpnCommand){
                        constexpr float maxCcVal=127;
                        float f =  (float)old_data2 + (float)in.cc14bitLsb/maxCcVal;
                        new_data2 = fromData2.getVal(f);
                    } else {
                        new_data2 = fromData2.getVal((float)old_data2);
                    }
                }
            }
        }

        // destination within boundaries
        passedFromFilter = passedFromFilter && new_data2 >= 0 && new_data1 >= 0 && new_channel >= 0 && new_command >= 0;

        if (deleteIfNot == MIDI_FILTER_ACTION_IF_NOT::DELETE_IF_NOT  && !passedFromFilter){
            in.eventStatus = RtMidiWrap::EVENT_STATUS::DELETED;
        }
        else if (deleteIfNot == MIDI_FILTER_ACTION_IF_NOT::DELETE_IF_IS  && passedFromFilter){
            in.eventStatus = RtMidiWrap::EVENT_STATUS::DELETED;
        }
        else {
            if (passedFromFilter){
                if (new_command == nrpnCommand) {
                    int original_command = in.data[0] >> 4;
                    sndVector[0] = (original_command<<4) + (new_channel -1) ;
                    in.nrpnControl = new_data1;
                    in.nrpnData = new_data2;
                    in.processNrpn = true;

                    in.data = sndVector;
                    in.updateProperties();
                    return;
                }

                if (in.processNrpn == true){
                    in.processNrpn = false;
                }

                sndVector[0] = (new_command<<4) + (new_channel -1) ;

                sndVector[1] = new_data1;
                if (2 <= sndVector.size()){
                    sndVector[2] = new_data2;
                }



                if(new_command == RtMidiWrap::CommonStatic::MIDI_CHANNEL_MESSAGES::channelaftertouch ||
                   new_command ==  RtMidiWrap::CommonStatic::MIDI_CHANNEL_MESSAGES::programchange ){
                    if (3 == sndVector.size()){
                        sndVector[1] = sndVector[2];
                        // There should not be sndVector[2] in channelaftertouch
                        sndVector.pop_back();
                    }
                }

                if(new_command == RtMidiWrap::CommonStatic::MIDI_CHANNEL_MESSAGES::pitchbend ){
                        sndVector[1] = in.cc14bitLsb;
                }


                in.data = sndVector;
                in.updateProperties();
            }





        }



    }

}
}
