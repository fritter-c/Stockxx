#ifndef RESISTANCESTUDIE_H
#define RESISTANCESTUDIE_H

#include "customstudie.h"

class ResistanceStudie : public CustomStudie
{
private:
    double m_price;
    QLineF m_line;
public:
    ResistanceStudie(double price, TimeScaleVisual* ts_Visual, PriceScaleVisual* ps_Visual, QGraphicsItem* parent);
    ~ResistanceStudie();

    // QGraphicsItem interface
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    virtual QRectF boundingRect() const override;
    virtual QPainterPath shape() const override;
};

#endif // RESISTANCESTUDIE_H
