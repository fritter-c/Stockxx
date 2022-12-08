#include "freehandstudie.h"

FreeHandStudie::FreeHandStudie(QObject* manager, QPointF point, TimeScaleVisual *ts_Visual, PriceScaleVisual *ps_Visual, QGraphicsItem *parent)
    : CustomStudie(manager, ts_Visual, ps_Visual, parent)
{
    CoordinatePair cp;
    cp.price = m_psVisual->PriceAtY(point.y());
    cp.qi = m_tsVisual->findNearestDate(point.x());
    m_pointList.append(cp);
    setAcceptHoverEvents(true);
}

void FreeHandStudie::addPoint(QPointF point)
{
    CoordinatePair cp;
    cp.price = m_psVisual->PriceAtY(point.y());
    cp.qi = m_tsVisual->findNearestDate(point.x());

    // suaviza a linha
    if (cp.qi != m_pointList.last().qi){
        m_pointList.append(cp);
    }
    else if(abs(m_psVisual->YAtPrice(cp.price) - m_psVisual->YAtPrice(m_pointList.last().price)) >
            abs(m_tsVisual->getSpacing())){
        m_pointList.append(cp);
    }

    update();
}

QRectF FreeHandStudie::boundingRect() const
{
    if (m_polygon.count() > 0){

        return m_polygon.boundingRect();
    }
    return parentItem()->boundingRect();
}

QPainterPath FreeHandStudie::shape() const
{

    QPainterPath path;
    QPen pen;
    pen.setWidth(m_nPenWidth);
    QPainterPathStroker ps{pen};
    path.addPolygon(m_polygon);
    path = ps.createStroke(path);
    return path;
}

void FreeHandStudie::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    m_polygon.clear();
    CustomStudie::paint(painter, option, widget);
    QPen pen{m_mainColor, m_nPenWidth};
    painter->setPen(pen);
    for(int i{0}; i < m_pointList.count() - 1; ++i){
        QPointF point1{m_tsVisual->XAtQuote(m_pointList[i].qi), m_psVisual->YAtPrice(m_pointList[i].price)};
        QPointF point2{m_tsVisual->XAtQuote(m_pointList[i + 1].qi), m_psVisual->YAtPrice(m_pointList[i + 1].price)};
        m_polygon.append({point1, point2});
        painter->drawLine(point1, point2);
    }
}

void FreeHandStudie::changeGeometry()
{
    CustomStudie::changeGeometry();
    m_polygon.clear();
    for(int i{0}; i < m_pointList.count() - 1; ++i){
        QPointF point1{m_tsVisual->XAtQuote(m_pointList[i].qi), m_psVisual->YAtPrice(m_pointList[i].price)};
        QPointF point2{m_tsVisual->XAtQuote(m_pointList[i + 1].qi), m_psVisual->YAtPrice(m_pointList[i + 1].price)};
        m_polygon.append({point1, point2});
    }
}
