#include "pricevisual.h"
#include "candle.h"
#include "qgraphicssceneevent.h"
#include "graphicmanager.h"


size_t PriceVisual::findNearestCandle(qreal mousePos)
{
    size_t i{0};
    while((mousePos < m_candlePos[i]) && (i < m_candlePos.size() - 1)){
        i++;
    }
    if (i > 0){
        qreal x1 {m_candlePos[i]};
        qreal x2 {m_candlePos[i-1]};
        if (abs(x1 - mousePos) > abs(x2 - mousePos)) return i-1;
        else return i;
    }
    else{
        return i;
    }
}

PriceVisual::PriceVisual(CustomPrice *customPrice, QObject *parent, QGraphicsView *view) : IndicatorVisual(customPrice, parent, view)
{
    m_priceCalc = new PriceCalc(customPrice);
    m_data = m_priceCalc;
    m_priceCalc->CreateIndicatorsValues();
    m_tsVisual = new TimeScaleVisual(this, parent, view);
    m_psVisual = new PriceScaleVisual(this, parent, view);
    m_tsVisual->recalculatePositions();
    setAcceptHoverEvents(true);
    m_parent = parent;
    m_pgVisual = new PriceGuide(this);
    m_tgVisual = new TimeGuideVisual(this);
    m_pgVisual->setVisible(false);
    m_tgVisual->setVisible(false);
    setFlag(ItemClipsChildrenToShape);
}

QRectF PriceVisual::boundingRect() const
{
    return QRectF(0, 0,
                  m_view->width() - m_psVisual->c_PriceScaleFWidth,
                  m_view->height()- m_tsVisual->c_rTimeScaleHeight);
}

void PriceVisual::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPointF pointHigh, pointLow, pointOpen, pointClose;
    QBrush brush {Qt::SolidPattern};
    QPen pen {Qt::black, 1};
    bool bNext{true};
    bool bFirst{true};
    bool bPainted{false};
    painter->setPen(pen);
    int nEntrys {m_tsVisual->getEntrys()};
    qreal nSpace{boundingRect().width()};
    qreal rCandleSize = fmin(40,(nSpace / nEntrys) - qMax(200/nEntrys, 5));
    m_priceCalc->PriorAll();
    Candle* candle;
    m_candlesDrawn.clear();
    m_candlePos.clear();
    while(bNext){
        candle = m_priceCalc->getCandle();
        pointHigh.ry() = m_psVisual->YAtPrice(m_priceCalc->High());
        pointHigh.rx() = m_tsVisual->XAtQuote(candle->qi);

        pointLow.ry() = m_psVisual->YAtPrice(m_priceCalc->Low());
        pointLow.rx() = pointHigh.rx();

        pointOpen.ry() = m_psVisual->YAtPrice(m_priceCalc->Open());
        pointOpen.rx() = pointHigh.rx();

        pointClose.ry() = m_psVisual->YAtPrice(m_priceCalc->Close());
        pointClose.rx() = pointHigh.rx();

        if ((bPainted) and (pointHigh.rx() < 0)) break;


        if (pointHigh.rx() > 0)
        {
            m_candlesDrawn.append(candle);
            m_candlePos.append(pointHigh.rx());
            bPainted = true;
            QLineF shadow{pointHigh, pointLow};
            // Desenha a linha (sombra, pavio) do candle
            painter->drawLine(shadow);
            if (rCandleSize >= 2){
                QRectF body;
                if (candle->ct == ctBull)
                {

                    brush.setColor(Qt::green);
                    body.setRect(pointClose.x() - rCandleSize/2 , pointClose.y(), rCandleSize, pointOpen.y() - pointClose.y());
                }
                else if (candle->ct == ctBear)
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
         bNext = m_priceCalc->Next();

    }
}

PriceScaleVisual *PriceVisual::GetPriceScale()
{
    return m_psVisual;
}

TimeScaleVisual *PriceVisual::GetTimeScale()
{
    return m_tsVisual;
}

PriceCalc *PriceVisual::GetPrice()
{
    return m_priceCalc;
}

double PriceVisual::Max()
{
    return m_priceCalc->Max();
}

double PriceVisual::Min()
{
    return m_priceCalc->Min();
}

QList<Candle *> PriceVisual::getCandles()
{
    return m_priceCalc->getCandles();
}

Candle *PriceVisual::getHoveredCandle()
{
    return hoveredCandle;
}

void PriceVisual::changeGeometry()
{
    IndicatorVisual::changeGeometry();
    m_pgVisual->geometryChanged();
    m_tgVisual->geometryChanged();
}

void PriceVisual::toggleCross()
{
    m_pgVisual->setVisible(not m_pgVisual->isVisible());
    m_tgVisual->setVisible(not m_tgVisual->isVisible());
    m_psVisual->update(); //atuliza a tag do cross
}


void PriceVisual::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    Candle* candle = m_candlesDrawn[findNearestCandle(event->pos().x())];
    if (hoveredCandle == nullptr) {
        hoveredCandle = candle;
        dynamic_cast<GraphicManager*>(m_parent)->candleHoveredChanged();
    }
    else if ((hoveredCandle != candle)){
        hoveredCandle = candle;
        dynamic_cast<GraphicManager*>(m_parent)->candleHoveredChanged();
    }
    if (event->pos().y() < boundingRect().bottom())
    {
        m_pgVisual->setRY(event->pos().y());
    }
    if(event->pos().x() < boundingRect().right())
    {
        m_tgVisual->setRX(event->pos().x());
    }
    QGraphicsItem::hoverMoveEvent(event);
}

void PriceVisual::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->pos().y() < boundingRect().bottom())
    {
        m_pgVisual->setRY(event->pos().y());
    }
    if(event->pos().x() < boundingRect().right())
    {
        m_tgVisual->setRX(event->pos().x());
    }
}

void PriceVisual::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}



