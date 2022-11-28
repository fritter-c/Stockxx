#ifndef CUSTOMSERIE_H
#define CUSTOMSERIE_H

#include "StockxxDataTypes.h"
#include <QObject>

class CustomSerie
{
public:
    CustomSerie();
    virtual bool Next();
    virtual bool Prior();
    virtual bool PriorAll();
    virtual bool NextAll();
    virtual bool PriorN(size_t N);
    virtual bool NextN(size_t N);
    virtual size_t Size();
    virtual double Open();
    virtual double Close();
    virtual QDateTime Date();
    virtual double High();
    virtual double Low();
    virtual double Volume();
    virtual QuoteIdentifier Quote();
};

#endif // CUSTOMSERIE_H
