#ifndef CUSTOMINDICATORVISUAL_H
#define CUSTOMINDICATORVISUAL_H

#include "customprice.h"
#include "pricescalevisual.h"
#include "timescalevisual.h"
#include "indicatordata.h"
#include <QObject>
#include <QGraphicsItem>

class CustomIndicatorVisual : public QGraphicsItem
{
    IndicatorData *m_data;
protected:
    CustomPrice* m_customPrice;
    IndicatorIdentifier m_id;
    QObject* m_parent;
    QGraphicsView* m_view;
    TimeScaleVisual* m_tsVisual;
    PriceScaleVisual* m_psVisual;
public:
    explicit CustomIndicatorVisual(QObject *parent = nullptr);

    IndicatorData *data() const;

signals:


};


#endif // CUSTOMINDICATORVISUAL_H
