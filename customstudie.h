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
    double m_nPenWidth{1};
public:
    CustomStudie(TimeScaleVisual* ts_Visual, PriceScaleVisual* ps_Visual, QGraphicsItem* parent);
    void changeGeometry();
    virtual void updatePrice(double);
    virtual void updateLastPos(QPointF);
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    virtual QPainterPath shape() const override;

    // QGraphicsItem interface
protected:
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
};

#endif // CUSTOMSTUDIE_H
