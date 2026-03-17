#pragma once

#include <QHostInfo>

enum class RunMode {
    Gui,
    Headless,
    ApplyDefaultPreset
};





class ParsedArguments {
public:
    RunMode mode = RunMode::Gui;

    explicit ParsedArguments(){
    }

    bool isRemoteAddress = false;
    bool isRegexPresetName = false;
    QString regexPresetName;

    QString serverName;      // optional
    int portNumber;
    QString presetName;   // optional

    QString errorMessage; // non-empty if parsing failed
    bool hasError = false;

    void parseArgumentsMain(int argc, char *argv[]);

    int runHeadless(int argc, char *argv[]);

    int runApplyDefaultPreset(int argc, char *argv[]);
private:
    bool isValidAddress(const QString &addr);

};


