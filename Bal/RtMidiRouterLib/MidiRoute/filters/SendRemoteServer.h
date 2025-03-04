#pragma once
#include "MidiRoute/routfilter.h"
#include "webchannel/EmitCommand.h"
#include "MidiRoute/filters/SignalSlot.h"

namespace MidiRoute {

class SendRemoteServer:public RoutFilter{
    //
public:

    std::string serverName;
    int serverPort, remoteMidiPortNumber;
    Webchannel::EmitCommand &ec;


    std::unique_ptr<SignalSlotClass> slotClass;
    std::unique_ptr<SignalClass> signalClass;

    int initConnectByPortName(std::string remoteMidiPortName){

        slotClass = std::unique_ptr<SignalSlotClass>(new SignalSlotClass()) ;
        remoteMidiPortNumber = slotClass->openConnection(QString::fromStdString(serverName),serverPort,QString::fromStdString(remoteMidiPortName));
        if (remoteMidiPortNumber == -1) {return -1;}
        signalClass =  std::unique_ptr< SignalClass>( new SignalClass( *slotClass.get() ) );
        return remoteMidiPortNumber;

    }

    SendRemoteServer(Webchannel::EmitCommand &ec,std::string serverName, int serverPort):
        serverName{serverName},serverPort{serverPort},remoteMidiPortNumber{-1},ec{ec}  {
    };

    SendRemoteServer(Webchannel::EmitCommand &ec,std::string serverName, int serverPort, int remoteMidiPortNumber):
        serverName{serverName},serverPort{serverPort},remoteMidiPortNumber{remoteMidiPortNumber},ec{ec}  {

        slotClass = std::unique_ptr<SignalSlotClass>(new SignalSlotClass()) ;
        slotClass->openConnection(QString::fromStdString(serverName),serverPort, remoteMidiPortNumber);
        signalClass =  std::unique_ptr< SignalClass>( new SignalClass( *slotClass.get() ) );
    };

    void doFilter(RtMidiWrap::MidiEvent &in) override{
        signalClass->sendRemoteServer(in,serverName, serverPort, remoteMidiPortNumber);
    };


};

}




