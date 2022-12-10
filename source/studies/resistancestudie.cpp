#include "resistancestudie.h"

ResistanceStudie::ResistanceStudie(QObject* manager, double price, TimeScaleVisual* ts_Visual,
                                   PriceScaleVisual* ps_Visual, QGraphicsItem* parent) : CustomStudie(manager, ts_Visual,ps_Visual,parent)
{
    m_price = price;
    m_psVisual->addPriceTag(m_price, Qt::yellow, this);
    setAcceptHoverEvents(true);
}

ResistanceStudie::~ResistanceStudie()
{
    m_psVisual->removePriceTag(this);
}

void ResistanceStudie::colorChanged()
{
    m_psVisual->updatePriceTag(this, m_price, m_mainColor);
}

QRectF ResistanceStudie::boundingRect() const
{
    return QRectF(m_tsVisual->boundingRect().left(),m_psVisual->YAtPrice(m_price) - m_nPenWidth / 2
                  ,m_tsVisual->boundingRect().right() - (m_tsVisual->boundingRect().left()-m_cPriceScaleMargin) ,m_nPenWidth);
}


QPainterPath ResistanceStudie::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}


void ResistanceStudie::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    CustomStudie::paint(painter, option, widget); // clips
    QPointF point1{m_tsVisual->boundingRect().left(), m_psVisual->YAtPrice(m_price)};
    QPointF point2{m_tsVisual->boundingRect().right() - m_cPriceScaleMargin, m_psVisual->YAtPrice(m_price)};
    QPen blackPen{m_mainColor, m_nPenWidth};
    blackPen.setStyle(m_penStyle);
    painter->setPen(blackPen);
    m_line = {point1, point2};
    painter->drawLine(m_line);
}
