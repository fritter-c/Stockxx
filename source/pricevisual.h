#ifndef PRICEVISUAL_H
#define PRICEVISUAL_H

#include "indicatorvisual.h"
#include "pricecalc.h"
#include "pricescalevisual.h"
#include "timescalevisual.h"

class PriceVisual : public IndicatorVisual
{

private:
    PriceCalc* m_priceCalc;
    Candle* hoveredCandle{nullptr};
    QObject* m_parent;
    SerieInterval m_interval;

public:
    PriceVisual(CustomPrice* customPrice, QObject* parent = nullptr, QGraphicsView* view = nullptr);
    ~PriceVisual();
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    PriceScaleVisual* GetPriceScale();
    TimeScaleVisual* GetTimeScale();
    PriceCalc* GetPrice();
    double Max();
    double Min();
    QList<Candle*> getCandles();
    Candle* getHoveredCandle();
    virtual void changeGeometry() override;
    void toggleCross();
    SerieInterval interval() const;
    void toggleRandomClose(bool);

protected:
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // PRICEVISUAL_H
