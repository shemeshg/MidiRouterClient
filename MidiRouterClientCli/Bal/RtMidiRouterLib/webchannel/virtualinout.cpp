#include "virtualinout.h"



void virtualInOutPortCallback( double deltatime, std::vector< unsigned char > *message, void *userData )
{
    (void)deltatime;
    VirtualInOut *midioutVirtual = static_cast<VirtualInOut*>(userData);
    midioutVirtual->midioutVirtual->sendMessage(message);

}


void VirtualInOut::addVirtualInOutPort(std::string portname){

    midiinVirtual->openVirtualPort(portname);

    midioutVirtual->openVirtualPort(portname);
    midiinVirtual->setCallback( &virtualInOutPortCallback, (void *)this );

}

std::vector<std::unique_ptr<VirtualInOut>> g; //NOLINT

void addVirtualInOutPort(std::string portname){
     std::unique_ptr<VirtualInOut> v = std::unique_ptr<VirtualInOut>(new VirtualInOut());
    v->addVirtualInOutPort(portname);
    g.push_back(std::move(v));

}
