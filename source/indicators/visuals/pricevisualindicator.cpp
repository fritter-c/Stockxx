#include "pricevisualindicator.h"
#include "indicatormanager.h"

PriceVisualIndicator::PriceVisualIndicator(TimeScaleVisual* timescale, PriceScaleVisual* pricescale,
    PriceIndicator* data, QGraphicsView *view, QObject* manager, QGraphicsItem* parent)
    : CustomVisualIndicator(timescale, pricescale,data, view, manager, parent)
{
    m_data = data;
    m_pgVisual = new PriceGuide(this);
    m_tgVisual = new TimeGuideVisual(this);
    m_pgVisual->setZValue(1);
    m_tgVisual->setZValue(1);
    m_pgVisual->setVisible(false);
    m_tgVisual->setVisible(false);
}

void PriceVisualIndicator::loadParams(IndicatorVisualParams)
{

}

PriceVisualIndicator::~PriceVisualIndicator()
{
    delete m_pgVisual; //necessário remover antes para deletar a tag
    IndicatorManager::Instance().scheduleDeletion(m_data->ID());
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
    bool bPainted{false};
    int nEntrys {m_tsVisual->getEntrys()};
    int nCandlesPainted{0};

    if(!(nEntrys > 0)) return;

    qreal nSpace{boundingRect().width()};
    qreal rCandleSize = fmin(100,(nSpace / nEntrys) - qMax(200/nEntrys, 5));
    bool bBody{rCandleSize >= 2};
    QPen pen {Qt::black,  m_dPenWidth};
    painter->setPen(pen);
    if (m_bHighlight)
        painter->setOpacity(0.5);
    m_data ->PriorAll();

    qreal rFirstPos{m_tsVisual->getFirstPos()};
    qreal rSpacing{m_tsVisual->getSpacing()};
    QuoteIdentifier qiFirstQuote{m_tsVisual->getFirstQuote()};
    m_data->GoToQuote(qiFirstQuote);
    m_dCandleSize = rCandleSize;
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
         nCandlesPainted++;
    } while(m_data->Next() and (nCandlesPainted < nEntrys));

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
    if (m_pgVisual != nullptr) {
        m_pgVisual->geometryChanged();
    }
    if (m_tgVisual != nullptr) {
       m_tgVisual->geometryChanged();
    }
}

void PriceVisualIndicator::toggleCross()
{
    m_pgVisual->setVisible(not m_pgVisual->isVisible());
    m_tgVisual->setVisible(not m_tgVisual->isVisible());
    m_psVisual->update(); //atuliza a tag do cross
}

SerieInterval PriceVisualIndicator::interval() const
{
    return m_data->Interval();
}

void PriceVisualIndicator::toggleRandomClose(bool)
{
}

bool PriceVisualIndicator::contains(const QPointF &point) const
{

    qreal pos;
    QPointF localpoint{point};
    QuoteIdentifier qi = m_tsVisual->findNearestDate(localpoint.x(), &pos);
    m_data->GoToQuote(qi);
    Candle candle{m_data->Candle()};
    QPointF pointHigh, pointLow, pointOpen, pointClose;
    qreal x{m_tsVisual->XAtQuote(qi)};

    pointHigh.ry() = m_psVisual->YAtPrice(candle.dHigh);
    pointHigh.rx() = x;

    pointLow.ry() = m_psVisual->YAtPrice(candle.dLow);
    pointLow.rx() = x;

    pointOpen.ry() = m_psVisual->YAtPrice(candle.dOpen);
    pointOpen.rx() = x;

    pointClose.ry() = m_psVisual->YAtPrice(candle.dClose);
    pointClose.rx() = x;

    if (m_dCandleSize >= 2){
        QRectF body;
        if (candle.ct == ctBull)
        {
            body.setRect(pointClose.x() - m_dCandleSize/2 , pointClose.y(), m_dCandleSize, pointOpen.y() - pointClose.y());
        }
        else if (candle.ct == ctBear)
        {
            body.setRect(pointClose.x() - m_dCandleSize/2, pointOpen.y(), m_dCandleSize, pointClose.y() - pointOpen.y());
        }
        else
        {
            body.setRect(pointClose.x() - m_dCandleSize/2, pointOpen.y(), m_dCandleSize, 0);
        }
        if (body.contains(point)){
            return true;
        }
        if ((abs((point.x() - x))< m_dPenWidth) and ((point.y() > pointHigh.ry()) and (point.y() < pointLow.ry())))
            return true;
    }
    else{
        if ((abs((point.x() - x)) < m_dPenWidth) and ((point.y() > pointHigh.ry()) and (point.y() < pointLow.ry())))
            return true;
    }
    return false;

}
