#ifndef CUSTOMSERIE_H
#define CUSTOMSERIE_H

#include <QObject>

class CustomSerie : public QObject
{
    Q_OBJECT
protected:
    size_t m_nIndex{0};
public:
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
};
#endif // CUSTOMSERIE_H