#include <regex>
#include <math.h>
#include "playmidi.h"
namespace RtMidiWrap {
PlayMidi::PlayMidi()
{}

unsigned int PlayMidi::getPortCount(){
    return midiinout->getPortCount();
}

std::string PlayMidi::getPortName(unsigned int portNumber){
    return  midiinout->getPortName(portNumber);
}

int PlayMidi::getPortNumber(const std::string &portName){
    return  midiinout->getPortNumber(portName);
}

void PlayMidi::openPort( unsigned int portNumber, const std::string &setPortName) {
    midiinout->openPort(portNumber,setPortName);
}
void PlayMidi::openPort( const std::string &PortName, const std::string &setPortName) {
    midiinout->openPort( PortName, setPortName);
}

bool PlayMidi::isPortOpen	(void){
    return midiinout->isPortOpen();
}

void PlayMidi::openVirtualPort	(const std::string & portName ){
    midiinout->openVirtualPort(portName);
}

void PlayMidi::setErrorCallback	(RtMidiErrorCallback errorCallback, void * 	userData){
    midiinout->setErrorCallback(errorCallback, userData);
}


int PlayMidi::openedPortNumber(){
    return midiinout->getOpenedPortNumber();
}
std::string PlayMidi::openedPortName(){
   return midiinout->getOpenedPortName();
}

BYTE PlayMidi::guessNoteNumber(std::string note){
    if (is_number(note)) {
        int i=std::stoi(note);
        constexpr int maxNoteNumber = 127;
        if (i>maxNoteNumber || i<0 ){throw std::runtime_error("error guessNoteNumber");}
        return std::stoi(note);
    }

    return noteNameToNumber(note);
}



std::string PlayMidi::noteNumberToName(BYTE num){
    constexpr int notesPerOctave = 12;
    return _notes[num % notesPerOctave] + std::to_string( getOctave(num));

}

BYTE PlayMidi::noteNameToNumber(std::string note){
    std::regex b("([CDEFGAB])(#{0,2}|b{0,2})([+-]?[[:digit:]]?)",std::regex_constants::icase);;
    if (! std::regex_match (note, b)){
        throw std::runtime_error("Invalid note name.");
    }

    char i = note[0];
    i = (char)std::toupper(i);
    std::string s{i};

    int semitones = this->_semitones.at(s);

    int octave = 0;
    size_t last_index = note.find_last_not_of("+-0123456789");
    octave = std::stoi( note.substr(last_index + 1) );


    constexpr int notesPerOctave = 12;
    int result = (int)(((octave + 1 - floor(octaveOffset)) * notesPerOctave) + semitones);

    if (note.find("#") != std::string::npos){result++;}
    if (note.find("b") != std::string::npos){result--;}
    constexpr int maxNoteNumber = 127;
    if (result < 0 || result > maxNoteNumber) {
        throw std::runtime_error("Invalid note name or note outside valid range.");
    }

    return result;
}



}
