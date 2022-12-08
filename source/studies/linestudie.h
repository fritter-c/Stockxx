#ifndef LINESTUDIE_H
#define LINESTUDIE_H

#include "customstudie.h"

class LineStudie : public CustomStudie
{
private:
    QLineF m_line;
    QPainterPath m_path;

public:
    LineStudie(QObject *manager, qreal, double, TimeScaleVisual* ts_Visual, PriceScaleVisual* ps_Visual, QGraphicsItem* parent);

public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    virtual void setSecondPrice(QPointF) override;
    virtual QPainterPath shape() const override;
    virtual QRectF boundingRect() const override;

};

#endif // LINESTUDIE_H
