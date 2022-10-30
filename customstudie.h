#ifndef CUSTOMSTUDIE_H
#define CUSTOMSTUDIE_H

#include <QGraphicsItem>
#include <pricescalevisual.h>
#include <timescalevisual.h>

class CustomStudie : public QGraphicsItem
{
protected:
    PriceScaleVisual* m_psVisual;
    TimeScaleVisual* m_tsVisual;
    const qreal m_cPriceScaleMargin = 2;
public:
    CustomStudie(TimeScaleVisual* ts_Visual, PriceScaleVisual* ps_Visual, QGraphicsItem* parent=nullptr);
    void changeGeometry();
    virtual void updatePrice(double);
};

#endif // CUSTOMSTUDIE_H
