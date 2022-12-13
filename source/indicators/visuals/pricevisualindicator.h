#ifndef PRICEVISUALINDICATOR_H
#define PRICEVISUALINDICATOR_H

#include "customvisualindicator.h"
#include "indicators/priceindicator.h"
#include <QGraphicsSceneHoverEvent>

class PriceVisualIndicator : public CustomVisualIndicator
{
private:
    PriceIndicator* m_data;
    Candle m_hoveredCandle;
    qreal m_dCandleSize{0};
protected:
    virtual void loadParams(IndicatorVisualParams) override;
public:
    PriceVisualIndicator(TimeScaleVisual* timescale, PriceScaleVisual* pricescale,
        PriceIndicator* data,QGraphicsView *view, QObject* manager, QGraphicsItem* parent = nullptr);
	~PriceVisualIndicator();

    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    PriceScaleVisual* GetPriceScale();
    TimeScaleVisual* GetTimeScale();
    PriceIndicator* GetPrice();
    double Max();
    double Min();
    CandleArray getCandles();
    Candle getHoveredCandle();
    virtual void changeGeometry() override;
    void toggleCross();
    SerieInterval interval() const;
    void toggleRandomClose(bool);
    virtual bool contains(const QPointF &point) const override;
};



#endif
