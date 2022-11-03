#ifndef FIBONACCISTUDIE_H
#define FIBONACCISTUDIE_H

#include "customstudie.h"

class FibonacciStudie : public CustomStudie
{
public:
    FibonacciStudie(qreal, double, TimeScaleVisual* ts_Visual, PriceScaleVisual* ps_Visual, QGraphicsItem* parent);

    // QGraphicsItem interface
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    virtual void setSecondPrice(QPointF) override;
    virtual QPainterPath shape() const override;
};

#endif // FIBONACCISTUDIE_H
