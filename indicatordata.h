#ifndef INDICATORDATA_H
#define INDICATORDATA_H

#include "StockxxDataTypes.h"
#include <QObject>
#include "customserie.h"

class IndicatorData : public CustomSerie
{
protected:
    DoublyArray ar_data;
    size_t m_nIndex{0};
    void setInnerDataSize(uint n);

public:
    explicit IndicatorData();
    virtual double data();
    virtual bool Next() override;
    virtual bool Prior() override;
    virtual bool PriorAll() override;
    virtual bool NextAll() override;
    virtual bool PriorN(size_t N) override;
    virtual bool NextN(size_t N) override;
    virtual void popLast();
    virtual void popFirst();
    virtual size_t Size() override;
    virtual size_t InnerSize();
    virtual bool goTo(size_t);
    virtual QVector<double>& operator[](size_t);
    virtual void grow(size_t);
    virtual void setSize(size_t);

signals:

};
#endif // INDICATORDATA_H
