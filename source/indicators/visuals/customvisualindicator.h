#ifndef CUSTOMVISUALINDICATOR_H
#define CUSTOMVISUALINDICATOR_H
#include <QGraphicsItem>
#include "priceguide.h"
#include "source/indicators/customindicator.h"
#include "source/graphic/timescalevisual.h"
#include "source/graphic/pricescalevisual.h"
#include "timeguidevisual.h"

class CustomVisualIndicator : public QGraphicsItem
{
protected:
	CustomIndicator* m_data;
	TimeScaleVisual* m_tsVisual;
	PriceScaleVisual* m_psVisual;
    PriceGuide* m_pgVisual;
    TimeGuideVisual* m_tgVisual;
    QGraphicsView* m_view;
	QObject* m_manager;
    bool m_bHighlight{false};
    double m_dPenWidth{1};
    virtual void loadParams(IndicatorVisualParams) = 0;
    BasicIndicatorStyle m_style;
public:
    CustomVisualIndicator(TimeScaleVisual* timescale, PriceScaleVisual* pricescale,
                          CustomIndicator* data,QGraphicsView *view, QObject* manager, QGraphicsItem *parent = nullptr);
	~CustomVisualIndicator();
    void setBHighlight(bool newBHighlight);
    virtual void changeGeometry() = 0;
};
#endif
