#include "timeguidevisual.h"
#include "qpainter.h"

TimeGuideVisual::TimeGuideVisual(QGraphicsItem *parent) : QGraphicsItem{parent}
{
    setParentItem(parent);
    m_rGuideHeight = topLevelItem()->boundingRect().height();
}

QRectF TimeGuideVisual::boundingRect() const
{
    return QRectF(m_rX, 0, 5, m_rGuideHeight); // aproximate area
}

void TimeGuideVisual::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPointF point1{m_rX, 0};
    QPointF point2(m_rX, m_rGuideHeight);
    painter->drawLine(point1, point2);
}

void TimeGuideVisual::geometryChanged()
{
    prepareGeometryChange();
    m_rGuideHeight = topLevelItem()->boundingRect().height();
}

void TimeGuideVisual::setRX(qreal newRY)
{
    prepareGeometryChange();
    m_rX = newRY;
}

