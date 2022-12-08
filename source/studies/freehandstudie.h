#ifndef FREEHANDSTUDIE_H
#define FREEHANDSTUDIE_H

#include "customstudie.h"


// for a v2, I expect to implement a "continuos" coordinate so that the drawing is more smooth
struct CoordinatePair{
    double price;
    QuoteIdentifier qi;
};

class FreeHandStudie : public CustomStudie
{
private:
    QList<CoordinatePair> m_pointList;
    QPolygonF m_polygon;
    QPainterPath m_path;
public:
    FreeHandStudie(QObject* manager, QPointF, TimeScaleVisual* ts_Visual, PriceScaleVisual* ps_Visual, QGraphicsItem* parent);
    void addPoint(QPointF) override;

    // QGraphicsItem interface
    virtual QRectF boundingRect() const override;
    virtual QPainterPath shape() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    virtual void changeGeometry() override;
};




#endif // FREEHANDSTUDIE_H
