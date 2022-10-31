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
    m_nFirstIndex = nZoom - nOffset;

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

void TimeScaleVisual::moveTime(int x)
{
    if (x < 0){
        if ((nOffset + x) >= 0)
            nOffset += x;
            recalculatePositions();
            update();
    }
    else if (x > 0){
        if ((nOffset + x) <= nZoom){
            nOffset += x;
            recalculatePositions();
            update();
        }
    }
}

QuoteIdentifier TimeScaleVisual::findNearestDate(qreal x, qreal *pos)
{
    qreal actualX{boundingRect().width() - x};
    int nTime{std::lround((actualX / m_rSpacing)) + 1};

    if (nTime + m_nFirstIndex < m_dtDateTimes.size()){
        *pos = m_rFirst + nTime * m_rSpacing;
        return m_dtDateTimes[nTime + m_nFirstIndex];
    }
    else{
        *pos = m_rLast;
        return m_dtDateTimes.last();
    }
}

QuoteIdentifier TimeScaleVisual::getFirstQuote()
{
    return m_dtDateTimes[m_nFirstID];
}

void TimeScaleVisual::recalculatePositions()
{
    QFont font;
    font.setPixelSize(12);
    QFontMetricsF fm{font};
    int nEntrys = m_dtDateTimes.size() - nZoom;
    double nText {fm.horizontalAdvance("00.00.0000")};
    double nSpace{boundingRect().width() - nText};
    double nSpaceNeeded{nEntrys * nText};
    double nSpacing {(nSpace - nSpaceNeeded) / nEntrys};
    double nX{boundingRect().width() - nText - c_rTimeScaleBoldMargin};
    m_rFirst = nX;
    m_rSpacing = (-nText-nSpacing);
    m_nFirstIndex = m_dtDateTimes.size() - nOffset - 1;
    m_nFirstID = m_dtDateTimes[m_nFirstIndex].id;
    m_rLast = m_rFirst + nEntrys * m_rSpacing;
    m_nLastID = m_dtDateTimes[nZoom - nOffset].id;
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

qreal TimeScaleVisual::getFirstPos()
{
    return m_rFirst;
}

qreal TimeScaleVisual::getSpacing()
{
    return m_rSpacing;
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
    qreal nX;
    long long nEntrys{m_dtDateTimes.size() - nZoom};
    double nSpaceNeeded = nEntrys * nText;
    double nSpacing = (nSpace - nSpaceNeeded) / nEntrys;
    int nSkip = 1;
    QPointF point(0, boundingRect().bottom() - c_rTimeScaleBottomMargin);
    if (m_bHighLight)
        font.setBold(true);

    painter->setPen(penTags);
    painter->setFont(font);
    if (nSpacing < nText)
    {
        nSkip = qMax(qCeil((nText + c_rTimeScaleTagMargin)/ (nText + nSpacing)), 2) + 1;
    }
    nX = m_rFirst;
    for(long long i {m_nFirstIndex}; i > nZoom - nOffset; i = i - nSkip){
        QString strDate = m_dtDateTimes[i].dtQuoteDate.toString("dd.MM.yyyy");
        point.rx() = nX;
        if ((nX + nText) > boundingRect().right()) break;
        painter->drawText(point, strDate);
        nX += nSkip * m_rSpacing;
    }
}

qreal TimeScaleVisual::XAtQuote(QuoteIdentifier quote)
{
    if (quote.id > m_nLastID){
        return -1;
    }
    else{
        uint64_t nTimes {quote.id - m_nFirstID};
        return m_rFirst + nTimes * m_rSpacing;
    }
}
