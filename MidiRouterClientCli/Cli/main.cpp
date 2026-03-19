#include "../Bal/ParsedArguments.h"
#include <QDebug>

#ifdef Q_OS_WIN
#include "CliWinService.h"
CliWinService* CliWinService::instance = nullptr;
#endif

int main(int argc, char *argv[]) {    
    ParsedArguments parsedArgs;
    parsedArgs.parseArgumentsMain(argc, argv);

    if (parsedArgs.mode == RunMode::Headless)
        return parsedArgs.runHeadless(argc, argv);
    else if (parsedArgs.mode == RunMode::ApplyDefaultPreset) {
        return parsedArgs.runApplyDefaultPreset(argc, argv);
    }

    #ifdef Q_OS_WIN

    CliWinService service(L"MidiRouterCli");
    service.run();
    #endif
}
