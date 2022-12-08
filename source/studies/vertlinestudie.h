#ifndef VERTLINESTUDIE_H
#define VERTLINESTUDIE_H

#include "customstudie.h"

class VertLineStudie : public CustomStudie
{
private:
    QuoteIdentifier m_qi;
public:
    VertLineStudie(QObject *manager, qreal, TimeScaleVisual* ts_Visual, PriceScaleVisual* ps_Visual, QGraphicsItem* parent);
    ~VertLineStudie();
    // QGraphicsItem interface
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    virtual void colorChanged() override;
};

#endif // VERTLINESTUDIE_H
