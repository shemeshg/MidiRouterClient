#include <QCoreApplication>
#include <QGuiApplication>
#include <QCommandLineParser>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QIcon>
#include "ParsedArguments.h"





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
