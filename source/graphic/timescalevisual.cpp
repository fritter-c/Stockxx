#include "timescalevisual.h"
#include "colorutils.h"
#include <QGraphicsSceneHoverEvent>

TimeScaleVisual::TimeScaleVisual(CustomIndicator* price, QObject* parent, QGraphicsView* view)
{
    m_price = price;
    m_view = view;
    m_parent = parent;
    setAcceptHoverEvents(true);
    popuplateDateTimes();
    m_price->addSubscriber(this);
}
void TimeScaleVisual::popuplateDateTimes()
{
    m_price->PriorAll();
    for (long long i {0}; i < m_price->Size(); ++i){
        m_dtDateTimes.append(m_price->Quote());
        m_price->Next();
    }
    if(m_dtDateTimes.size() > 30)
        nZoom = m_dtDateTimes.size() - 30;
    else
        nZoom = 0;
    m_nFirstIndex = nZoom - nOffset;
}

void TimeScaleVisual::recalculatePositions()
{
    QFont font;
    font.setPixelSize(12);
    QFontMetricsF fm{font};
    int nEntrys = m_dtDateTimes.size() - nZoom;
    double nText;
    if (m_price->Interval() == siDaily){
         nText = fm.horizontalAdvance("00.00.0000");
    }
    else{
        nText = fm.horizontalAdvance("00.00 00:00");
    }
    double nSpace{boundingRect().width() - nText};
    double nSpaceNeeded{nEntrys * nText};
    double nSpacing {(nSpace - nSpaceNeeded) / nEntrys};
    double nX{0};
    m_rFirst = nX;
    m_rSpacing = (nText + nSpacing);
    m_nFirstIndex = nZoom - nOffset;
    if((m_nFirstIndex < m_dtDateTimes.size()) &&
        (m_nFirstIndex > 0) && (m_dtDateTimes.size())){

        m_nFirstID = m_dtDateTimes[m_nFirstIndex].id;
        m_rLast = m_rFirst + nEntrys * m_rSpacing;
        m_nLastID = m_dtDateTimes[nZoom - nOffset].id;
    }
}

void TimeScaleVisual::OnNewData(size_t start)
{
    if(start == 0){
        popuplateDateTimes();
        recalculatePositions();
        if(m_price->visualParent())
            m_price->visualParent()->update();
        update();
    }
}
void TimeScaleVisual::zoom(int delta){
    if (delta > 0){
        if (nZoom + delta/10 < m_dtDateTimes.size() - 1){
            nZoom += delta/10;
            recalculatePositions();
            if(m_price->visualParent())
                m_price->visualParent()->update();
            update();

        }
        else if (nZoom < m_dtDateTimes.size() - 1){
            nZoom++;
            recalculatePositions();
            if(m_price->visualParent())
                m_price->visualParent()->update();
            update();

        }
    }
    else{
        if ((nZoom - nOffset + delta/10) > 0){
            nZoom += delta/10;
            recalculatePositions();
            if(m_price->visualParent())
                m_price->visualParent()->update();
            update();         
        }
        else if(nZoom - nOffset > 0){
            nZoom--;
            recalculatePositions();
            if(m_price->visualParent())
                m_price->visualParent()->update();
            update();          
        }
    }
}

void TimeScaleVisual::paintTimeTags(QPainter * painter, TimeTag tg)
{
    painter->setClipRect(boundingRect());
    const qreal rRectMargin = 2;
    QString date{tg.iq.dtQuoteDate.toString("dd.MM.yyyy hh.mm")};
    QFont font{painter->font()};
    QFontMetricsF fm{font};
    qreal rAdvance{fm.horizontalAdvance(date)};
    QPointF p1 {XAtQuote(tg.iq) - rAdvance/2, boundingRect().bottom() - c_rTimeScaleBottomMargin};
    QPointF p2 {XAtQuote(tg.iq) - rAdvance/2 - rRectMargin, boundingRect().top()};
    QBrush brush{tg.color};
    painter->setBrush(brush);
    QRectF rect{p2, QSizeF{rAdvance + 2 * rRectMargin, boundingRect().bottom() - p2.y()}};
    QPen pen {Qt::black, 1};
    painter->setPen(pen);
    painter->drawRect(rect);
    if (isDarkColor(tg.color)){
        QPen penText{Qt::white};
        painter->setPen(penText);
    }
    else{
        QPen penText{Qt::black};
        painter->setPen(penText);
    }
    painter->drawText(p1, date);
}

