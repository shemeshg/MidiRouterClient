#include "ParsedArguments.h"
#include "Bal/BalData.h"
#include "quithelper.h"

void ParsedArguments::parseArgumentsMain(int argc, char *argv[]) {
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
                        "  --preset-name <preset>   Preset name (regex) to apply, use \"\" to list presets ";
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

int ParsedArguments::runHeadless(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    BalData bl;
    bl.startServer(bl.reqServerPortNumber());
    return app.exec();
}

int ParsedArguments::runApplyDefaultPreset(int argc, char *argv[]){
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

        if (!bl.midiClientConnection()->userDataConfig()->activatePresetByRegex(regexPresetName) || regexPresetName.isEmpty()){
            qDebug()<<"Coudnot find preset for regex"<<regexPresetName;


            QStringList names;
            for (auto *p : bl.midiClientConnection()->userDataConfig()->midiRoutePresets())
                names << p->name();

            qDebug()<<"Presets: "<<names;


            return 1;

        }
    }

    quitHelper.onApplyFinished = [&](){
        qDebug()<<"Connected inputs: "<<bl.midiClientConnection()->userDataConfig()->connectedInPorts();
    };

    qDebug()<<"Apply preset"<<bl.midiClientConnection()->userDataConfig()->activePreset()->name();
    bl.applyConfigEngine(callback, &engine);


    return app.exec();
}

bool ParsedArguments::isValidAddress(const QString &addr)
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

