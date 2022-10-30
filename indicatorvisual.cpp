#include "indicatorvisual.h"

IndicatorVisual::IndicatorVisual(CustomPrice *customPrice, QObject *parent, QGraphicsView *view)
{
    m_customPrice = customPrice;
    m_parent = parent;
    m_view = view;
}

QRectF IndicatorVisual::boundingRect() const
{
    return QRectF(0,0,0,0);
}

void IndicatorVisual::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    
}

void IndicatorVisual::changeGeometry()
{
    prepareGeometryChange();
}


