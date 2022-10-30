#include "resistancestudie.h"

ResistanceStudie::ResistanceStudie(double price, TimeScaleVisual* ts_Visual, PriceScaleVisual* ps_Visual, QGraphicsItem* parent) : CustomStudie(ts_Visual,ps_Visual,parent)
{
    m_price = price;
    m_psVisual->addPriceTag(m_price, Qt::yellow, this);
}

ResistanceStudie::~ResistanceStudie()
{
    m_psVisual->removePriceTag(this);
}



QRectF ResistanceStudie::boundingRect() const
{
    return QRectF(m_tsVisual->boundingRect().left(),m_psVisual->YAtPrice(m_price),m_tsVisual->boundingRect().right() - (m_tsVisual->boundingRect().left()-m_cPriceScaleMargin) ,2);
}

void ResistanceStudie::updatePrice(double price)
{
    prepareGeometryChange();
    m_price = price;
    m_psVisual->updatePriceTag(this, m_price);
    update();
}



void ResistanceStudie::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPointF point1{m_tsVisual->boundingRect().left(), m_psVisual->YAtPrice(m_price)};
    QPointF point2{m_tsVisual->boundingRect().right() - m_cPriceScaleMargin, m_psVisual->YAtPrice(m_price)};
    QPen blackPen{Qt::yellow, 2};
    painter->setPen(blackPen);
    m_line = {point1, point2};
    painter->drawLine(m_line);

}
