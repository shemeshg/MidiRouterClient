#include "../Bal/ParsedArguments.h"

int main(int argc, char *argv[]) {

    ParsedArguments parsedArgs;
    parsedArgs.parseArgumentsMain(argc, argv);

    if (parsedArgs.mode == RunMode::Headless)
        return parsedArgs.runHeadless(argc, argv);
    else if (parsedArgs.mode == RunMode::ApplyDefaultPreset) {
        return parsedArgs.runApplyDefaultPreset(argc, argv);
    }
}