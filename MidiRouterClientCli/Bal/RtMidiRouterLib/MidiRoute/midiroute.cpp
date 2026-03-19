#include "midiroute.h"
#include <string>

using namespace std;

namespace MidiRoute {



void MidiInRouter::proccess14bitCc(RtMidiWrap::MidiEvent &m)
{

    for  (int &cc14item:cc14Bit)
    {        
        constexpr int bit14ModChannel = 1000;
        int channelCc = m.channel * bit14ModChannel + m.data1;
        if(m.command == RtMidiWrap::CommonStatic::MIDI_CHANNEL_MESSAGES::controlchange &&
                channelCc == cc14item ){

            msbForCc14Bit[channelCc] = m.data2;
            return;
        }

        constexpr int bit14ModCc = 32;
        if(m.command == RtMidiWrap::CommonStatic::MIDI_CHANNEL_MESSAGES::controlchange &&
                channelCc == cc14item + bit14ModCc){
            m.cc14bitLsb = m.data2;
            m.data1 = m.data1 - bit14ModCc;
            m.data2 = msbForCc14Bit[channelCc - bit14ModCc];
            m.data[1] = m.data1;
            m.data[2] = m.data2;
        }
    }
}

void MidiInRouter::proccessNrpn(RtMidiWrap::MidiEvent &m)
{   
    constexpr int NrpnCc99 = 99;
    constexpr int NrpnCc98 = 98;
    constexpr int NrpnCc6 = 6;
    constexpr int NrpnCc38 = 38;
    constexpr int max7bit=128;
    if (m.command == RtMidiWrap::CommonStatic::MIDI_CHANNEL_MESSAGES::controlchange &&
            m.data1 == NrpnCc99){
        NrpnContainer nrpnC;
        nrpnC.nrpnCtrlMsb = m.data2;
        nrpnPack[m.channel] = std::move(nrpnC);
    }
    else if (m.command == RtMidiWrap::CommonStatic::MIDI_CHANNEL_MESSAGES::controlchange &&
            m.data1 == NrpnCc98){
        nrpnPack[m.channel].nrpnCtrlLsb = m.data2;
    }
    else if (m.command == RtMidiWrap::CommonStatic::MIDI_CHANNEL_MESSAGES::controlchange &&
            m.data1 == NrpnCc6){
        nrpnPack[m.channel].nrpnDataMsb = m.data2;
    }
    else if (m.command == RtMidiWrap::CommonStatic::MIDI_CHANNEL_MESSAGES::controlchange &&
            m.data1 == NrpnCc38){
        nrpnPack[m.channel].nrpnDataLsb = m.data2;

        m.nrpnControl = nrpnPack[m.channel].nrpnCtrlMsb * max7bit + nrpnPack[m.channel].nrpnCtrlLsb;
        m.nrpnData = nrpnPack[m.channel].nrpnDataMsb * max7bit + nrpnPack[m.channel].nrpnDataLsb;
    } else {
        m.resetNrpnParams();
    }
}

void MidiInRouter::proccessChainsAndFilters(RtMidiWrap::MidiEvent &m)
{
    // Force copy operation for vector
    std::vector< BYTE> mData;
    for (unsigned i=0; i<m.data.size(); i++)
            mData.push_back(m.data[i]);

    unsigned int nBytesChains = (unsigned int)routeFilterChains->chains.size();

    for ( unsigned int i_chain=0; i_chain<nBytesChains; i_chain++ ){
        RtMidiWrap::MidiEvent copyOfM = m;
        unsigned int nBytesFilters = (unsigned int)routeFilterChains->chains[i_chain]->filterMidiChannelMsgAry.size();

        std::vector< BYTE> copyOfData = mData;
        copyOfM.data  = copyOfData;

        for ( unsigned int i_filters=0; i_filters<nBytesFilters; i_filters++ ){
            if( copyOfM.eventStatus == RtMidiWrap::EVENT_STATUS::OK) {
                routeFilterChains->chains[i_chain]->filterMidiChannelMsgAry[i_filters]->doFilter(copyOfM);
            }
            if( copyOfM.eventStatus == RtMidiWrap::EVENT_STATUS::DEFFERED){
                copyOfM.defferedFilterChainId = (int)i_chain;
                copyOfM.defferedFilterId = (int)i_filters;
                if (copyOfM.defferedEventType == RtMidiWrap::DEFFERED_EVENT_TYPE::QUANTIZE_SPP){
                    copyOfM.defferedSubmittedAt = songposition.sppNoReset;
                    copyOfM.defferedEventType = RtMidiWrap::DEFFERED_EVENT_TYPE::IN_SPP;
                    int quantizeDiv = (int)(songposition.spp / copyOfM.defferedTo);
                    int quantizeAfterPosition = (int)((double)(quantizeDiv + 1) * copyOfM.defferedTo) ;
                    copyOfM.defferedTo = ((double)quantizeAfterPosition - songposition.spp);
                }
                if (copyOfM.defferedEventType == RtMidiWrap::DEFFERED_EVENT_TYPE::QUANTIZE_BAR){
                    copyOfM.defferedSubmittedAt = songposition.getBarPositionNoReset();
                    copyOfM.defferedEventType = RtMidiWrap::DEFFERED_EVENT_TYPE::IN_BAR;
                    int quantizeDiv = (int)(songposition.getBarPosition() / copyOfM.defferedTo);
                    int quantizeAfterPosition = (int)((double)(quantizeDiv + 1) * copyOfM.defferedTo) ;
                    copyOfM.defferedTo = ((double)quantizeAfterPosition - songposition.getBarPosition());
                }
                if (copyOfM.defferedEventType == RtMidiWrap::DEFFERED_EVENT_TYPE::AT_SPP){
                    copyOfM.defferedSubmittedAt = songposition.spp;
                }
                if(copyOfM.defferedEventType == RtMidiWrap::DEFFERED_EVENT_TYPE::IN_SPP){
                    copyOfM.defferedSubmittedAt = songposition.sppNoReset;
                }
                if (copyOfM.defferedEventType == RtMidiWrap::DEFFERED_EVENT_TYPE::AT_BAR){
                    copyOfM.defferedSubmittedAt = songposition.getBarPosition();
                }
                if(copyOfM.defferedEventType == RtMidiWrap::DEFFERED_EVENT_TYPE::IN_BAR){
                    copyOfM.defferedSubmittedAt = songposition.getBarPositionNoReset();
                }
                RtMidiWrap::MidiEvent defferedCopyOfM = copyOfM;
                defferedMidiEvents.push_back(std::unique_ptr<RtMidiWrap::MidiEvent>(new RtMidiWrap::MidiEvent (defferedCopyOfM)));
                copyOfM.eventStatus = RtMidiWrap::EVENT_STATUS::DELETED;
            }
        }
    }


}

void MidiInRouter::listener(RtMidiWrap::MidiEvent &m){
    if (!listenerRunning){return;}
    proccess14bitCc(m);
    proccessNrpn(m);
    proccessChainsAndFilters(m);
    if (m.hasNrpn()){
        m.processNrpn = true;
        proccessChainsAndFilters(m);
    }



}


}
