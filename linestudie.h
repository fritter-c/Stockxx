#ifndef LINESTUDIE_H
#define LINESTUDIE_H

#include "customstudie.h"

class LineStudie : public CustomStudie
{
private:
    QLineF m_line;
public:
    LineStudie(qreal, double, TimeScaleVisual* ts_Visual, PriceScaleVisual* ps_Visual, QGraphicsItem* parent=nullptr);

    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // CustomStudie interface
    virtual void updateLastPos(QPointF) override;
};

#endif // LINESTUDIE_H
