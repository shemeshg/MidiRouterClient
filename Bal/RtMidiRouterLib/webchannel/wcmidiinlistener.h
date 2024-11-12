#pragma once
#include "MidiRoute/midiroute.h"
#include "EmitCommand.h"

namespace Webchannel {


class WcMidiInListener:public MidiRoute::MidiInRouter{
public:
    EmitCommand &ec;
    //std::unique_ptr<WcRouteFilterChains> wrfc = unique_ptr<WcRouteFilterChains>(new WcRouteFilterChains());


    std::vector<int> propegateClockToOtherMidiIns {};

    ~WcMidiInListener() override{
        clearRoutingMidiChains();
    }

    WcMidiInListener(const WcMidiInListener&) = delete;
    WcMidiInListener& operator=(const WcMidiInListener&)= delete;
    WcMidiInListener(WcMidiInListener&&) = delete;
    WcMidiInListener& operator=(WcMidiInListener&&) = delete;


    void clearRoutingMidiChains(){
        getRouteFilterChains()->chains.clear();
        clearCc14Bit();
        propegateClockToOtherMidiIns.clear();
        getDefferedMidiEvents().clear();
    }

    WcMidiInListener(EmitCommand &ec): ec{ec}{
        //int i = ec.routeFilterChains->addChain();
        //ec.routeFilterChains->chains[i]->addSendMidiPort("IAC Driver Bus 1");
    };

    void clockAction(double barPosition, double spp, double barPositionNoReset, double sppNoReset) override{
        for (auto &channelId : propegateClockToOtherMidiIns){
            ec.propegateClock(channelId, barPosition, spp, barPositionNoReset, sppNoReset);
        }

        bool found = false;
        for (unsigned i=0; i<getDefferedMidiEvents().size(); ++i){
            auto m = getDefferedMidiEvents()[i].get();
             if (m->defferedEventType == RtMidiWrap::DEFFERED_EVENT_TYPE::AT_SPP && m->defferedTo <= spp){
                m->eventStatus = RtMidiWrap::EVENT_STATUS::OK;
                found = true;
            }
            if (m->defferedEventType == RtMidiWrap::DEFFERED_EVENT_TYPE::IN_SPP && (m->defferedTo + m->defferedSubmittedAt) <= sppNoReset){
                m->eventStatus = RtMidiWrap::EVENT_STATUS::OK;
                found = true;
            }
            if (m->defferedEventType == RtMidiWrap::DEFFERED_EVENT_TYPE::AT_BAR && m->defferedTo <= barPosition){
                m->eventStatus = RtMidiWrap::EVENT_STATUS::OK;
                found = true;
            }
            if (m->defferedEventType == RtMidiWrap::DEFFERED_EVENT_TYPE::IN_BAR && (m->defferedTo + m->defferedSubmittedAt) <= barPositionNoReset){
                m->eventStatus = RtMidiWrap::EVENT_STATUS::OK;
                found = true;
            }
        }

        if (!found){return;}

        for (unsigned i=0; i<getDefferedMidiEvents().size(); ++i){
            auto m = getDefferedMidiEvents()[i].get();
            if (m->eventStatus == RtMidiWrap::EVENT_STATUS::OK){
                   unsigned int nBytesFilters = (unsigned int)getRouteFilterChains()->chains[m->defferedFilterChainId]->filterMidiChannelMsgAry.size();
                   for ( unsigned int i_filters= (m->defferedFilterId+1) ; i_filters<nBytesFilters; i_filters++ ){
                        getRouteFilterChains()->chains[m->defferedFilterChainId]->filterMidiChannelMsgAry[i_filters]->doFilter(*m);
                   }
                   m->eventStatus = RtMidiWrap::EVENT_STATUS::DELETED;
            }
        }


        getDefferedMidiEvents().erase(
              std::remove_if(
                  getDefferedMidiEvents().begin(),
                  getDefferedMidiEvents().end(),
                  [&] (std::unique_ptr<RtMidiWrap::MidiEvent> const& m)
                  {
                      return m->eventStatus  == RtMidiWrap::EVENT_STATUS::DELETED;
                  }),
              getDefferedMidiEvents().end()
              );



    }


    /*
    void listener(RtMidiWrap::MidiEvent &m){
        ec.msgSend(m);
    }
    */

};
}


