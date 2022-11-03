#include "customstudie.h"

CustomStudie::CustomStudie(TimeScaleVisual *ts_Visual, PriceScaleVisual *ps_Visual, QGraphicsItem *parent)
    : QGraphicsItem{parent}
{
    m_tsVisual = ts_Visual;
    m_psVisual = ps_Visual;
    setParentItem(parent);

}

void CustomStudie::changeGeometry()
{
    prepareGeometryChange();
}

void CustomStudie::updatePrice(double)
{

}

void CustomStudie::setThirdPrice(QPointF)
{

}

void CustomStudie::addPoint(QPointF)
{

}

void CustomStudie::setSecondPrice(QPointF)
{

}

QRectF CustomStudie::boundingRect() const
{
    return QRectF(0,0,0,0);
}

void CustomStudie::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setClipRect(parentItem()->boundingRect());
}

QPainterPath CustomStudie::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());

    return path;
}

void CustomStudie::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    prepareGeometryChange();
    m_nPenWidth = 3;
}

void CustomStudie::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    prepareGeometryChange();
    m_nPenWidth = 1;
}
