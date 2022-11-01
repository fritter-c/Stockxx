#ifndef CUSTOMSTUDIE_H
#define CUSTOMSTUDIE_H

#include <QGraphicsItem>
#include "pricescalevisual.h"
#include "timescalevisual.h"
#include "StockxxDateUtils.h"

class CustomStudie : public QGraphicsItem
{
protected:
    PriceScaleVisual* m_psVisual;
    TimeScaleVisual* m_tsVisual;
    const qreal m_cPriceScaleMargin = 2;
    QuoteIdentifier m_qiStartQuote{ZERO_DATE};
    QuoteIdentifier m_qiEndQuote{ZERO_DATE};
    double m_dStartPrice{0};
    double m_dEndPrice{0};
public:
    CustomStudie(TimeScaleVisual* ts_Visual, PriceScaleVisual* ps_Visual, QGraphicsItem* parent=nullptr);
    void changeGeometry();
    virtual void updatePrice(double);
    virtual void updateLastPos(QPointF);
};

#endif // CUSTOMSTUDIE_H
