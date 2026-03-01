#include <QCoreApplication>
#include <QGuiApplication>
#include <QCommandLineParser>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QIcon>
#include "Bal/BalData.h"



bool parseArgumentsIsRunHeadless(int argc, char *argv[]) {
    QCoreApplication tempApp(argc, argv);

    QCommandLineParser parser;
    parser.addHelpOption();

    QCommandLineOption headlessOption(
        QStringList() << "headless",
        "Run in headless mode on the specified port by the gui.",
        ""
        );

    parser.addOption(headlessOption);

    parser.process(tempApp);

    if (parser.isSet(headlessOption)) {
        return true;
    }

    return false;
}

int runHeadless(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    BalData bl;
    bl.startServer(bl.reqServerPortNumber());

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
    bool isRunHeadless = parseArgumentsIsRunHeadless(argc, argv);

    if (isRunHeadless)
        return runHeadless(argc, argv);
    else
        return runGui(argc, argv);
}
