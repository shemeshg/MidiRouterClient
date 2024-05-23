#include "playmidiin.h"
//#include "midievent.h"
namespace RtMidiWrap {


void _callback( double deltatime, std::vector< unsigned char > *message, void *userData)
{


  PlayMidiIn *p = static_cast<PlayMidiIn*>(userData);
  p->callback(deltatime,*message, p->openedPortNumber(),p->openedPortName());

}

PlayMidiIn::PlayMidiIn()
{
    midiin = std::unique_ptr<MidiIn>(new MidiIn());
    midiinout = midiin.get();

    midiin->setCallback(&_callback,(void *)this);
}

void PlayMidiIn::ignoreTypes( bool midiSysex,bool midiTime, bool midiSense){
    midiin->ignoreTypes(midiSysex, midiTime, midiSense);
}

void PlayMidiIn::callback( double deltatime, std::vector< BYTE> &message, int portNumber, std::string portName){

    if (message[0] == MIDI_SYSTEM_MESSAGES::songposition){
        songposition.setSpp(message);
        clockAction(songposition.getBarPosition(),songposition.spp, songposition.getBarPositionNoReset(), songposition.sppNoReset);
        return;
    }
    if (message[0] == MIDI_SYSTEM_MESSAGES::clock){
        songposition.tick();
        clockAction(songposition.getBarPosition(),songposition.spp, songposition.getBarPositionNoReset(), songposition.sppNoReset);
        return;
    }



    MidiEvent m(deltatime, message, portNumber, portName);

    listener(m);
}



void PlayMidiIn::listener(MidiEvent &m){
    (void)m;

    /*
    std::cout<<m.deltatime<<" ";
    std::cout<<m.channe<<" ";
    std::cout<<m.commandStr<<" ";
    std::cout<<m.data1<<" ";
    std::cout<<m.data2<<std::endl;

    unsigned int nBytes = m.data.size();
    for ( unsigned int i=0; i<nBytes; i++ )
      std::cout << "Byte " << i << " = " << (int)m.data.at(i) << ", ";
    */
}



}
