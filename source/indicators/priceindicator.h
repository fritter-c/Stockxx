#ifndef PRICEINDICATOR_H
#define PRICEINDICATOR_H

#include "customindicator.h"

class PriceIndicator : public CustomIndicator
{
    Q_OBJECT
protected:
    CandleArray m_arData;
    virtual void resize(size_t n);
    virtual void grow(size_t n);
public:
    PriceIndicator(CustomSerie *base);
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
    virtual void addNewPrice(size_t, size_t, CandleArray*);
};

#endif // PRICEINDICATOR_H
