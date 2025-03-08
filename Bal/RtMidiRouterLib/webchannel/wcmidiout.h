#pragma once

#include <QObject>
#include <QStringList>
#include <QVariantMap>
#include <QVariantList>
#include <QVector>
#include <QJsonDocument>
#include <QJsonObject>
#include "RtMidiWrap/playmidiout.h"
namespace Webchannel {
class WcMidiOut : public QObject
{
    Q_OBJECT

public:
    explicit WcMidiOut(QObject *parent);

    Q_INVOKABLE bool msgToServer(const QString &msg);
    Q_INVOKABLE int getPortCount();
    Q_INVOKABLE QString getPortName(int i);
    Q_INVOKABLE int getPortNumber(const QString &s);
    Q_INVOKABLE QVariantMap getPorts();
    Q_INVOKABLE QVariantMap getOpenedPorts();

    Q_INVOKABLE void openPort( int portNumber) ;
    Q_INVOKABLE void openVirtualPort(const QString &s);

    // these functions assume openedMidiOutObj[portNumber] exists
    Q_INVOKABLE bool isPortOpen( int portNumber);
    Q_INVOKABLE void playNote( int portNumber, QStringList notes,  QStringList channels, int velocity);
    Q_INVOKABLE void stopNote( int portNumber, QStringList notes,  QStringList channels, int velocity);
    Q_INVOKABLE void sendChannelMode( int portNumber, int command, int value,  QStringList channels);
    Q_INVOKABLE void sendKeyAftertouch( int portNumber, QStringList notes,  QStringList channels, int pressure);
    Q_INVOKABLE void sendChannelAftertouch( int portNumber, int pressurer,  QStringList channels);
    Q_INVOKABLE void sendPitchBend( int portNumber, float bend,  QStringList channels);
    Q_INVOKABLE void sendPitchBendLsbMsb( int portNumber, int lsb, int msb,  QStringList channels);
    Q_INVOKABLE void decrementRegisteredParameter( int portNumber,int parameter ,QStringList channels);
    Q_INVOKABLE void incrementRegisteredParameter( int portNumber,int parameter ,QStringList channels);
    Q_INVOKABLE void setRegisteredParameter( int portNumber,int parameter,QStringList data,QStringList channels);
    Q_INVOKABLE void setModulationRange( int portNumber,int semitones,int cents,QStringList channels);
    Q_INVOKABLE void setPitchBendRange( int portNumber,int semitones,int cents,QStringList channels);
    Q_INVOKABLE void sendControlChange( int portNumber,int controller,int value,QStringList channels);
    Q_INVOKABLE void setNonRegisteredParameter( int portNumber,QStringList parameter,QStringList data,QStringList channels);
    Q_INVOKABLE void setNonRegisteredParameterInt( int portNumber,int parameter,int data,QStringList channels);
    Q_INVOKABLE void sendMessage( int portNumber,QStringList message);
    Q_INVOKABLE void restart(){
        midiout = std::make_unique<RtMidiWrap::MidiOut>();
        openedMidiOutObj.clear();
    }

    Q_INVOKABLE void sendActiveSensing(int portNumber){
        openedMidiOutObj[portNumber]->sendActiveSensing();
    }
    Q_INVOKABLE void sendClock(int portNumber){
        openedMidiOutObj[portNumber]->sendClock();
    }
    Q_INVOKABLE void sendContinue(int portNumber){
        openedMidiOutObj[portNumber]->sendContinue();
    }
    Q_INVOKABLE void sendReset(int portNumber){
        openedMidiOutObj[portNumber]->sendReset();
    }
    Q_INVOKABLE void sendStart(int portNumber){
        openedMidiOutObj[portNumber]->sendStart();
    }
    Q_INVOKABLE void sendStop(int portNumber){
        openedMidiOutObj[portNumber]->sendStop();
    }
    Q_INVOKABLE void sendTuningRequest(int portNumber){
        openedMidiOutObj[portNumber]->sendTuningRequest();
    }
    Q_INVOKABLE void setMasterTuning( int portNumber,float value,QStringList channels){
        openedMidiOutObj[portNumber]->setMasterTuning( value, qStringListToVectorByte(channels));
    }
    Q_INVOKABLE void sendSongPosition( int portNumber,int value){
        openedMidiOutObj[portNumber]->sendSongPosition( value);
    }
    Q_INVOKABLE void sendSongSelect( int portNumber,int value){
        openedMidiOutObj[portNumber]->sendSongSelect( value);
    }
    Q_INVOKABLE void sendTimecodeQuarterFrame( int portNumber,int value){
        openedMidiOutObj[portNumber]->sendTimecodeQuarterFrame( value);
    }
    Q_INVOKABLE void setTuningBank( int portNumber,int value,QStringList channels){
        openedMidiOutObj[portNumber]->setTuningBank( value, qStringListToVectorByte(channels));
    }
    Q_INVOKABLE void setTuningProgram( int portNumber,int value,QStringList channels){
        openedMidiOutObj[portNumber]->setTuningProgram( value, qStringListToVectorByte(channels));
    }
    Q_INVOKABLE void sendProgramChange( int portNumber,int program,QStringList channels){
        openedMidiOutObj[portNumber]->sendProgramChange( program, qStringListToVectorByte(channels));
    }
    Q_INVOKABLE void sendSysex( int portNumber,QStringList data){
        openedMidiOutObj[portNumber]->sendSysex( qStringListToVectorByte(data));
    }

private:
    // For general requests like midi list ports
    std::unique_ptr<RtMidiWrap::MidiOut> midiout;
    // Opened opnes
    std::map<int, std::unique_ptr<RtMidiWrap::PlayMidiOut>> openedMidiOutObj;

    std::vector<BYTE> qStringListToVectorByte(QStringList &channels){
        std::vector<BYTE>  stdchannels;
        foreach( QString str, channels) {
            stdchannels.push_back(str.toInt());
        }
        return stdchannels;
    }

    std::vector<std::string> qStringListToVectorString(QStringList &notes){

        std::vector<std::string>  stdNotes;
        foreach( QString str, notes) {
            stdNotes.push_back(str.toStdString());
        }
        return stdNotes;
    }

signals:
    bool msgToClient(QString msg);
};
}

