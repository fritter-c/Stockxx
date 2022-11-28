#ifndef CUSTOMPRICECALC_H
#define CUSTOMPRICECALC_H

#include "customdataseriecalc.h"
#include <QObject>
#include "customserie.h"

class CustomPriceCalc : public CustomSerie
{
protected:
    CustomDataSerieCalc* m_dataSerie;
    AssetId m_assetId;
    size_t m_nIndex;
    SerieInterval m_interval;
public:
    explicit CustomPriceCalc(CustomDataSerieCalc* dataSerie);
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
    virtual bool goTo(size_t);
    inline DataSerieValue operator[](size_t i) const{
        return *m_dataSerie->ar_values[i];
    }
    SerieInterval interval() const;

};

#endif // CUSTOMPRICECALC_H