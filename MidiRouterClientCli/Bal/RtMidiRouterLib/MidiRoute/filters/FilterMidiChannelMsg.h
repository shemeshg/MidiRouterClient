#pragma once

#include "MidiRoute/routfilter.h"
#include "MidiRoute/rangemap.h"

namespace MidiRoute {

void filterMidiChannelMsg(RtMidiWrap::MidiEvent &in, RangeMap &fromChannel, RangeMap &fromCommand, RangeMap &fromData1, RangeMap &fromData2,
                           MIDI_FILTER_ACTION_IF_NOT deleteIfNot
                          );


class FilterMidiChannelMsg:public RoutFilter{
    RangeMap fromChannel;
    RangeMap fromCommand;
    RangeMap fromData1;
    RangeMap fromData2;

    MIDI_FILTER_ACTION_IF_NOT deleteIfNot;
public:

    FilterMidiChannelMsg(RangeMap fromChannel, RangeMap fromCommand, RangeMap fromData1, RangeMap fromData2,
                         MIDI_FILTER_ACTION_IF_NOT deleteIfNot):
        fromChannel(fromChannel), fromCommand(fromCommand), fromData1(fromData1),fromData2(fromData2),
                                     deleteIfNot(deleteIfNot)
    {
    };


    void doFilter(RtMidiWrap::MidiEvent &in) override {
       filterMidiChannelMsg(in, fromChannel, fromCommand, fromData1, fromData2,
                                  deleteIfNot);
    };

};

}

