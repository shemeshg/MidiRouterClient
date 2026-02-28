#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QIcon>
#include <QQuickStyle>
#include "Bal/BalData.h"
#include <QCommandLineParser>




int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    BalData bl;
    QCommandLineParser parser;
    parser.addHelpOption();
    QCommandLineOption headlessOption(
        QStringList() << "headless",
        "Run in headless mode on the specified port.",
        "port"
        );
    parser.addOption(headlessOption);
    parser.process(app);
    if (parser.isSet(headlessOption)) {
        bool ok = false;
        int port = parser.value(headlessOption).toInt(&ok);

        if (!ok || port <= 0) {
            qWarning() << "Invalid port number for --headless";
            return 1;
        }

        bl.startServer(port);
        return app.exec();
    }

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
        Qt::QueuedConnection);
    engine.loadFromModule("MainQml", "Main");

    return app.exec();

}
