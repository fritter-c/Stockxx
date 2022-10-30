#include "candlemagnifier.h"
#include "qpainter.h"
#include "qpen.h"
#include <QGraphicsBlurEffect>

CandleMagnifier::CandleMagnifier(QGraphicsItem* parent) : QGraphicsItem{parent}
{

    setOpacity(0.85);
    setAcceptHoverEvents(true);
    setFlags(ItemIsMovable | ItemIsPanel | ItemIgnoresParentOpacity);
    setParentItem(parent);

}

void
CandleMagnifier::bringBack()
{
    setPos(0,0);
}

void CandleMagnifier::changeSize(QSizeF newSize)
{
    qreal viewSize = fmin(newSize.width(), newSize.height());
    prepareGeometryChange();
    m_rHeight = viewSize/2.5;
    m_rWidth  = viewSize/2.5;


}

void CandleMagnifier::setSelectedCandle(Candle * newCandle)
{
    m_selectedCandle = newCandle;
    update();
}

QRectF CandleMagnifier::boundingRect() const
{
    return QRectF(0,0,m_rWidth,m_rHeight);
}

qreal
inline CandleMagnifier::YAtPrice(double price, double space, double low, double span){
return -(price - low) * (space - 0.1 * m_rHeight) / span + space;
}
void CandleMagnifier::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    if (m_selectedCandle == nullptr) return;
    QPen penBorder{Qt::black, 3};
    painter->setPen(penBorder);
    QRectF rect{0,0,m_rWidth,m_rHeight};
    QBrush brush{QColor::fromRgb(229,229,229)};
    painter->drawRect(rect);
    painter->fillRect(rect,brush);;
    qreal nSpace{m_rHeight - 0.2 * m_rHeight};
    double dSpan{m_selectedCandle->dHigh - m_selectedCandle->dLow};
    qreal nCandlePos{m_rWidth/2 + 0.1 * m_rWidth};
    QLineF shadow{nCandlePos, m_rHeight - 0.1 * m_rHeight,nCandlePos, 0.1 * m_rHeight};
    QPen penShadow{Qt::black, 2};
    qreal rCandleSize{0.2 * m_rWidth};
    QRectF body;
    QBrush bodyBrush{Qt::SolidPattern};
    QPointF pointOpen{nCandlePos, YAtPrice(m_selectedCandle->dOpen, nSpace, m_selectedCandle->dLow,dSpan)};
    QPointF pointClose{nCandlePos, YAtPrice(m_selectedCandle->dClose, nSpace, m_selectedCandle->dLow,dSpan)};
    if (m_selectedCandle->ct == ctBull)
    {
        bodyBrush.setColor(Qt::green);
        body.setRect(nCandlePos - rCandleSize/2 , pointClose.y(), rCandleSize, pointOpen.y() - pointClose.y());
    }
    else if (m_selectedCandle->ct == ctBear)
    {
        bodyBrush.setColor(Qt::red);
        body.setRect(pointClose.x() - rCandleSize/2, pointOpen.y(), rCandleSize, pointClose.y() - pointOpen.y());
    }
    else
    {
        bodyBrush.setColor(Qt::black);
        body.setRect(nCandlePos - rCandleSize/2, pointOpen.y(), rCandleSize, 0);
    }
    painter->setPen(penShadow);
    painter->drawLine(shadow);
    painter->setBrush(bodyBrush);
    painter->drawRect(body);
    QFont font{painter->font()};
    //font.setPixelSize(12);
    QFontMetrics fm{font};
    QPointF pointDate{m_rHeight/2 - fm.horizontalAdvance("00.00.0000 00:00")/2, static_cast<qreal>(fm.height())};
    painter->drawText(pointDate, m_selectedCandle->dtDate.toString("dd.MM.yyyy hh:mm"));
    QPointF pointVolume{m_rHeight/2 -fm.horizontalAdvance(QString::number(m_selectedCandle->dVolume))/2, m_rHeight - 5};
    painter->drawText(pointVolume, QString::number(m_selectedCandle->dVolume));

}