void TimeScaleVisual::moveTime(int x)
{
    if (x < 0){
        if ((nOffset + x) >= 0){
            nOffset += x;
            recalculatePositions();
            update();
        }
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
    if(x <= boundingRect().width()){
        int nTime = round(x / m_rSpacing);
        if ((nTime + m_nFirstIndex < m_dtDateTimes.size()) and
            (nTime < getEntrys()) and
           ((nTime + m_nFirstIndex) > 0)){
            *pos = m_rFirst + nTime * m_rSpacing;
            return m_dtDateTimes[nTime + m_nFirstIndex];
        }
        else{
            *pos = m_rLast;
            if (m_dtDateTimes.size())
                return m_dtDateTimes.last();
        }
   }
   *pos = INVALID_DOUBLE;
   return INVALID_QUOTE;
}
QuoteIdentifier TimeScaleVisual::findNearestDate(qreal x)
{
    if(x <= boundingRect().width()){
        int nTime = round(x / m_rSpacing);
        if ((nTime + m_nFirstIndex < m_dtDateTimes.size()) and
            (nTime < getEntrys()) and
           ((nTime + m_nFirstIndex) > 0)){
            return m_dtDateTimes[nTime + m_nFirstIndex];
        }
        else{
            if (m_dtDateTimes.size())
                return m_dtDateTimes.last();
        }
   }
   return INVALID_QUOTE;
}

QuoteIdentifier TimeScaleVisual::getFirstQuote()
{
    return m_dtDateTimes[m_nFirstIndex];
}

void TimeScaleVisual::addPriceTag(qreal x, QColor color, QGraphicsItem *sender)
{
    m_timeTags.insert(sender, {findNearestDate(x), color});
    update();
}

void TimeScaleVisual::removePriceTag(QGraphicsItem *sender)
{
    if (m_timeTags.contains(sender)){
        m_timeTags.remove(sender);
        update();
    }
}

void TimeScaleVisual::updatePriceTag(QGraphicsItem *sender, qreal x, QColor color)
{
    if (m_timeTags.contains(sender)){
        m_timeTags[sender].iq = findNearestDate(x);
        m_timeTags[sender].color = color;
        update();
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

TimeScaleVisual::~TimeScaleVisual()
{
    m_hashDates.clear();
    m_drawnPositions.clear();
    m_dtDateTimes.clear();
    m_timeTags.clear();
    m_price->removeSubscriber(this);
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
    double nText;
    bool bIntraday{!(m_price->Interval() == siDaily)};
    if (!bIntraday){
         nText = fm.horizontalAdvance("00.00.0000");
    }
    else{
        nText = fm.horizontalAdvance("00.00 00:00");
    }
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
    for(long long i {m_nFirstIndex}; i < m_nFirstIndex + nEntrys; i = i + nSkip){
        QString strDate{};
        if (bIntraday)
            strDate = m_dtDateTimes[i].dtQuoteDate.toString("dd.MM hh:mm");
        else
           strDate = m_dtDateTimes[i].dtQuoteDate.toString("dd.MM.yyyy");
        point.rx() = nX;
        if ((nX + nText) > boundingRect().right()) break;
        painter->drawText(point, strDate);
        nX += nSkip * m_rSpacing;
    }
    QHashIterator<QGraphicsItem*, TimeTag> i(m_timeTags);
    while(i.hasNext()){
        i.next();
        if (i.key()->isVisible())
            paintTimeTags(painter, i.value());
    }
}

qreal TimeScaleVisual::XAtQuote(QuoteIdentifier quote)
{
    long long nTimes {static_cast<long long>(m_nFirstID - quote.id )};
    return m_rFirst + nTimes * m_rSpacing;
}
