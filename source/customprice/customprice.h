#ifndef CUSTOMPRICE_H
#define CUSTOMPRICE_H

#include <QObject>
#include "customdataserie.h"
#include "StockxxDataTypes.h"
#include "customserie.h"

class CustomPrice : public CustomSerie
{
    Q_OBJECT
protected:
    CustomDataSerie* m_dataSerie;
    CandleArray m_candles;
    AssetId m_assetId;
    SerieInterval m_interval;
    double m_dMax{std::numeric_limits<double>::lowest()};
    double m_dMin{std::numeric_limits<double>::max()};
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
    virtual QuoteIdentifier Quote() override;
    virtual SerieInterval Interval() override;
    virtual bool GoToQuote(QuoteIdentifier) override;
    virtual bool GoToQuote(size_t) override;
    virtual CandleArray GetCandles() override;
    virtual double Max() override;
    virtual double Min() override;
    virtual bool GoToIndex(size_t) override;

signals:

};
#endif // CUSTOMPRICE_H
