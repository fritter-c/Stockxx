#ifndef CALCDAEMON_H
#define CALCDAEMON_H

#include <QThread>

class CalcDaemon : public QThread
{
private:
    static CalcDaemon* instance;
public:
    explicit CalcDaemon(QObject *parent = nullptr);
    static CalcDaemon& Instance(){
        return *instance;
    }
};

#endif // CALCDAEMON_H
