#pragma once
#include "RtMidiWrap.h"
#include <algorithm>
#include <cctype>


namespace RtMidiWrap {
class PlayMidi:public CommonStatic
{

public:
    IMidiInOut  *midiinout = 0;

    PlayMidi();

    unsigned int getPortCount();
    std::string getPortName(unsigned int portNumber);
    int getPortNumber(const std::string &portName);
    void openPort( unsigned int portNumber = 0, const std::string &setPortName = std::string( "RtMidi" ) ) ;
    void openPort( const std::string &PortName, const std::string &setPortName = std::string( "RtMidi" ) ) ;
    bool isPortOpen	(void);
    void openVirtualPort	(const std::string & portName = std::string( "RtMidi Output" )	);
    void setErrorCallback	(RtMidiErrorCallback errorCallback = NULL, void * 	userData = 0 );

    bool is_number(const std::string& s)
    {
        return !s.empty() && std::find_if(s.begin(),
                                          s.end(), [](BYTE c) { return !std::isdigit(c); }) == s.end();
    }

    int getOctave(int number) {
        constexpr int semiTonsPerOct = 12;
        return (number / semiTonsPerOct - 1) + octaveOffset;
    }

    BYTE noteNameToNumber(std::string note);
    std::string noteNumberToName(BYTE num);
    BYTE guessNoteNumber(std::string note);


    int octaveOffset = 0;

    int openedPortNumber();
    std::string openedPortName();



};



}


