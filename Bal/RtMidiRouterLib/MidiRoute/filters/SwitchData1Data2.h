

#pragma once

#include "MidiRoute/routfilter.h"

namespace MidiRoute {

class SwitchData1Data2 : public RoutFilter {

public:
    void doFilter(RtMidiWrap::MidiEvent &in) override {
        if (in.processNrpn && in.passedThrouFilter) {
            int oldNrpnData = in.nrpnData;
            in.nrpnData = in.nrpnControl;
            in.nrpnControl = oldNrpnData;
        } else {
            if (in.data.size() == 3) {
                int oldData2 = in.data.at(2);
                in.data[2] = in.data[1];
                in.data[1] = oldData2;
            }
        }
    };
};

} // namespace MidiRoute
