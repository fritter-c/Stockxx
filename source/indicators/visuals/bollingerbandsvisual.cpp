#include "bollingerbandsvisual.h"
#include "indicatormanager.h"

BollingerBandsVisual::BollingerBandsVisual(IndicatorVisualParams params, TimeScaleVisual* timescale, PriceScaleVisual* pricescale,
    BollingerBands* data,QGraphicsView *view, QObject* manager, QGraphicsItem *parent) :
    CustomVisualIndicator{ timescale, pricescale, data, view, manager, parent }
{
    BollingerBandsVisual::loadParams(params);
    m_data = data;
    m_data->addSubscriber(this);
}
BollingerBandsVisual::~BollingerBandsVisual()
{
    m_data->removeSubscriber(this);
    IndicatorManager::Instance().scheduleDeletion(m_data->ID());
}
void BollingerBandsVisual::changeGeometry()
{
    prepareGeometryChange();
}
QRectF BollingerBandsVisual::boundingRect() const
{
    return QRectF(0, 0,
        m_view->width() - m_psVisual->c_PriceScaleFWidth,
        m_view->height() - m_tsVisual->c_rTimeScaleHeight);
}
void BollingerBandsVisual::loadParams(IndicatorVisualParams params)
{
    m_style = *static_cast<BasicIndicatorStyle*>(params[0]);
    delete params[0];
}
void BollingerBandsVisual::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{

    QPen pen;
    pen.setStyle(m_style.penStyle);
    pen.setColor(m_style.color);
    pen.setWidth(m_style.width);
    painter->setPen(pen);
    painter->setClipRect(boundingRect());

    int nEntrys{ m_tsVisual->getEntrys() };
    if (!(nEntrys and m_data->Size())) return;

    m_data->PriorAll();
    bool bNext{ true };


    QuoteIdentifier qiFirstQuote{ m_tsVisual->getFirstQuote() };
    qreal rSpacing{ m_tsVisual->getSpacing() };
    int nCandlesPainted{ 0 };
    if (m_bHighlight)
        painter->setOpacity(0.5);
    m_data->GoToQuote(qiFirstQuote);

    // traversa até o primeiro valor válido
    while (!m_data->Valid() and m_data->Next()){

    };
    qreal rFirstPos{ m_tsVisual->XAtQuote(m_data->Quote()) };
    do {
        QPointF startMa;
        QPointF endMa;

        QPointF startUpper;
        QPointF endUpper;

        QPointF startLower;
        QPointF endLower;

        QVector<double> values{m_data->Values()};
        startMa.ry() = m_psVisual->YAtPrice(values[1]);
        startMa.rx() = rFirstPos;

        startUpper.ry() = m_psVisual->YAtPrice(values[0]);
        startUpper.rx() = rFirstPos;

        startLower.ry() = m_psVisual->YAtPrice(values[2]);
        startLower.rx() = rFirstPos;

        bNext = m_data->Next();
        if (!bNext) break;
        values = m_data->Values();

        endMa.ry() = m_psVisual->YAtPrice(values[1]);
        endMa.rx() = rFirstPos + rSpacing;

        endUpper.ry() = m_psVisual->YAtPrice(values[0]);
        endUpper.rx() = rFirstPos + rSpacing;

        endLower.ry() = m_psVisual->YAtPrice(values[2]);
        endLower.rx() = rFirstPos + rSpacing;

        painter->drawLine(startMa, endMa); // média
             painter->drawLine(startUpper, endUpper); // banda superior
                  painter->drawLine(startLower, endLower); // banda inferior

        rFirstPos += rSpacing;
        nCandlesPainted++;

    } while (bNext and (nCandlesPainted < nEntrys));
}
bool BollingerBandsVisual::contains(const QPointF& point) const
{
    qreal pos;
    QPointF localpoint{ point };
    QuoteIdentifier qi = m_tsVisual->findNearestDate(localpoint.x(), &pos);
    m_data->GoToQuote(qi);
    QPointF startMa;
    QPointF endMa;

    QPointF startUpper;
    QPointF endUpper;

    QPointF startLower;
    QPointF endLower;
    //volta um para desenhar uma linha completa
    m_data->Prior();
    qreal rFirstPos{ m_tsVisual->XAtQuote(m_data->Quote()) };
    qreal rSpacing{ m_tsVisual->getSpacing() };
    QPainterPath path;
    int nIndex{ 0 };

    // desenha virtualmente dois segmentos
    while (nIndex < 2) {
        QVector<double> values{m_data->Values()};
        startMa.ry() = m_psVisual->YAtPrice(values[1]);
        startMa.rx() = rFirstPos;

        startUpper.ry() = m_psVisual->YAtPrice(values[0]);
        startUpper.rx() = rFirstPos;

        startLower.ry() = m_psVisual->YAtPrice(values[2]);
        startLower.rx() = rFirstPos;

        m_data->Next();

        values = m_data->Values();

        endMa.ry() = m_psVisual->YAtPrice(values[1]);
        endMa.rx() = rFirstPos + rSpacing;

        endUpper.ry() = m_psVisual->YAtPrice(values[0]);
        endUpper.rx() = rFirstPos + rSpacing;

        endLower.ry() = m_psVisual->YAtPrice(values[2]);
        endLower.rx() = rFirstPos + rSpacing;

        path.moveTo(startMa);
        path.lineTo(endMa);
        path.moveTo(startUpper);
        path.lineTo(endUpper);
        path.moveTo(startLower);
        path.lineTo(endLower);
        nIndex++;
        rFirstPos += rSpacing;
    }
    QPen pen;
    pen.setWidth(m_style.width);
    QPainterPathStroker stroker{ pen };
    return stroker.createStroke(path).contains(point);
}
