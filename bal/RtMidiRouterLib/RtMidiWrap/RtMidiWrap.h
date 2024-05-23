#pragma once
#include "common.h"
#include "RtMidi.h"

// Platform-dependent sleep routines.
#if defined(WIN32)
    #include <chrono>
    #include <thread>
    #define SLEEP( milliseconds ) std::this_thread::sleep_for(std::chrono::milliseconds((DWORD) milliseconds));
#else // Unix variants
  #include <unistd.h>
  //#define SLEEP( milliseconds ) usleep( (unsigned long) (milliseconds * 1000.0) )
#endif


namespace RtMidiWrap {





//MyClass.h
class RtMidiWrapClass {
public:
    static inline const  std::map<int, std::string>  apiMap = {
    {RtMidi::MACOSX_CORE, "OS-X CoreMIDI" },
    {RtMidi::WINDOWS_MM, "Windows MultiMedia"},
    {RtMidi::UNIX_JACK, "Jack Client"},
    {RtMidi::LINUX_ALSA, "Linux ALSA"},
    {RtMidi::RTMIDI_DUMMY, "RtMidi Dummy"}
      };
};


std::vector<std::string> getCompiledApi();


class IMidiInOut{

public:
    unsigned int getPortCount();
    std::string getPortName(unsigned int portNumber);
    int getPortNumber(const std::string &portName);
    void openPort( unsigned int portNumber = 0, const std::string &setPortName = std::string( "RtMidi" ) ) ;
    void openPort( const std::string &PortName, const std::string &setPortName = std::string( "RtMidi" ) ) ;
    bool isPortOpen	(void);
    void openVirtualPort	(const std::string & portName = std::string( "RtMidi Output" )	);
    void setErrorCallback	(RtMidiErrorCallback errorCallback = NULL, void * 	userData = 0 );



    std::string &getOpenedPortName(){
         return openedPortName;
    }
    int &getOpenedPortNumber(){
        return openedPortNumber;
    }
protected:
    void  setP_midi(RtMidi  *p){
        p_midi=p;
    };
private:
    std::string openedPortName = "";
    int openedPortNumber = -1;
    RtMidi  *p_midi=0;
    unsigned int unqIdPortNumber(unsigned int portNumber);
};

class MidiIn:public IMidiInOut{
std::unique_ptr<RtMidiIn> p_midi_in;    

public:
    //! User callback function type definition.
    typedef void (*RtMidiCallback)( double timeStamp, std::vector<unsigned char> *message, void *userData );

    MidiIn();

    std::string getCurrentApi();

    void setCallback( RtMidiCallback callback, void *userData = 0 );
    void cancelCallback();
    void ignoreTypes( bool midiSysex = true,bool midiTime = true, bool midiSense = true);
    double getMessage	(std::vector< unsigned char > * message	);

};

class MidiOut:public IMidiInOut{
    std::unique_ptr<RtMidiOut> p_midi_out;
public:
    MidiOut();

    std::string getCurrentApi();
    void sendMessage(const std::vector< BYTE > *message);
    void sendMessage(const BYTE * 	message,size_t 	size);

};

}





