#include "midievent.h"
//#include "common.h"
namespace RtMidiWrap {



MidiEvent::MidiEvent(double deltatime, std::vector< BYTE> &data,
                     int portNumber, std::string &portName):data(data),deltatime(deltatime),portNumber(portNumber), portName(portName){
}



}
