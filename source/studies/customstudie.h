#ifndef CUSTOMSTUDIE_H
#define CUSTOMSTUDIE_H

#include <QGraphicsItem>
#include "pricescalevisual.h"
#include "timescalevisual.h"

class CustomStudie : public QGraphicsItem
{
protected:
    PriceScaleVisual* m_psVisual;
    TimeScaleVisual* m_tsVisual;
    const qreal m_cPriceScaleMargin = 2;
    QuoteIdentifier m_qiStartQuote{INVALID_QUOTE};
    QuoteIdentifier m_qiEndQuote{INVALID_QUOTE};
    double m_dStartPrice{0};
    double m_dEndPrice{0};
    double m_nPenWidth{1};

    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
public:
    CustomStudie(TimeScaleVisual* ts_Visual, PriceScaleVisual* ps_Visual, QGraphicsItem* parent);
    virtual void changeGeometry();
    virtual void setSecondPrice(QPointF);
    virtual void setThirdPrice(QPointF);
    virtual void addPoint(QPointF);
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    virtual QPainterPath shape() const override;
};



#endif // CUSTOMSTUDIE_H