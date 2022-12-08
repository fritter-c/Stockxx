#ifndef INDICATORVISUAL_H
#define INDICATORVISUAL_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsView>
#include "customprice.h"
#include "indicatorcalc.h"
#include "pricescalevisual.h"
#include "timescalevisual.h"
#include "priceguide.h"
#include "timeguidevisual.h"

class IndicatorVisual : public QGraphicsItem
{
protected:
    CustomPrice* m_customPrice;
    IndicatorCalc* m_data;
    QObject* m_parent;
    QGraphicsView* m_view;
    TimeScaleVisual* m_tsVisual;
    PriceScaleVisual* m_psVisual;
    PriceGuide* m_pgVisual{nullptr};
    TimeGuideVisual* m_tgVisual{nullptr};

public:
    IndicatorVisual(CustomPrice* customPrice, QObject* parent = nullptr, QGraphicsView* view = nullptr);
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    virtual void changeGeometry();
};
#endif // INDICATORVISUAL_H