#pragma once


#include "RtMidiWrap/RtMidiWrap.h"
#include <string>
#include <memory>

void virtualInOutPortCallback( double deltatime, std::vector< unsigned char > *message, void *userData );

class VirtualInOut {
public:
    std::unique_ptr<RtMidiIn> midiinVirtual = std::unique_ptr<RtMidiIn>( new RtMidiIn() );
    std::unique_ptr<RtMidiOut> midioutVirtual = std::unique_ptr<RtMidiOut>( new RtMidiOut() );
    void addVirtualInOutPort(std::string portname);
};



void addVirtualInOutPort(std::string portname);


