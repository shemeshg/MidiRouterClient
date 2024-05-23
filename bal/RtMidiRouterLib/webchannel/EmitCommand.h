#pragma once
#include "RtMidiWrap/midievent.h"


namespace Webchannel {
enum LOG_TO{
    CLIENT,
    SERVER
};

class EmitCommand{
public:     
     virtual void msgSend(RtMidiWrap::MidiEvent &m, LOG_TO logto, std::string userdata)=0;
    virtual void propegateClock(int portNumber, double barPosition, double spp, double barPositionNoReset, double sppNoReset) = 0;

    EmitCommand(){}
    virtual ~EmitCommand() = default;
    EmitCommand(const EmitCommand&) = delete;
    EmitCommand& operator=(const EmitCommand&)= delete;
    EmitCommand(EmitCommand&&) = delete;
    EmitCommand& operator=(EmitCommand&&) = delete;
};


}


