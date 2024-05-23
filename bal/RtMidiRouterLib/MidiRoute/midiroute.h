#pragma once
#include "RtMidiWrap/playmidiin.h"
#include "RtMidiWrap/playmidiout.h"
#include "midifilterchain.h"


namespace MidiRoute {
void doRoute(std::string configFile);




class NrpnContainer {
public:
    int nrpnCtrlMsb = -1;
    int nrpnCtrlLsb = -1;
    int nrpnDataMsb = -1;
    int nrpnDataLsb = -1;
};

class MidiInRouter:public RtMidiWrap::PlayMidiIn{
private:
    // protected temporary container for 14bit msb until lsb arrive
    // <channel+cc,data2>
    std::map<int,int> msbForCc14Bit;
    std::map<int,NrpnContainer> nrpnPack;

    void proccess14bitCc(RtMidiWrap::MidiEvent &m);
    void proccessNrpn(RtMidiWrap::MidiEvent &m);
    void proccessChainsAndFilters(RtMidiWrap::MidiEvent &m);

    std::vector<int> cc14Bit {};
    std::unique_ptr<MidiFilterChain> routeFilterChains;
    std::vector<std::unique_ptr<RtMidiWrap::MidiEvent>> defferedMidiEvents;
public:

    std::vector<std::unique_ptr<RtMidiWrap::MidiEvent>> &getDefferedMidiEvents(){
        return defferedMidiEvents;
    }

    std::unique_ptr<MidiFilterChain>  &getRouteFilterChains(){
        return routeFilterChains;
    }
    MidiInRouter(){
        routeFilterChains = std::unique_ptr<MidiFilterChain>(new MidiFilterChain());
    }

    void addCc14Bit(int channel,int cc){
        constexpr int bit14ModChannel = 1000;
        cc14Bit.push_back(channel * bit14ModChannel + cc);
    }

    void clearCc14Bit(){
        cc14Bit.clear();
    }
    void listener(RtMidiWrap::MidiEvent &m) override;

};




}




