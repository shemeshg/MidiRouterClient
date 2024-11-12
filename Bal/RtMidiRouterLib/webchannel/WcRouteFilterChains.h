#pragma once
#include "MidiRoute/midifilterchain.h"

namespace Webchannel {

class WcRouteFilterChains {
public:
    std::unique_ptr<MidiRoute::MidiFilterChain> routeFilterChains = std::unique_ptr<MidiRoute::MidiFilterChain>(new MidiRoute::MidiFilterChain());
};

}


