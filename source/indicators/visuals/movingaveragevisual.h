#ifndef MOVINGAVERAGEVISUAL_H
#define MOVINGAVERAGEVISUAL_H

#include "customvisualindicator.h"
#include "indicators/movingaverage.h"

class MovingAverageVisual : public CustomVisualIndicator
{
protected:
    void loadParams(IndicatorVisualParams) override;
    MovingAverage* m_data;
public:
    MovingAverageVisual(IndicatorVisualParams, TimeScaleVisual* timescale, PriceScaleVisual* pricescale,
                        MovingAverage* data,QGraphicsView *view, QObject* manager, QGraphicsItem *parent = nullptr);
    ~MovingAverageVisual();
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void changeGeometry() override;
    virtual bool contains(const QPointF& point) const override;
};

#endif // MOVINGAVERAGEVISUAL_H
