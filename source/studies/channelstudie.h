#ifndef CHANNELSTUDIE_H
#define CHANNELSTUDIE_H

#include "customstudie.h"

class ChannelStudie : public CustomStudie
{
private:
    double m_dSecondStartPrice;
    double m_dSecondEndPrice;
public:
    ChannelStudie(QObject* manager, qreal, double, TimeScaleVisual* ts_Visual, PriceScaleVisual* ps_Visual, QGraphicsItem* parent);
    void setThirdPrice(QPointF) override;

    // CustomStudie interface
    virtual void setSecondPrice(QPointF) override;
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    virtual QPainterPath shape() const override;
};

#endif // CHANNELSTUDIE_H
