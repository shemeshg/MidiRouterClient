#pragma once
#include "filters/sendmidiport.h"
#include "filters/FilterMidiChannelMsg.h"
#include "filters/logdata.h"
#include "filters/defferedevent.h"
#include "filters/SendRemoteServer.h"

namespace MidiRoute {

class RoutFiltersChainClass{
public:

    std::vector<std::unique_ptr<RoutFilter>> filterMidiChannelMsgAry;

    void addSendMidiPort(std::string portName)
    {
         filterMidiChannelMsgAry.push_back(std::unique_ptr<SendMidiPort>(new SendMidiPort(portName) ));
    }

    void addSendMidiPort(int portNumber)
    {
         filterMidiChannelMsgAry.push_back(std::unique_ptr<SendMidiPort>(new SendMidiPort(portNumber)));
    }

    void addSendRemoteServer(Webchannel::EmitCommand &ec, std::string serverName, int serverPort, int remoteMidiPortNumber)
    {

         filterMidiChannelMsgAry.push_back(std::unique_ptr<SendRemoteServer>(new SendRemoteServer(ec, serverName, serverPort, remoteMidiPortNumber)));
    }

    bool addSendRemoteServerByRemotePortName(Webchannel::EmitCommand &ec, std::string serverName, int serverPort, std::string remoteMidiPortName)
    {

        auto srs = std::unique_ptr<SendRemoteServer>(new SendRemoteServer(ec, serverName, serverPort));
        if (srs->initConnectByPortName(remoteMidiPortName)){
            filterMidiChannelMsgAry.push_back(std::move(srs));
            return true;
        }
        return false;

    }

    void addLogData(Webchannel::EmitCommand &ec, Webchannel::LOG_TO logto, string userdata){
            filterMidiChannelMsgAry.push_back(std::unique_ptr<LogData>( new LogData(ec, logto, userdata)));
    }

    void addDeferedEvent(RtMidiWrap::DEFFERED_EVENT_TYPE defferedEventType, double defferedTo){
            filterMidiChannelMsgAry.push_back(std::unique_ptr<DefferedEvent>(new  DefferedEvent( defferedEventType, defferedTo )));
    }

    void addFilterMidiChannelMsg(RangeMap fromChannel, RangeMap fromCommand, RangeMap fromData1, RangeMap fromData2,
                                 MIDI_FILTER_ACTION_IF_NOT deleteIfNot){


        filterMidiChannelMsgAry.push_back(std::unique_ptr<FilterMidiChannelMsg>(
                          new FilterMidiChannelMsg   ( fromChannel, fromCommand, fromData1, fromData2, deleteIfNot
                                                                        )));
    }




};


}


