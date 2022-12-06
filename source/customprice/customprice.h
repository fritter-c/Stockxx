#ifndef CUSTOMPRICE_H
#define CUSTOMPRICE_H

#include <QObject>
#include "customdataserie.h"
#include "StockxxDataTypes.h"
#include "customserie.h"

class CustomPrice : public CustomSerie
{
protected:
    CustomDataSerie* m_dataSerie;
    AssetId m_assetId;
    size_t m_nIndex;
    SerieInterval m_interval;
public:
    explicit CustomPrice(CustomDataSerie* dataSerie, QObject *parent = nullptr);
    virtual bool Next() override;
    virtual bool Prior() override;
    virtual bool PriorAll() override;
    virtual bool NextAll() override;
    virtual bool PriorN(size_t N) override;
    virtual bool NextN(size_t N) override;
    virtual size_t Size() override;
    virtual double Open() override;
    virtual double Close() override;
    virtual QDateTime Date() override;
    virtual double High() override;
    virtual double Low() override;
    virtual double Volume() override;
    virtual DataSerieValue *Data();
    virtual QuoteIdentifier Quote();
    SerieInterval interval() const;

signals:

};

#endif // CUSTOMPRICE_H
