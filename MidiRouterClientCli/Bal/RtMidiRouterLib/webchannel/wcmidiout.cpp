#include "wcmidiout.h"
//#include <QStringList>
//#include <QVariantMap>
//#include <string>
#include <QTimer>

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

bool WcMidiOut::sendEmbededCommandsSequence(int portNumber, QString commandsString, QStringList channels)
{
    bool tokenFound = false;
    // Combined regex to preserve order of appearance
    QRegularExpression re(
        R"(\b(?:CC-(\d+)-(\d+)|PC-(\d+)|NRPN-(\d+)-(\d+)|WAIT-(\d+)|NOTE-ON-(\d+)-(\d+)|NOTE-OFF-(\d+)-(\d+))\b)"
        );

    QRegularExpressionMatchIterator it = re.globalMatch(commandsString);

    int accumulatedDelay = 0;
    while (it.hasNext()) {
        QRegularExpressionMatch m = it.next();

        // --- WAIT-x ---
        if (m.captured(6).length()) {
            int waitMs = m.captured(6).toInt();
            accumulatedDelay += waitMs;
            tokenFound = true;
            continue;
        }

        // --- CC-x-y ---
        if (m.captured(1).length() && m.captured(2).length()) {
            int cc1 = m.captured(1).toInt();
            int cc2 = m.captured(2).toInt();

            QTimer::singleShot(accumulatedDelay, this, [=]() {
                sendControlChange(portNumber, cc1, cc2, channels);
            });

            tokenFound = true;
            continue;
        }

        // --- PC-x ---
        if (m.captured(3).length()) {
            int pc = m.captured(3).toInt();

            QTimer::singleShot(accumulatedDelay, this, [=]() {
                sendProgramChange(portNumber, pc, channels);
            });

            tokenFound = true;
            continue;
        }

        // --- NRPN-x-y ---
        if (m.captured(4).length() && m.captured(5).length()) {
            int n1 = m.captured(4).toInt();
            int n2 = m.captured(5).toInt();

            QTimer::singleShot(accumulatedDelay, this, [=]() {
                setNonRegisteredParameterInt(portNumber, n1, n2, channels);
            });

            tokenFound = true;
            continue;
        }

        // NOTE-ON-x-y
        if (m.captured(7).length() && m.captured(8).length()) {
            QString note = m.captured(7);
            int velocity = m.captured(8).toInt();

            QStringList noteList = { note };

            QTimer::singleShot(accumulatedDelay, this, [=]() {
                playNote(portNumber, noteList, channels, velocity);
            });

            tokenFound = true;
            continue;
        }

        // NOTE-OFF-x-y
        if (m.captured(9).length() && m.captured(10).length()) {
            QString note = m.captured(9);
            int velocity = m.captured(10).toInt();

            QStringList noteList = { note };

            QTimer::singleShot(accumulatedDelay, this, [=]() {
                stopNote(portNumber, noteList, channels, velocity);
            });

            tokenFound = true;
            continue;
        }
    }
    return tokenFound;
}

}
