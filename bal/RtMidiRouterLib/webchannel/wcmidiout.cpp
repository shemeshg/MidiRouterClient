#include "wcmidiout.h"
//#include <QStringList>
//#include <QVariantMap>
//#include <string>
//#include "RtMidiWrap/playmidiout.h"
namespace Webchannel {
WcMidiOut::WcMidiOut(QObject *parent) : QObject(parent)
{
    midiout = std::unique_ptr<RtMidiWrap::MidiOut>(new RtMidiWrap::MidiOut());
}

bool WcMidiOut::msgToServer(const QString &msg){
    emit msgToClient("Just received msg from client of " + msg);
    return true;
}

int WcMidiOut::getPortCount(){

    return (int)midiout->getPortCount();
};

QString WcMidiOut::getPortName(int i){
    return  QString::fromStdString(  midiout->getPortName(i) );
}

int WcMidiOut::getPortNumber(const QString &s){
    return midiout->getPortNumber(s.toStdString());
}

QVariantMap WcMidiOut::getPorts(){
    QVariantMap qm;
    int nPorts = (int)midiout->getPortCount();

    for ( int i=0; i<nPorts; i++ ) {
      qm[QString::number(i)] = QString::fromStdString( midiout->getPortName(i));
    }
    return qm;
}

QVariantMap WcMidiOut::getOpenedPorts(){
    QVariantMap qm;

    for(auto const& imap: openedMidiOutObj){
        qm[QString::number(imap.first)] = QString::fromStdString(imap.second->midiout->getOpenedPortName());
    }

    return qm;
}


void WcMidiOut::openPort( int portNumber){
    if ( openedMidiOutObj.find(portNumber) == openedMidiOutObj.end() ) {
      // not found
        openedMidiOutObj[portNumber] = std::unique_ptr<RtMidiWrap::PlayMidiOut>(new RtMidiWrap::PlayMidiOut());
        openedMidiOutObj[portNumber]->openPort(portNumber);
    } else {
      // found
      return;
    }
}

void WcMidiOut::openVirtualPort(const QString &s){
    return midiout->openVirtualPort(s.toStdString());
}



bool WcMidiOut::isPortOpen( int portNumber){
    bool isOpened = openedMidiOutObj[portNumber]->midiout->isPortOpen();
    return isOpened;
}

void WcMidiOut::playNote( int portNumber, QStringList notes,  QStringList channels, int velocity){
    openPort(portNumber);
    openedMidiOutObj[portNumber]->playNote(qStringListToVectorString(notes), qStringListToVectorByte(channels), velocity);
}

void WcMidiOut::stopNote( int portNumber, QStringList notes,  QStringList channels, int velocity){
    openPort(portNumber);
    openedMidiOutObj[portNumber]->stopNote(qStringListToVectorString(notes), qStringListToVectorByte(channels), velocity);
}

void WcMidiOut::sendKeyAftertouch( int portNumber, QStringList notes,  QStringList channels, int pressure){
    openPort(portNumber);
    openedMidiOutObj[portNumber]->sendKeyAftertouch(qStringListToVectorString(notes), qStringListToVectorByte(channels), pressure);
}

void WcMidiOut::sendChannelMode( int portNumber, int command, int value,  QStringList channels){
   openPort(portNumber);
    openedMidiOutObj[portNumber]->sendChannelMode((RtMidiWrap::CommonStatic::MIDI_CHANNEL_MODE_MESSAGES)command, value, qStringListToVectorByte(channels));
}

void WcMidiOut::sendChannelAftertouch( int portNumber, int pressurer,  QStringList channels){
   openPort(portNumber);
    openedMidiOutObj[portNumber]->sendChannelAftertouch( pressurer, qStringListToVectorByte(channels));
}

void WcMidiOut::sendPitchBend( int portNumber, float bend,  QStringList channels){
   openPort(portNumber);
    openedMidiOutObj[portNumber]->sendPitchBend( bend, qStringListToVectorByte(channels));
}

void WcMidiOut::sendPitchBendLsbMsb( int portNumber, int lsb, int msb,  QStringList channels){
    openPort(portNumber);
    openedMidiOutObj[portNumber]->sendPitchBendLsbMsb( lsb, msb, qStringListToVectorByte(channels));
}

void WcMidiOut::decrementRegisteredParameter( int portNumber,int parameter ,QStringList channels){
    openPort(portNumber);
    openedMidiOutObj[portNumber]->decrementRegisteredParameter( (RtMidiWrap::CommonStatic::MIDI_REGISTERED_PARAMETER)parameter, qStringListToVectorByte(channels));
}

void WcMidiOut::incrementRegisteredParameter( int portNumber,int parameter ,QStringList channels){
    openPort(portNumber);
    openedMidiOutObj[portNumber]->incrementRegisteredParameter( (RtMidiWrap::CommonStatic::MIDI_REGISTERED_PARAMETER)parameter, qStringListToVectorByte(channels));
}

void WcMidiOut::setRegisteredParameter( int portNumber,int parameter,QStringList data ,QStringList channels){
    openPort(portNumber);
    openedMidiOutObj[portNumber]->setRegisteredParameter( (RtMidiWrap::CommonStatic::MIDI_REGISTERED_PARAMETER)parameter, qStringListToVectorByte(data), qStringListToVectorByte(channels));
}

void WcMidiOut::setModulationRange( int portNumber,int semitones,int cents,QStringList channels){
    openPort(portNumber);
    openedMidiOutObj[portNumber]->setModulationRange( semitones, cents, qStringListToVectorByte(channels));
}

void WcMidiOut::setPitchBendRange( int portNumber,int semitones,int cents,QStringList channels){
    openPort(portNumber);
    openedMidiOutObj[portNumber]->setPitchBendRange( semitones, cents, qStringListToVectorByte(channels));
}

void WcMidiOut::sendControlChange( int portNumber,int controller,int value,QStringList channels){
    openPort(portNumber);
    openedMidiOutObj[portNumber]->sendControlChange( controller, value, qStringListToVectorByte(channels));
}

void WcMidiOut::setNonRegisteredParameter( int portNumber,QStringList parameter,QStringList data,QStringList channels){
    openPort(portNumber);
    openedMidiOutObj[portNumber]->setNonRegisteredParameter( qStringListToVectorByte(parameter), qStringListToVectorByte(data), qStringListToVectorByte(channels));
}

void WcMidiOut::setNonRegisteredParameterInt( int portNumber,int parameter,int data,QStringList channels){
    openPort(portNumber);
    openedMidiOutObj[portNumber]->setNonRegisteredParameterInt( parameter, data, qStringListToVectorByte(channels));
}


void WcMidiOut::sendMessage( int portNumber,QStringList message){
    openPort(portNumber);
    auto msg = qStringListToVectorByte(message);
    openedMidiOutObj[portNumber]->midiout->sendMessage( &msg);
}

}
