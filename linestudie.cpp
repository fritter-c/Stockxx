#include "linestudie.h"

LineStudie::LineStudie(qreal x, double price, TimeScaleVisual *ts_Visual, PriceScaleVisual *ps_Visual, QGraphicsItem *parent) : CustomStudie{ts_Visual, ps_Visual, parent}
{
    qreal rX;
    m_dStartPrice = price;
    m_dEndPrice = price;
    m_qiStartQuote = m_tsVisual->findNearestDate(x, &rX);
    m_qiEndQuote = m_qiStartQuote;
}

QRectF LineStudie::boundingRect() const
{
    QPointF point1{0,0};
    QPointF point2{0,0};

    if ((m_tsVisual->XAtQuote(m_qiStartQuote) > 0) and (m_tsVisual->XAtQuote(m_qiEndQuote) > 0)){
        point1 = QPointF(m_tsVisual->XAtQuote(m_qiStartQuote), m_psVisual->YAtPrice(m_dStartPrice));
        point2 = QPointF(m_tsVisual->XAtQuote(m_qiEndQuote), m_psVisual->YAtPrice(m_dEndPrice));
    }
    else if (m_tsVisual->XAtQuote(m_qiStartQuote) > 0){
        point1 = QPointF(m_tsVisual->XAtQuote(m_qiStartQuote), m_psVisual->YAtPrice(m_dStartPrice));
        point2 = QPointF(m_tsVisual->boundingRect().right(), m_psVisual->YAtPrice(m_dEndPrice));
    }
    QRectF rect{point1, point2};
    //rect.setHeight(2);
    return rect.normalized();
}

void LineStudie::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if ((m_dStartPrice != m_dEndPrice) or (m_qiStartQuote != m_qiEndQuote)){
        if ((m_tsVisual->XAtQuote(m_qiStartQuote) > 0) and (m_tsVisual->XAtQuote(m_qiEndQuote) > 0)){
            QPointF point1{m_tsVisual->XAtQuote(m_qiStartQuote), m_psVisual->YAtPrice(m_dStartPrice)};
            QPointF point2{m_tsVisual->XAtQuote(m_qiEndQuote), m_psVisual->YAtPrice(m_dEndPrice)};
            QPen blackPen{Qt::yellow, 2};
            painter->setPen(blackPen);
            m_line = {point1, point2};
            painter->drawLine(m_line);
        }
        else if(m_tsVisual->XAtQuote(m_qiStartQuote) > 0){
            QPointF point1{m_tsVisual->XAtQuote(m_qiStartQuote), m_psVisual->YAtPrice(m_dStartPrice)};
            QPointF point2{m_tsVisual->boundingRect().right(), m_psVisual->YAtPrice(m_dEndPrice)}; // desenha até o final do gráfico
            QPen blackPen{Qt::yellow, 2};
            painter->setPen(blackPen);
            m_line = {point1, point2};
            painter->drawLine(m_line);
        }
    }
}

void LineStudie::updateLastPos(QPointF pf)
{
    prepareGeometryChange();
    qreal rX;
    m_qiEndQuote = m_tsVisual->findNearestDate(pf.x(), &rX);
    m_dEndPrice  = m_psVisual->PriceAtY(pf.y());
    update();
}

