#pragma once
#include <memory>
#include "playmidi.h"

namespace RtMidiWrap {

namespace {
    constexpr int initVelocity = 64;
}

class PlayMidiOut:public PlayMidi
{



    std::vector<BYTE> _convertNoteToArray(std::vector<std::string> notes);

    void _selectRegisteredParameter(std::vector<BYTE> parameterAry, std::vector<BYTE> channels = channelAll);
    void _selectNonRegisteredParameter(std::vector<BYTE> parameterAry, std::vector<BYTE> channels = channelAll);
    void _setCurrentRegisteredParameter(std::vector<BYTE> data, std::vector<BYTE> channels = channelAll);
    void _deselectRegisteredParameter( std::vector<BYTE> channels = channelAll );
public:
    std::unique_ptr<MidiOut> midiout;
    PlayMidiOut();
    void sendChannelMode(MIDI_CHANNEL_MODE_MESSAGES command, BYTE value, std::vector<BYTE> channels = channelAll);
    void playNote( std::vector<std::string> notes, std::vector<BYTE> channels = channelAll, BYTE velocity = initVelocity);
    void stopNote( std::vector<std::string> notes, std::vector<BYTE> channels = channelAll, BYTE velocity = initVelocity);
    void sendKeyAftertouch(std::vector<std::string> notes, std::vector<BYTE> channels = channelAll, BYTE pressure = initVelocity );
    void sendChannelAftertouch(BYTE pressure = initVelocity, std::vector<BYTE> channels = channelAll);
    void sendPitchBend(float bend,  std::vector<BYTE> channels = channelAll);
    void sendPitchBendLsbMsb(BYTE lsb, BYTE msb,  std::vector<BYTE> channels = channelAll);
    void decrementRegisteredParameter(MIDI_REGISTERED_PARAMETER parameter, std::vector<BYTE> channels = channelAll);
    void incrementRegisteredParameter(MIDI_REGISTERED_PARAMETER parameter, std::vector<BYTE> channels = channelAll);
    void setRegisteredParameter(MIDI_REGISTERED_PARAMETER parameter,  std::vector<BYTE> data, std::vector<BYTE> channels = channelAll);
    void setModulationRange(BYTE semitones=0,BYTE cents=0,std::vector<BYTE> channels = channelAll);
    void setPitchBendRange(BYTE semitones=0,BYTE cents=0,std::vector<BYTE> channels = channelAll);
    void sendControlChange(BYTE controller, BYTE value, std::vector<BYTE> channels = channelAll);
    void setNonRegisteredParameter( std::vector<BYTE> parameter, std::vector<BYTE> data, std::vector<BYTE> channels = channelAll);
    void setNonRegisteredParameterInt( int parameter, int data, std::vector<BYTE> channels = channelAll);
    void sendMessage(const std::vector<BYTE> *message);
    void sendMessage(const BYTE *message,size_t size);

    void sendActiveSensing();
    void sendClock();
    void sendContinue();
    void sendReset();
    void sendStart();
    void sendStop();
    void sendTuningRequest();
    void setMasterTuning(float value = 0, std::vector<BYTE> channels = channelAll); //desired decimal adjustment value in semitones (-65 < x < 64)
    void sendSongPosition(int value = 0);
    void sendSongSelect(BYTE value);
    void sendTimecodeQuarterFrame(BYTE value);
    void setTuningBank(BYTE value, std::vector<BYTE> channels = channelAll);
    void setTuningProgram(BYTE value, std::vector<BYTE> channels = channelAll);
    void sendProgramChange(BYTE program, std::vector<BYTE> channels = channelAll);
    void sendSysex(std::vector<BYTE> data);





};
}



