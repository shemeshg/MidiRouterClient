#include <QCoreApplication>
#include <QGuiApplication>
#include <QCommandLineParser>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QIcon>
#include "Bal/BalData.h"

struct AppConfig {
    bool headless = false;
    int port = 0;
};

AppConfig parseArguments(int argc, char *argv[]) {
    QCoreApplication tempApp(argc, argv);

    QCommandLineParser parser;
    parser.addHelpOption();

    QCommandLineOption headlessOption(
        QStringList() << "headless",
        "Run in headless mode on the specified port.",
        "port"
        );

    parser.addOption(headlessOption);

    parser.process(tempApp);

    AppConfig cfg;
    if (parser.isSet(headlessOption)) {
        cfg.headless = true;
        bool ok = false;
        cfg.port = parser.value(headlessOption).toInt(&ok);
        if (!ok || cfg.port <= 0) {
            qWarning() << "Invalid port number for --headless";
            exit(1);
        }
    }

    return cfg;
}

int runHeadless(int argc, char *argv[], const AppConfig &cfg) {
    QCoreApplication app(argc, argv);

    BalData bl;
    bl.startServer(cfg.port);

    return app.exec();
}

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
    AppConfig cfg = parseArguments(argc, argv);

    if (cfg.headless)
        return runHeadless(argc, argv, cfg);
    else
        return runGui(argc, argv);
}
