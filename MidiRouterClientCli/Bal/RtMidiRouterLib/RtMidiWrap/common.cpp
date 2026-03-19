#include "common.h"
namespace RtMidiWrap {

const std::vector<BYTE> CommonStatic::channelAll = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
const CommonStatic::SiMap CommonStatic::_semitones ={
    {"C",0}, {"D",2}, {"E",4}, {"F",5}, {"G",7}, {"A",9}, {"B",11}
};

const CommonStatic::MrpMap CommonStatic::midiRegisteredParameter = {
    {MIDI_REGISTERED_PARAMETER::pitchbendrange, {0x00, 0x00}},
    {MIDI_REGISTERED_PARAMETER::channelfinetuning, {0x00, 0x01}},
    {MIDI_REGISTERED_PARAMETER::channelcoarsetuning, {0x00, 0x02}},
    {MIDI_REGISTERED_PARAMETER::tuningprogram, {0x00, 0x03}},
    {MIDI_REGISTERED_PARAMETER::modulationrange, {0x00, 0x04}},
    {MIDI_REGISTERED_PARAMETER::azimuthangle, {0x3D, 0x00}},
    {MIDI_REGISTERED_PARAMETER::elevationangle, {0x3D, 0x01}},
    {MIDI_REGISTERED_PARAMETER::gain, {0x3D, 0x02}},
    {MIDI_REGISTERED_PARAMETER::distanceratio, {0x3D, 0x03}},
    {MIDI_REGISTERED_PARAMETER::maximumdistance, {0x3D, 0x04}},
    {MIDI_REGISTERED_PARAMETER::maximumdistancegain, {0x3D, 0x05}},
    {MIDI_REGISTERED_PARAMETER::referencedistanceratio, {0x3D, 0x06}},
    {MIDI_REGISTERED_PARAMETER::panspreadangle, {0x3D, 0x07}},
    {MIDI_REGISTERED_PARAMETER::rollangle, {0x3D, 0x08}}
};

}
