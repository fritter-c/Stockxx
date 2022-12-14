#include "graphictitlebar.h"
#include "qbrush.h"
#include "qpainter.h"

GraphicTitlebar::GraphicTitlebar(QGraphicsItem *parent) : QGraphicsItem{parent}
{
    m_parent = parent;
    setAcceptHoverEvents(true);
    setZValue(1);
}

void GraphicTitlebar::setTitle(const QString & newTitle)
{
    m_mainTitle = newTitle.toUpper();
    update();
}

void GraphicTitlebar::setTimeframe(SerieInterval si)
{
    m_mainTimeframe = ToString(si);
    update();
}

void GraphicTitlebar::setCandle(const Candle & newCandle)
{
    m_candle = newCandle;
    update();
}

void GraphicTitlebar::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    m_bHighlight = true;
    update();
}

void GraphicTitlebar::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    m_bHighlight = false;
    update();
}

QRectF GraphicTitlebar::boundingRect() const
{
    QRectF a_rect(0,0, m_parent->boundingRect().width(), c_nTitlebarHeight);
    return a_rect;
}

void GraphicTitlebar::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setClipRect(boundingRect());
    QRectF rect(0,0, m_parent->boundingRect().width(), c_nTitlebarHeight);
    QBrush brush{Qt::black};
    painter->setBrush(brush);

    if (m_bHighlight)
        setOpacity(0.7);
    else{
        setOpacity(0.4);
    }

    painter->drawRect(rect);

    QPen pen{Qt::white};
    painter->setPen(pen);
    QFont font {painter->font()};
    font.setPixelSize(12);
    painter->setFont(font);

    const int c_nHmargin = 5;
    const int c_nVmargin = 2;

    QPointF p(c_nHmargin, boundingRect().bottom() - c_nVmargin);
    painter->drawText(p, m_mainTitle);
    QFontMetricsF metric(font);
    qreal advance {metric.horizontalAdvance(m_mainTitle)};
    QPointF p2(p.x() + c_nHmargin + advance, boundingRect().bottom() - c_nVmargin);
    painter->drawText(p2, m_mainTimeframe);
    if(m_candle != INVALID_CANDLE){
        advance = metric.horizontalAdvance(m_mainTimeframe);

        QPointF p3(p2.x() + c_nHmargin + advance, boundingRect().bottom() - c_nVmargin);
        QString string = "(O:" +
                QString::number(m_candle.dOpen) +
                " H:" + QString::number(m_candle.dHigh) +
                " L:" + QString::number(m_candle.dLow) +
                " C:" + QString::number(m_candle.dClose) +
                " V:" + QString::number(m_candle.dVolume) +
                ")";
        painter->drawText(p3, string);
    }
}
