#include "linestudie.h"

LineStudie::LineStudie(QObject* manager,
                       qreal x, double price, TimeScaleVisual
                       *ts_Visual, PriceScaleVisual *ps_Visual, QGraphicsItem *parent) : CustomStudie{manager,
                                                                                                      ts_Visual, ps_Visual, parent}
{
    qreal rX;
    m_dStartPrice = price;
    m_dEndPrice = price;
    m_qiStartQuote = m_tsVisual->findNearestDate(x, &rX);
    m_qiEndQuote = m_qiStartQuote;
    setAcceptHoverEvents(true);
}

void LineStudie::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    if ((m_dStartPrice != m_dEndPrice) or (m_qiStartQuote != m_qiEndQuote)){
        CustomStudie::paint(painter, option, widget); // clips
        QPointF point1{m_tsVisual->XAtQuote(m_qiStartQuote), m_psVisual->YAtPrice(m_dStartPrice)};
        QPointF point2{m_tsVisual->XAtQuote(m_qiEndQuote), m_psVisual->YAtPrice(m_dEndPrice)};
        QPen blackPen{m_mainColor, m_nPenWidth };
        blackPen.setStyle(m_penStyle);
        painter->setPen(blackPen);
        m_line = {point1, point2};
        painter->drawLine(m_line);
    }

}

void LineStudie::setSecondPrice(QPointF pf)
{
    prepareGeometryChange();
    qreal rX;
    m_qiEndQuote = m_tsVisual->findNearestDate(pf.x(), &rX);
    m_dEndPrice  = m_psVisual->PriceAtY(pf.y());
    update();
}

QPainterPath LineStudie::shape() const
{
    QPointF point1{m_tsVisual->XAtQuote(m_qiStartQuote), m_psVisual->YAtPrice(m_dStartPrice)};
    QPointF point2{m_tsVisual->XAtQuote(m_qiEndQuote), m_psVisual->YAtPrice(m_dEndPrice)};
    QPainterPath path;
    path.moveTo(point1);
    path.lineTo(point2);
    QPen pen;
    pen.setWidth(m_nPenWidth);
    QPainterPathStroker ps{pen};
    path = ps.createStroke(path);
    return path;
}

QRectF LineStudie::boundingRect() const
{
    QPointF point1{m_tsVisual->XAtQuote(m_qiStartQuote), m_psVisual->YAtPrice(m_dStartPrice)};
    QPointF point2{m_tsVisual->XAtQuote(m_qiEndQuote), m_psVisual->YAtPrice(m_dEndPrice)};
    return QRectF(point1, point2).normalized();
}



