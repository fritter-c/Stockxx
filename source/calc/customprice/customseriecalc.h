#ifndef CUSTOMSERIECALC_H
#define CUSTOMSERIECALC_H

#include "qdatetime.h"
#include <cstddef>
#include <QObject>

class CustomSerieCalc : public QObject
{
    Q_OBJECT
protected:
    size_t m_nIndex{0};
public:
    CustomSerieCalc();
    virtual bool Next() = 0;
    virtual bool Prior() = 0;
    virtual bool PriorAll() = 0;
    virtual bool NextAll() = 0;
    virtual bool PriorN(size_t N) = 0;
    virtual bool NextN(size_t N) = 0;
    virtual size_t Size() = 0;
    virtual double Open() = 0;
    virtual double Close() = 0;
    virtual QDateTime Date() = 0;
    virtual double High() = 0;
    virtual double Low() = 0;
    virtual double Volume() = 0;

signals:

};

#endif // CUSTOMSERIECALC_H
