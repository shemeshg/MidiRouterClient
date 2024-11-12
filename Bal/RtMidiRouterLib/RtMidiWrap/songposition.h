#pragma once

#include<cmath>
#include "common.h"

namespace RtMidiWrap {
class SongPosition {
public:

    double timeSig = 4;
    double timeSigDivBy = 4;
    double fromSppPos = 0;

    double clock = 0;
    double spp = 0;
    double sppNoReset = 0;
    double getBarPosition(){

        double totalBars = timeSig * timeSigDivBy ;
        return ((spp - fromSppPos )/ totalBars) ;
    }

    double getBarPositionNoReset(){

        double totalBars = timeSig * timeSigDivBy ;
        return ((sppNoReset - fromSppPos )/ totalBars) ;
    }

    void tick(){
        clock++;
        constexpr double bitPerBar = 4;
        constexpr double sppPerBar = 24;
        spp = spp + (timeSigDivBy/bitPerBar) * ((timeSig * timeSigDivBy)/timeSig )/sppPerBar;
        sppNoReset = spp + (timeSigDivBy/bitPerBar) * ((timeSig * timeSigDivBy)/timeSig )/sppPerBar;
        int g= (int)clock;
        if (g % (int)sppPerBar ==0){clock=0;}

        return;

    }
    void setSpp(std::vector< BYTE> &message){
        unsigned int nBytes = (unsigned int)message.size();

        int sppTotal = 0;

        constexpr int sppEvery7 = 7;
        for ( unsigned int i=1; i<nBytes; i++ )
          sppTotal = sppTotal + ( (int)message.at(i) << ( sppEvery7 * (i -1) ) );
        int ipow = (int)(log2(timeSigDivBy) - 2);

        spp = sppTotal * ( pow (4, ipow));
    }

};
}

