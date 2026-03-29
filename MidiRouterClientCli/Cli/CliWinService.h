#pragma once
#include <windows.h>
#include <string>
#include <QCoreApplication>
#include <QTimer>
#include <memory>
#include "../Bal/BalData.h"


class CliWinService {
public:
    explicit CliWinService(std::wstring name)
        : serviceName(std::move(name)) {
        instance = this;
    }

    bool run() {
        SERVICE_TABLE_ENTRY serviceTable[] = {
            { const_cast<LPWSTR>(serviceName.c_str()), ServiceMain },
            { nullptr, nullptr }
        };
        bool ok = StartServiceCtrlDispatcher(serviceTable);
        return ok;
    }

private:
    // -------------------------
    // SERVICE ENTRY POINT
    // -------------------------
    static void WINAPI ServiceMain(DWORD argc, LPWSTR* argv) {

        instance->statusHandle = RegisterServiceCtrlHandler(
            instance->serviceName.c_str(),
            ServiceCtrlHandler
            );
        if (!instance->statusHandle) {
            return;
        }

        instance->status.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
        instance->status.dwControlsAccepted = SERVICE_ACCEPT_STOP;
        instance->status.dwCurrentState = SERVICE_START_PENDING;
        SetServiceStatus(instance->statusHandle, &instance->status);

        // Create stop event
        instance->stopEvent = CreateEvent(nullptr, TRUE, FALSE, nullptr);
        if (!instance->stopEvent) {
            return;
        }

        // Create Qt application
        int fakeArgc = 0;
        char* fakeArgv[] = { nullptr };
        instance->app = std::make_unique<QCoreApplication>(fakeArgc, fakeArgv);

        // Create worker BEFORE QTimer
        instance->worker = std::make_unique<BalData>();

        // Delay server start until event loop is running
        QTimer::singleShot(0, [] {
            instance->worker->startServer(instance->worker->reqServerPortNumber());

            if (!instance->worker->isServerRunning()) {
                // Report failure
                instance->status.dwCurrentState = SERVICE_STOPPED;
                instance->status.dwWin32ExitCode = ERROR_SERVICE_SPECIFIC_ERROR;
                SetServiceStatus(instance->statusHandle, &instance->status);

                instance->app->quit();
                return;
            }

            // SUCCESS — now tell SCM we are running
            instance->status.dwCurrentState = SERVICE_RUNNING;
            SetServiceStatus(instance->statusHandle, &instance->status);
        });


        // Report running
        instance->status.dwCurrentState = SERVICE_START_PENDING;
        SetServiceStatus(instance->statusHandle, &instance->status);

        // BLOCK on Qt event loop
        int code = instance->app->exec();

        // Report stopped
        instance->status.dwCurrentState = SERVICE_STOPPED;
        SetServiceStatus(instance->statusHandle, &instance->status);
    }

    // -------------------------
    // SERVICE CONTROL HANDLER
    // -------------------------
    static void WINAPI ServiceCtrlHandler(DWORD ctrlCode) {
        if (ctrlCode == SERVICE_CONTROL_STOP) {

            instance->status.dwCurrentState = SERVICE_STOP_PENDING;
            SetServiceStatus(instance->statusHandle, &instance->status);

            // Stop server
            if (instance->worker) {
                instance->worker->stopServer();
            }

            // Quit Qt event loop
            if (instance->app) {
                instance->app->quit();
            }

            // Signal stop event
            SetEvent(instance->stopEvent);
        }
    }

private:
    static CliWinService* instance;

    std::wstring serviceName;
    SERVICE_STATUS_HANDLE statusHandle{};
    SERVICE_STATUS status{};
    HANDLE stopEvent = nullptr;

    std::unique_ptr<QCoreApplication> app;
    std::unique_ptr<BalData> worker;
};


