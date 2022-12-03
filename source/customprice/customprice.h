#ifndef CUSTOMPRICE_H
#define CUSTOMPRICE_H

#include <QObject>
#include "customdataserie.h"
#include "StockxxDataTypes.h"

class CustomPrice : public QObject
{
protected:
    CustomDataSerie* m_dataSerie;
    AssetId m_assetId;
    size_t m_nIndex;
    SerieInterval m_interval;
public:
    explicit CustomPrice(CustomDataSerie* dataSerie, QObject *parent = nullptr);
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
    virtual DataSerieValue *Data();
    virtual QuoteIdentifier Quote();
    SerieInterval interval() const;

signals:

};

#endif // CUSTOMPRICE_H
