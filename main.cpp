#include <QCoreApplication>
#include <QGuiApplication>
#include <QCommandLineParser>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QIcon>
#include "Bal/BalData.h"
#include "quithelper.h"

enum class RunMode {
    Gui,
    Headless,
    ApplyDefaultPreset,
    ApplyFirstRegexFoundPreset
};





class ParsedArguments {
public:
    RunMode mode = RunMode::Gui;

    explicit ParsedArguments(){
    }

    QString address;      // optional
    int portNumber;
    QString presetName;   // optional

    QString errorMessage; // non-empty if parsing failed
    bool hasError = false;

    void parseArgumentsMain(int argc, char *argv[]) {
        QCoreApplication tempApp(argc, argv);

        QCommandLineParser parser;
        parser.addHelpOption();

        QCommandLineOption headlessOption(
            QStringList() << "headless",
            "Run in headless mode on the specified port by the gui.",
            ""
            );

        QString applyDesc = "Apply a preset (local or remote).\n"
                            "  --address <address>      Remote address (ip:port).\n"
                            "  --preset-name <preset>   Preset name to apply.";
        QCommandLineOption applyOption(
            QStringList() << "apply",
            applyDesc
            );

        QCommandLineOption addressOption(
            QStringList() << "address",
            "    Remote address in the form ip:port.",
            "address"
            );
        addressOption.setFlags(QCommandLineOption::HiddenFromHelp);

        QCommandLineOption presetNameOption(
            QStringList() << "preset-name",
            "    Preset name to apply.",
            "preset"
            );
        presetNameOption.setFlags(QCommandLineOption::HiddenFromHelp);

        parser.addOption(headlessOption);
        parser.addOption(applyOption);
        parser.addOption(addressOption);
        parser.addOption(presetNameOption);


        parser.process(tempApp);


        if (parser.isSet(headlessOption)) {
            mode = RunMode::Headless;
        } else if (parser.isSet(presetNameOption)) {
            mode = RunMode::ApplyFirstRegexFoundPreset;
        } else if (parser.isSet(applyOption)) {
            mode = RunMode::ApplyDefaultPreset;
        }
    }

    int runHeadless(int argc, char *argv[]) {
        QCoreApplication app(argc, argv);
        BalData bl;
        bl.startServer(bl.reqServerPortNumber());
        return app.exec();
    }

    int runApplyDefaultPreset(int argc, char *argv[]){
        QCoreApplication app(argc, argv);
        BalData bl;

        bl.startClient();
        QJSEngine engine;

        QuitHelper quitHelper;
        QJSValue myLibVal = engine.newQObject(&quitHelper);


        engine.globalObject().setProperty(
            "QuitHelper",
            engine.newQObject(&quitHelper)
            );


        QJSValue callback = engine.evaluate(
            "(function(result) { QuitHelper.quit(); })"
            );

        bl.applyConfigEngine(callback, &engine);

        return app.exec();


    }
private:

};






int runGui(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    app.setWindowIcon(QIcon(":/icon.png"));
#ifdef Q_OS_WIN
    QQuickStyle::setStyle("Fusion");
#endif

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection
        );

    engine.loadFromModule("MainQml", "Main");
    return app.exec();
}

int main(int argc, char *argv[]) {
#ifdef Q_OS_WIN
    return runGui(argc, argv);
#endif

    ParsedArguments parsedArgs;
    parsedArgs.parseArgumentsMain(argc, argv);


    if (parsedArgs.mode == RunMode::Headless)
        return parsedArgs.runHeadless(argc, argv);
    else if (parsedArgs.mode == RunMode::ApplyDefaultPreset) {
        return parsedArgs.runApplyDefaultPreset(argc, argv);
    }
        return runGui(argc, argv);
}
