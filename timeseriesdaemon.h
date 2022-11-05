#ifndef TIMESERIESDAEMON_H
#define TIMESERIESDAEMON_H

#include <QThread>

class TimeSeriesDaemon : public QThread
{
protected:
    virtual void run() override;

public:
    explicit TimeSeriesDaemon(QObject *parent = nullptr);
};



#endif // TIMESERIESDAEMON_H
