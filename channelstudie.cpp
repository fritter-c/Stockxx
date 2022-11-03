#include "channelstudie.h"

ChannelStudie::ChannelStudie(qreal x, double price, TimeScaleVisual *ts_Visual, PriceScaleVisual *ps_Visual, QGraphicsItem *parent)
    : CustomStudie(ts_Visual, ps_Visual, parent)
{
    m_dStartPrice = price;
    m_dEndPrice = price;
    m_dSecondStartPrice = price;
    m_dSecondEndPrice = price;
    m_qiStartQuote = m_tsVisual->findNearestDate(x);
    m_qiEndQuote = m_qiStartQuote;
    setAcceptHoverEvents(true);
}

void ChannelStudie::setThirdPrice(QPointF y)
{
    prepareGeometryChange();
    m_dSecondEndPrice = m_psVisual->PriceAtY(y.y());
    m_dSecondStartPrice = m_dStartPrice - (m_dEndPrice - m_dSecondEndPrice);
}

void ChannelStudie::setSecondPrice(QPointF pf)
{
    prepareGeometryChange();
    m_qiEndQuote = m_tsVisual->findNearestDate(pf.x());
    m_dEndPrice  = m_psVisual->PriceAtY(pf.y());
    m_dSecondEndPrice  = m_dEndPrice;
    update();
}

QRectF ChannelStudie::boundingRect() const
{
    if (m_dStartPrice > m_dSecondStartPrice){
        QPointF point1{m_tsVisual->XAtQuote(m_qiStartQuote), m_psVisual->YAtPrice(m_dStartPrice)};
        QPointF point2{m_tsVisual->XAtQuote(m_qiEndQuote), m_psVisual->YAtPrice(m_dSecondEndPrice)};
        return QRectF{point1, point2}.normalized();
    }
    else{
        QPointF point1{m_tsVisual->XAtQuote(m_qiStartQuote), m_psVisual->YAtPrice(m_dSecondStartPrice)};
        QPointF point2{m_tsVisual->XAtQuote(m_qiEndQuote), m_psVisual->YAtPrice(m_dEndPrice)};
        return QRectF{point1, point2}.normalized();
    }

}

void ChannelStudie::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    CustomStudie::paint(painter, option, widget);
    QPointF point1{m_tsVisual->XAtQuote(m_qiStartQuote), m_psVisual->YAtPrice(m_dStartPrice)};
    QPointF point2{m_tsVisual->XAtQuote(m_qiEndQuote), m_psVisual->YAtPrice(m_dEndPrice)};
    QPointF point3{m_tsVisual->XAtQuote(m_qiStartQuote), m_psVisual->YAtPrice(m_dSecondStartPrice)};
    QPointF point4{m_tsVisual->XAtQuote(m_qiEndQuote), m_psVisual->YAtPrice(m_dSecondEndPrice)};
    QPen pen{Qt::yellow, m_nPenWidth};
    painter->setPen(pen);
    painter->drawLines({{point1, point2}, {point3, point4}});
}

QPainterPath ChannelStudie::shape() const
{
    QPointF point1{m_tsVisual->XAtQuote(m_qiStartQuote), m_psVisual->YAtPrice(m_dStartPrice)};
    QPointF point2{m_tsVisual->XAtQuote(m_qiEndQuote), m_psVisual->YAtPrice(m_dEndPrice)};
    QPointF point3{m_tsVisual->XAtQuote(m_qiStartQuote), m_psVisual->YAtPrice(m_dSecondStartPrice)};
    QPointF point4{m_tsVisual->XAtQuote(m_qiEndQuote), m_psVisual->YAtPrice(m_dSecondEndPrice)};
    QPainterPath path;
    path.moveTo(point1);
    path.lineTo(point2);
    path.moveTo(point3);
    path.lineTo(point4);
    QPen pen;
    pen.setWidth(m_nPenWidth);
    QPainterPathStroker ps{pen};
    path = ps.createStroke(path);
    return path;
}
