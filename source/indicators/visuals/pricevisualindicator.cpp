#include "pricevisualindicator.h"
#include "graphicmanager.h"

void PriceVisualIndicator::hoverMoveEvent(QGraphicsSceneHoverEvent* event)
{
    Candle candle;
    qreal pos;
    if (m_data->GoToQuote(m_tsVisual->findNearestDate(event->pos().x(), &pos)))
        candle = m_data->Candle();
    if (m_hoveredCandle == Candle()) {
        m_hoveredCandle = candle;
        dynamic_cast<GraphicManager*>(m_manager)->candleHoveredChanged();
    }
    else if ((m_hoveredCandle != candle)) {
        m_hoveredCandle = candle;
        dynamic_cast<GraphicManager*>(m_manager)->candleHoveredChanged();
    }
    if (event->pos().y() < boundingRect().bottom())
    {
        //m_pgVisual->setRY(event->pos().y());
    }
    if (event->pos().x() < boundingRect().right())
    {
        // m_tgVisual->setRX(event->pos().x());
    }
    QGraphicsItem::hoverMoveEvent(event);
}

void PriceVisualIndicator::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->pos().y() < boundingRect().bottom())
    {
        //m_pgVisual->setRY(event->pos().y());
    }
    if (event->pos().x() < boundingRect().right())
    {
        //m_tgVisual->setRX(event->pos().x());
    }
}

PriceVisualIndicator::PriceVisualIndicator(TimeScaleVisual* timescale, PriceScaleVisual* pricescale,
    PriceIndicator* data, QGraphicsView *view, QObject* manager, QGraphicsItem* parent)
    : CustomVisualIndicator(timescale, pricescale,data, view, manager, parent)
{
    m_data = data;
    setAcceptHoverEvents(true);
}

PriceVisualIndicator::~PriceVisualIndicator()
{
}

QRectF PriceVisualIndicator::boundingRect() const
{
    return QRectF(0, 0,
                  m_view->width() - m_psVisual->c_PriceScaleFWidth,
                  m_view->height()- m_tsVisual->c_rTimeScaleHeight);
}

void PriceVisualIndicator::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setClipRect(boundingRect());
    QPointF pointHigh, pointLow, pointOpen, pointClose;
    QBrush brush {Qt::SolidPattern};

    bool bFirst{true};
    bool bPainted{false};

    int nEntrys {m_tsVisual->getEntrys()};

    if(!(nEntrys > 0)) return;

    qreal nSpace{boundingRect().width()};
    qreal rCandleSize = fmin(100,(nSpace / nEntrys) - qMax(200/nEntrys, 5));
    bool bBody{rCandleSize >= 2};
    QPen pen {Qt::black, 1};
    painter->setPen(pen);
    m_data ->PriorAll();

    qreal rFirstPos{m_tsVisual->getFirstPos()};
    qreal rSpacing{m_tsVisual->getSpacing()};
    QuoteIdentifier qiFirstQuote{m_tsVisual->getFirstQuote()};
    m_data->GoToQuote(qiFirstQuote);
    do{
        Candle candle{m_data->Candle()};
        pointHigh.ry() = m_psVisual->YAtPrice(m_data->High());
        pointHigh.rx() = rFirstPos;

        pointLow.ry() = m_psVisual->YAtPrice(m_data->Low());
        pointLow.rx() = pointHigh.rx();

        pointOpen.ry() = m_psVisual->YAtPrice(m_data->Open());
        pointOpen.rx() = pointHigh.rx();

        pointClose.ry() = m_psVisual->YAtPrice(m_data->Close());
        pointClose.rx() = pointHigh.rx();

        if ((bPainted) and (pointHigh.rx() < 0)) break;


        if (pointHigh.rx() > 0)
        {
            bPainted = true;
            QLineF shadow{pointHigh, pointLow};
            // Desenha a linha (sombra, pavio) do candle
            painter->drawLine(shadow);
            if (bBody){
                QRectF body;
                if (candle.ct == ctBull)
                {
                    brush.setColor(Qt::green);
                    body.setRect(pointClose.x() - rCandleSize/2 , pointClose.y(), rCandleSize, pointOpen.y() - pointClose.y());
                }
                else if (candle.ct == ctBear)
                {
                    brush.setColor(Qt::red);
                    body.setRect(pointClose.x() - rCandleSize/2, pointOpen.y(), rCandleSize, pointClose.y() - pointOpen.y());
                }
                else
                {
                    brush.setColor(Qt::black);
                    body.setRect(pointClose.x() - rCandleSize/2, pointOpen.y(), rCandleSize, 0);
                }
                painter->setBrush(brush);
                painter->drawRect(body);
            }

         }
         rFirstPos += rSpacing;

    } while(m_data->Next());

}

PriceScaleVisual* PriceVisualIndicator::GetPriceScale()
{
    return m_psVisual;
}

TimeScaleVisual* PriceVisualIndicator::GetTimeScale()
{
    return m_tsVisual;
}

PriceIndicator* PriceVisualIndicator::GetPrice()
{
    return m_data;
}

double PriceVisualIndicator::Max()
{
    return m_data->Max();
}

double PriceVisualIndicator::Min()
{
    return m_data->Min();
}

CandleArray PriceVisualIndicator::getCandles()
{
    return m_data->GetCandles();
}

Candle PriceVisualIndicator::getHoveredCandle()
{
    return m_hoveredCandle;
}

void PriceVisualIndicator::changeGeometry()
{
    prepareGeometryChange();
    //if (m_pgVisual != nullptr) {
    //    m_pgVisual->geometryChanged();
    //}
    //if (m_tgVisual != nullptr) {
    //    m_tgVisual->geometryChanged();
    //}
}

void PriceVisualIndicator::toggleCross()
{
}

SerieInterval PriceVisualIndicator::interval() const
{
    return m_data->Interval();
}

void PriceVisualIndicator::toggleRandomClose(bool)
{
}
