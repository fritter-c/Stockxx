#ifndef CUSTOMARRAYINDICATOR_H
#define CUSTOMARRAYINDICATOR_H

#include "IndicatorDataTypes.h"
#include "customindicator.h"

class CustomArrayIndicator : public CustomIndicator
{
    Q_OBJECT
protected:
    DoublyArray m_arData;
    virtual void setInnerSize(size_t N);
    virtual void resize(size_t n) = 0;
    virtual void grow(size_t n) = 0;
public:
    CustomArrayIndicator(CustomSerie*base);
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
    virtual bool GoToQuote(QuoteIdentifier qi) override;
    virtual QuoteIdentifier Quote() override;
    virtual void addNewValue(size_t, size_t, DoublyArray*);
    virtual bool GoToQuote(size_t) override;
    virtual SerieInterval Interval() override;
    virtual double Max() override;
    virtual double Min() override;
    virtual bool GoToIndex(size_t) override;
    virtual bool Valid();
    virtual double Value() = 0;
    virtual QVector<double> Values() = 0;
};

#endif // CUSTOMARRAYINDICATOR_H
