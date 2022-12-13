#ifndef IGLOWER_H
#define IGLOWER_H
#include "qtimer.h"
class IGlower : public QObject{
    Q_OBJECT
    QTimer m_glowTimer;
    void onTimer();
    int m_intensity{0};
    bool bFading{false};
public:
    IGlower();
    virtual void onGlow(int intensity) = 0;
    virtual void stop();
    virtual void start();
};

inline void IGlower::onTimer()
{
    if (bFading)
        m_intensity--;
    else
        m_intensity++;

    if (m_intensity <= 0){
        m_intensity = 0;
        bFading = false;
    }
    else if(m_intensity >= 100){
        m_intensity = 100;
        bFading = true;
    }
    onGlow(m_intensity);
}

inline IGlower::IGlower()
{
    m_glowTimer.setInterval(10);
    connect(&m_glowTimer, &QTimer::timeout,this, &IGlower::onTimer);
}

inline void IGlower::stop()
{
    m_glowTimer.stop();
    m_intensity = 0;
    bFading = false;
}

inline void IGlower::start()
{
    m_glowTimer.start();
}

#endif // IGLOWER_H
