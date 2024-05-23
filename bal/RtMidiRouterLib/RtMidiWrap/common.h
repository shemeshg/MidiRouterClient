#pragma once
#include <string>
#include <map>
#include <vector>

typedef unsigned char BYTE;

namespace RtMidiWrap {
enum MIDI_MSG_TYPE {
    MIDI_CHANNEL_MESSAGES = 0,
    MIDI_SYSTEM_MESSAGES = 1
};

class CommonStatic {
public:
    std::vector<std::string> _notes = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};

    enum MIDI_SYSTEM_MESSAGES {
        // System common messages
        sysex = 0xF0,            // 240
        timecode = 0xF1,         // 241
        songposition = 0xF2,     // 242
        songselect = 0xF3,       // 243
        tuningrequest = 0xF6,    // 246
        sysexend = 0xF7,         // 247 (never actually received - simply ends a sysex)

        // System real-time messages
        clock = 0xF8,            // 248
        start = 0xFA,            // 250
        ccontinue = 0xFB,         // 251
        stop = 0xFC,             // 252
        activesensing = 0xFE,    // 254
        reset = 0xFF,            // 255
    };


    std::map<int,std::string> mapMIDI_SYSTEM_MESSAGES = {
        // System common messages
        {MIDI_SYSTEM_MESSAGES::sysex ,"sysex"},
        {MIDI_SYSTEM_MESSAGES::timecode , "timecode"},
        {MIDI_SYSTEM_MESSAGES::songposition , "songposition"},
        {MIDI_SYSTEM_MESSAGES::songselect , "songselect"},
        {MIDI_SYSTEM_MESSAGES::tuningrequest , "tuningrequest"},
        {MIDI_SYSTEM_MESSAGES::sysexend , "sysexend"},

        // System real-time messages
        {MIDI_SYSTEM_MESSAGES::clock , "clock"},
        {MIDI_SYSTEM_MESSAGES::start , "start"},
        {MIDI_SYSTEM_MESSAGES::ccontinue , "ccontinue"},
        {MIDI_SYSTEM_MESSAGES::stop , "stop"},
        {MIDI_SYSTEM_MESSAGES::activesensing , "activesensing"},
        {MIDI_SYSTEM_MESSAGES::reset , "reset"}
    };

    const std::map<int,std::string> mapMIDI_CHANNEL_MODE_MESSAGES = {
        {120,"allsoundoff"},
        {121,"resetallcontrollers"},
        {122,"localcontrol"},
        {123,"allnotesoff"},
        {124,"omnimodeoff"},
        {125,"omnimodeon"},
        {126,"monomodeon"},
        {127,"polymodeon"}};

    const std::map<int,std::string> mapMIDI_CONTROL_CHANGE_MESSAGES = {
        {0,"bankselectcoarse"},
        {1,"modulationwheelcoarse"},
        {2,"breathcontrollercoarse"},
        {4,"footcontrollercoarse"},
        {5,"portamentotimecoarse"},
        {6,"dataentrycoarse"},
        {7,"volumecoarse"},
        {8,"balancecoarse"},
        {10,"pancoarse"},
        {11,"expressioncoarse"},
        {12,"effectcontrol1coarse"},
        {13,"effectcontrol2coarse"},
        {16,"generalpurposeslider1"},
        {17,"generalpurposeslider2"},
        {18,"generalpurposeslider3"},
        {19,"generalpurposeslider4"},
        {32,"bankselectfine"},
        {33,"modulationwheelfine"},
        {34,"breathcontrollerfine"},
        {36,"footcontrollerfine"},
        {37,"portamentotimefine"},
        {38,"dataentryfine"},
        {39,"volumefine"},
        {40,"balancefine"},
        {42,"panfine"},
        {43,"expressionfine"},
        {44,"effectcontrol1fine"},
        {45,"effectcontrol2fine"},
        {64,"holdpedal"},
        {65,"portamento"},
        {66,"sustenutopedal"},
        {67,"softpedal"},
        {68,"legatopedal"},
        {69,"hold2pedal"},
        {70,"soundvariation"},
        {71,"resonance"},
        {72,"soundreleasetime"},
        {73,"soundattacktime"},
        {74,"brightness"},
        {75,"soundcontrol6"},
        {76,"soundcontrol7"},
        {77,"soundcontrol8"},
        {78,"soundcontrol9"},
        {79,"soundcontrol10"},
        {80,"generalpurposebutton1"},
        {81,"generalpurposebutton2"},
        {82,"generalpurposebutton3"},
        {83,"generalpurposebutton4"},
        {91,"reverblevel"},
        {92,"tremololevel"},
        {93,"choruslevel"},
        {94,"celestelevel"},
        {95,"phaserlevel"},
        {96,"databuttonincrement"},
        {97,"databuttondecrement"},
        {98,"nonregisteredparametercoarse"},
        {99,"nonregisteredparameterfine"},
        {100,"registeredparametercoarse"},
        {101,"registeredparameterfine"}
    };

    enum MIDI_CHANNEL_MESSAGES {
        noteoff = 0x8,           // 8
        noteon = 0x9,            // 9
        keyaftertouch = 0xA,     // 10
        controlchange = 0xB,     // 11
        channelmode = 0xB,       // 11
        nrpn = 0xB,              // 11
        programchange = 0xC,     // 12
        channelaftertouch = 0xD, // 13
        pitchbend = 0xE          // 14
    };

    std::map<int,std::string> mapMIDI_CHANNEL_MESSAGES = {
        {MIDI_CHANNEL_MESSAGES::noteoff,"noteoff"},
        {MIDI_CHANNEL_MESSAGES::noteon,"noteon"},
        {MIDI_CHANNEL_MESSAGES::keyaftertouch, "keyaftertouch"},
        {MIDI_CHANNEL_MESSAGES::controlchange, "controlchange"},
        {MIDI_CHANNEL_MESSAGES::channelmode, "channelmode"},
        {MIDI_CHANNEL_MESSAGES::nrpn , "nrpn"},
        {MIDI_CHANNEL_MESSAGES::programchange , "programchange"},
        {MIDI_CHANNEL_MESSAGES::channelaftertouch, "channelaftertouch"},
        {MIDI_CHANNEL_MESSAGES::pitchbend, "pitchbend"}
    };

    //static defs
    typedef std::map<std::string, int> SiMap;
    const static SiMap _semitones;

    const static std::vector<BYTE> channelAll;

    enum MIDI_REGISTERED_PARAMETER{
        pitchbendrange,
        channelfinetuning,
        channelcoarsetuning,
        tuningprogram,
        tuningbank,
        modulationrange,
        azimuthangle,
        elevationangle,
        gain,
        distanceratio,
        maximumdistance,
        maximumdistancegain,
        referencedistanceratio,
        panspreadangle,
        rollangle
    };
    typedef std::map<MIDI_REGISTERED_PARAMETER, std::vector<BYTE>> MrpMap;
    const static MrpMap midiRegisteredParameter;

    enum MIDI_CHANNEL_MODE_MESSAGES {

        allsoundoff = 120,
        resetallcontrollers = 121,
        localcontrol = 122,
        allnotesoff = 123,
        omnimodeoff = 124,
        omnimodeon = 125,
        monomodeon = 126,
        polymodeon = 127
    };

};



}

