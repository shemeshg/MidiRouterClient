#pragma once
#include "RtMidiWrap/midievent.h"

namespace MidiRoute {



enum MIDI_FILTER_ACTION_IF_NOT {
    DO_NOT_DELETE = 0,
    DELETE_IF_NOT = 1,
    DELETE_IF_IS = 2
};

class RoutFilter:public RtMidiWrap::CommonStatic{
public:
    virtual void doFilter(RtMidiWrap::MidiEvent &in)=0;
    RoutFilter(){};
    virtual ~RoutFilter()=default;
    RoutFilter(const RoutFilter&) = delete;
    RoutFilter& operator=(const RoutFilter&)= delete;
    RoutFilter(RoutFilter&&) = delete;
    RoutFilter& operator=(RoutFilter&&) = delete;

};




}

