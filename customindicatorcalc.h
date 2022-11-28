#ifndef CUSTOMINDICATORCALC_H
#define CUSTOMINDICATORCALC_H

#include "indicatordata.h"
#include <QObject>

class CustomIndicatorCalc : public QObject
{
    Q_OBJECT
protected:
    CustomSerie* m_baseSerie;
    IndicatorData* m_data;
    IndicatorIdentifier m_id;
    size_t m_nIndex;
public:
    explicit CustomIndicatorCalc(CustomSerie* baseSerie);
    virtual size_t Size();
    virtual size_t Width();
    virtual double Value();
    virtual void createIndicatorValues();
    virtual QVector<double>& operator[](size_t);

    const IndicatorIdentifier &id() const;

public slots:
    void onCreateIndicatorFull();

signals:
    void NewData(size_t index);

};

#endif // CUSTOMINDICATORCALC_H
