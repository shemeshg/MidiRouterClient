#include <QCoreApplication>
#include <QGuiApplication>
#include <QCommandLineParser>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QIcon>
#include "Bal/BalData.h"
#include "quithelper.h"
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
        } else if (parser.isSet(applyOption)) {
            mode = RunMode::ApplyDefaultPreset;
            if (parser.isSet(presetNameOption)) {
                isRegexPresetName = true;
                regexPresetName = parser.value(presetNameOption);
            }
        }



        if (parser.isSet(addressOption)) {
            isRemoteAddress = true;
            QString addr = parser.value(addressOption);
            if (isValidAddress(addr)){
                const QStringList parts = addr.split(':');
                serverName = parts[0];
                portNumber = parts[1].toInt();

            } else {
                hasError = true;
                errorMessage = QString("Invalid address format: '%1'. Expected ip:port").arg(addr);
                return;
            }
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
        if (hasError){
            qDebug()<<errorMessage;
            return 1;
        }
        BalData bl;

        if (isRemoteAddress){
            bl.startClient(serverName,portNumber);
        } else {
            bl.startClient();
        }
        if (bl.midiClientConnection()->serverStatus() != MidiClientConnection::ServerStatus::RUNNING){
            return 1;
        }


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


        if (isRegexPresetName){
            if (bl.midiClientConnection()->userDataConfig()->activatePresetByRegex(regexPresetName)){
                qDebug()<<"Found preset"<<bl.midiClientConnection()->userDataConfig()->activePreset()->name()
                         <<" for " <<regexPresetName;
            } else {
                qDebug()<<"Coudnot find regex"<<regexPresetName;
                return 1;

            }
        }

        bl.applyConfigEngine(callback, &engine);



        return app.exec();


    }
private:
    bool isValidAddress(const QString &addr)
    {
        const QStringList parts = addr.split(':');
        if (parts.size() != 2)
            return false;

        const QString host = parts[0];
        const QString portStr = parts[1];

        // Validate port
        bool ok = false;
        int port = portStr.toInt(&ok);
        if (!ok || port < 1 || port > 65535)
            return false;

        // Try IP first
        QHostAddress ip;
        if (ip.setAddress(host))
            return true;

        // Try hostname
        QHostInfo info = QHostInfo::fromName(host);
        return (info.error() == QHostInfo::NoError);
    }

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
