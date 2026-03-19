//-define-file body webchannel/throttle.cpp
//-define-file header webchannel/throttle.h
//-only-file header //-
#pragma once
#include <functional>
#include <QTimer>


//-only-file body //-
//- #include "throttle.h"
#include <QDateTime>

//-only-file header
//-var {PRE} "Throttle::"
class Throttle: public QObject
{
public:
    //- {function} 1 1
    explicit Throttle(const int timeout, std::function<void()> func)
    //-only-file body
        :timeout{timeout}, func{func}
    {
        bindTimerForSaveThrottle();
    }

    //- {fn}
    void trigger()
    //-only-file body
    {
        qint64 now = QDateTime::currentMSecsSinceEpoch();

        if (m_saveAllowed && (now - m_lastSaveTime >= timeout)) {
            // Allowed → run immediately
            m_saveAllowed = false;
            m_lastSaveTime = now;
            func();
            m_throttleTimer.start();
        } else {
            // Not allowed → queue one save
            m_pendingSave = true;
        }
    }
    //-only-file header

  //-only-file header
private:
    const int timeout;
    const std::function<void()> func;

    bool m_saveAllowed = true;
    bool m_pendingSave = false;
    QTimer m_throttleTimer;
    qint64 m_lastSaveTime = 0;

    //- {fn}
    void bindTimerForSaveThrottle()
    //-only-file body
    {
        m_throttleTimer.setInterval(timeout);
        m_throttleTimer.setSingleShot(true);

        connect(&m_throttleTimer, &QTimer::timeout, this, [this] {
            m_saveAllowed = true;

            if (m_pendingSave) {
                m_pendingSave = false;
                m_saveAllowed = false;
                m_lastSaveTime = QDateTime::currentMSecsSinceEpoch();
                func();   // triggers immediate save if allowed
                m_throttleTimer.start();
            }
        });
    }

    //-only-file header
};
