#ifndef BOLLINGERBANDSVISUAL_H
#define BOLLINGERBANDSVISUAL_H

#include "customvisualindicator.h"
#include "indicators/bollingerbands.h"

class BollingerBandsVisual : public CustomVisualIndicator
{
protected:
    void loadParams(IndicatorVisualParams) override;
    BollingerBands* m_data;
public:
    BollingerBandsVisual(IndicatorVisualParams, TimeScaleVisual* timescale, PriceScaleVisual* pricescale,
                         BollingerBands* data,QGraphicsView *view, QObject* manager, QGraphicsItem *parent = nullptr);
    ~BollingerBandsVisual();
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void changeGeometry() override;
    virtual bool contains(const QPointF& point) const override;
};

#endif // BOLLINGERBANDSVISUAL_H
