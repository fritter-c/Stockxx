#include "timescalevisual.h"
#include "pricevisual.h"
#include <QGraphicsSceneHoverEvent>

void TimeScaleVisual::popuplateDateTimes()
{
    QList<Candle*> candles;
    candles = m_price->getCandles();
    m_mapCandles.clear();
    for (long long i {candles.size() - 1}; i >= 0; --i){
        m_dtDateTimes.append(candles[i]->qi);
    }
    nZoom = m_dtDateTimes.size() - 30;

}

void TimeScaleVisual::zoom(int delta)
{
    if (delta > 0){
        if (nZoom + delta/10 < m_dtDateTimes.size() - 1){
            nZoom += delta/10;
            recalculatePositions();
            update();
            m_price->update();
        }
        else if (nZoom < m_dtDateTimes.size() - 1){
            nZoom++;
            recalculatePositions();
            update();
            m_price->update();
        }
    }
    else{
        if ((nZoom + nOffset + delta/10) > 0){
            nZoom += delta/10;
            recalculatePositions();
            update();
            m_price->update();
        }
        else if(nZoom + nOffset > 0){
            nZoom--;
            recalculatePositions();
            update();
            m_price->update();
        }

    }
}

void TimeScaleVisual::recalculatePositions()
{
    m_datePositions.clear();
    QFont font;
    font.setPixelSize(12);
    QFontMetricsF fm{font};
    int nEntrys = m_dtDateTimes.size() - nZoom;
    double nText {fm.horizontalAdvance("00.00.0000")};
    double nSpace{boundingRect().width() - nText};
    double nSpaceNeeded{nEntrys * nText};
    double nSpacing {(nSpace - nSpaceNeeded) / nEntrys};
    double nX{boundingRect().width() - nText - c_rTimeScaleBoldMargin};
    for(long long  i {m_dtDateTimes.size() + nOffset - 1}; i >= nZoom + nOffset; i--)
    {
        QuoteIdentifier strDate = m_dtDateTimes[i];
        m_datePositions.insert(strDate, nX);
        nX = nX - nText - nSpacing;
    }
}

void TimeScaleVisual::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    m_bHighLight = true;
    update();
    event->accept();
}

void TimeScaleVisual::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    m_bHighLight = false;
    update();
    event->accept();
}

void TimeScaleVisual::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    zoom(event->delta());
    event->accept();
}

TimeScaleVisual::TimeScaleVisual(PriceVisual *price, QObject* parent, QGraphicsView* view)
{
    m_price = price;
    m_view = view;
    m_parent = parent;
    setAcceptHoverEvents(true);
    popuplateDateTimes();
}

int TimeScaleVisual::getEntrys()
{
    return m_dtDateTimes.count() - nZoom;
}

void TimeScaleVisual::changeGeometry()
{
    prepareGeometryChange();
}

QRectF TimeScaleVisual::boundingRect() const
{
    return QRectF{0, m_view->height() - c_rTimeScaleHeight,m_view->width() - c_rPriceScaleWidth, c_rTimeScaleHeight };
}

void TimeScaleVisual::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen penBorder{Qt::black, 2};
    painter->setPen(penBorder);
    painter->drawLine(0, m_view->height() - c_rTimeScaleHeight, m_view->width() - c_rPriceScaleWidth, m_view->height() - c_rTimeScaleHeight);
    QPen penTags {Qt::black};
    QFont font;
    font.setPixelSize(12);
    QFontMetricsF fm(font);
    double nText = fm.horizontalAdvance("00.00.0000");
    double nSpace = boundingRect().width() - nText;
    qreal nX = XAtQuote(m_dtDateTimes[m_dtDateTimes.size() - 1 + nOffset]);
    long long nEntrys{m_dtDateTimes.size() - nZoom};
    double nSpaceNeeded = nEntrys * nText;
    double nSpacing = (nSpace - nSpaceNeeded) / nEntrys;
    int nSkip = 1;
    QPointF point(nX, boundingRect().bottom() - c_rTimeScaleBottomMargin);
    if (m_bHighLight)
        font.setBold(true);

    painter->setPen(penTags);
    painter->setFont(font);
    if (nSpacing < nText)
    {
        nSkip = qMax(qCeil((nText + c_rTimeScaleTagMargin)/ (nText + nSpacing)), 2) + 1;
    }
    for(long long i {m_dtDateTimes.size() + nOffset - 1}; i > nZoom + nOffset; i = i - nSkip){
        QString strDate = m_dtDateTimes[i].dtQuoteDate.toString("dd.MM.yyyy");
        nX = XAtQuote(m_dtDateTimes[i]);
        point.rx() = nX;
        qreal h {fm.height()};
        if ((nX + nText) > boundingRect().right()) break;
        painter->drawText(point, strDate);
    }

}

qreal TimeScaleVisual::XAtQuote(QuoteIdentifier quote)
{
    if (m_datePositions.contains(quote))
      {
          return m_datePositions[quote];
      }
      else
      {
          return -1;
      }
}
