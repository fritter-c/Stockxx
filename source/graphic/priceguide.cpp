#include "priceguide.h"
#include "qpainter.h"
#include "pricevisual.h"

void PriceGuide::setRY(qreal newRY)
{
    geometryChanged();
    m_rY = newRY;
}

PriceGuide::PriceGuide(QGraphicsItem *parent) : QGraphicsItem{parent}
{
    setParentItem(parent);
    m_parent = parent;
    m_rGuideLenght = topLevelItem()->boundingRect().width();

    PriceScaleVisual* pr = dynamic_cast<PriceVisual*>(m_parent)->GetPriceScale();
    pr->addPriceTag(pr->PriceAtY(m_rY),Qt::gray, this);
}

PriceGuide::~PriceGuide()
{
    PriceScaleVisual* pr = dynamic_cast<PriceVisual*>(m_parent)->GetPriceScale();
    pr->removePriceTag(this);
}


QRectF PriceGuide::boundingRect() const
{
    return QRectF(0,m_rY, m_rGuideLenght, 5); // aproximate area
}

void PriceGuide::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPointF point1{0, m_rY};
    QPointF point2{m_rGuideLenght,m_rY};
    painter->drawLine(point1, point2);
}

void PriceGuide::geometryChanged()
{
    prepareGeometryChange();
    m_rGuideLenght = topLevelItem()->boundingRect().width();
    PriceScaleVisual* pr = dynamic_cast<PriceVisual*>(m_parent)->GetPriceScale();
    pr->updatePriceTag(this, pr->PriceAtY(m_rY));
}