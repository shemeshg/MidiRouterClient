#pragma once

namespace {
    constexpr int defaultPort = 12345;
}

class MidiServerClass
{
public:
    MidiServerClass();
    void connectAndExec();
    int getPort(){
        return port;
    }
    bool getServerIsRunning(){
        return serverIsRunning;
    }
private:
    int port = defaultPort;
    bool serverIsRunning = false;
};


