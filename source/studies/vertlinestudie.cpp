#include "vertlinestudie.h"

VertLineStudie::VertLineStudie(QObject* manager, qreal x, TimeScaleVisual* ts_Visual, PriceScaleVisual* ps_Visual, QGraphicsItem* parent)
    : CustomStudie(manager, ts_Visual, ps_Visual, parent)
{
    qreal pos;
    m_qi = m_tsVisual->findNearestDate(x, &pos);
    m_tsVisual->addPriceTag(x, Qt::yellow, this);
    setAcceptHoverEvents(true);
}

VertLineStudie::~VertLineStudie()
{
    m_tsVisual->removePriceTag(this);
}

QRectF VertLineStudie::boundingRect() const
{
    return QRectF(m_tsVisual->XAtQuote(m_qi) - m_nPenWidth/2, parentItem()->boundingRect().top(),
                   m_nPenWidth, m_tsVisual->boundingRect().top() - parentItem()->boundingRect().top());
}

void VertLineStudie::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    CustomStudie::paint(painter, option, widget);
    QPen pen{m_mainColor,m_nPenWidth};
    painter->setPen(pen);
    QPointF p1{m_tsVisual->XAtQuote(m_qi), m_tsVisual->boundingRect().top()};
    QPointF p2{m_tsVisual->XAtQuote(m_qi), parentItem()->boundingRect().top()};
    painter->drawLine(p1, p2);
}

void VertLineStudie::colorChanged()
{
    m_tsVisual->updatePriceTag(this, m_tsVisual->XAtQuote(m_qi), m_mainColor);
}
