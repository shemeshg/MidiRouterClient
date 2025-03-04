//#include <string>
//#include <map>
//#include "RtMidi.h"
#include "RtMidiWrap.h"
#include <regex>

namespace RtMidiWrap {



// namespace function
std::vector<std::string> getCompiledApi(){
    std::vector<std::string> _return;

    std::vector< RtMidi::Api > apis;
    RtMidi :: getCompiledApi( apis );

    for ( unsigned int i=0; i<apis.size(); i++ )
      _return.push_back( RtMidiWrapClass::apiMap.at( apis[i] ));


    return _return;
}

// class functions



    MidiIn::MidiIn(){        
        p_midi_in = std::make_unique<RtMidiIn>();
        setP_midi( p_midi_in.get());
    };

    MidiOut::MidiOut(){
        p_midi_out = std::make_unique<RtMidiOut>();
        setP_midi(p_midi_out.get()) ;
    };


    std::string MidiIn::getCurrentApi(){
        return RtMidiWrapClass::apiMap.at( p_midi_in->getCurrentApi());
    }

    void MidiIn::setCallback( RtMidiCallback callback, void *userData  ){
        p_midi_in->setCallback(callback, userData);
    }
    void MidiIn::cancelCallback(){
        p_midi_in->cancelCallback();
    }
    void MidiIn::ignoreTypes( bool midiSysex,bool midiTime, bool midiSense){
        p_midi_in->ignoreTypes(midiSysex, midiTime, midiSense);
    }
    double MidiIn::getMessage	(std::vector< unsigned char > * message	){
        return  p_midi_in->getMessage(message);
    }


    std::string MidiOut::getCurrentApi(){
        return RtMidiWrapClass::apiMap.at( p_midi_out->getCurrentApi());
    }

    void MidiOut::sendMessage(const std::vector<BYTE> *message){
        p_midi_out->sendMessage(message);
    }
    void MidiOut::sendMessage(const BYTE *message,size_t 	size){
        p_midi_out->sendMessage(message,size);
    }

    unsigned int IMidiInOut::getPortCount(){
        return p_midi->getPortCount();
    }

    std::string IMidiInOut::getPortName(unsigned int portNumber){

        return std::to_string(unqIdPortNumber(portNumber)) + "_" + extractAlsaNameIfRequired(p_midi->getPortName(portNumber));
    }

    std::string IMidiInOut::extractAlsaNameIfRequired(const std::string& input) {
        // Regex pattern to match the desired part
        std::regex pattern(R"((.*):(.* \d+:\d+$))");
        std::smatch match;
    
        if (std::regex_match(input, match, pattern)) {
            // match[2] contains the part after the first colon, but includes the numbers at the end
            std::string namePart = match[2];
    
            // Find the position of the last space
            size_t lastSpace = namePart.find_last_of(' ');
            if (lastSpace != std::string::npos) {
                // Remove the digits part after the last space
                namePart = namePart.substr(0, lastSpace);
            }
            
            return namePart;
        }
    
        // Return an empty string if the pattern does not match
        return input;
    }
    
    
    

    int IMidiInOut::getPortNumber(const std::string &portName){
        unsigned int nPorts = this->getPortCount();

        for ( unsigned i=0; i<nPorts; i++ ) {
          if ( this->getPortName(i) == portName){return (int)i;}
        }
        return -1;
    }

    bool IMidiInOut::isPortOpen(){
        return p_midi->isPortOpen();
    }

    void IMidiInOut::openVirtualPort	(const std::string &portName){
        p_midi->openVirtualPort(portName);
    }

    void IMidiInOut::setErrorCallback(RtMidiErrorCallback errorCallback, void * 	userData ){
        p_midi->setErrorCallback(errorCallback,userData);
    }

    unsigned int IMidiInOut::unqIdPortNumber(unsigned int portNumber)
    {
        //unsigned int nPorts = this->getPortCount();
        unsigned unqId = 0;
        std::string portnameWithoutUnqIdx = p_midi->getPortName(portNumber);
        for ( unsigned i=0; i<portNumber; i++ ) {
          if ( p_midi->getPortName(i) == portnameWithoutUnqIdx){unqId ++;}
        }
        return unqId;
    }

    void IMidiInOut::openPort( unsigned int portNumber, const std::string &setPortName) {
        p_midi->openPort(portNumber,setPortName);
        this->openedPortNumber = (int)portNumber;
        this->openedPortName = getPortName(openedPortNumber);
    }
    void IMidiInOut::openPort( const std::string &PortName, const std::string &setPortName) {
        this->openPort(this->getPortNumber(PortName),setPortName);
        this->openedPortName = PortName;
        this->openedPortNumber = this->getPortNumber(PortName);
    }
}
