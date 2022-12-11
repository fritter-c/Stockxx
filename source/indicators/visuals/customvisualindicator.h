#ifndef CUSTOMVISUALINDICATOR_H
#define CUSTOMVISUALINDICATOR_H
#include <QGraphicsItem>
#include "source/indicators/customindicator.h"
#include "source/graphic/timescalevisual.h"
#include "source/graphic/pricescalevisual.h"

class CustomVisualIndicator : public QGraphicsItem
{
protected:
	CustomIndicator* m_data;
	TimeScaleVisual* m_tsVisual;
	PriceScaleVisual* m_psVisual;
    QGraphicsView* m_view;
	QObject* m_manager;
	virtual void changeGeometry() = 0;

public:
    CustomVisualIndicator(TimeScaleVisual* timescale, PriceScaleVisual* pricescale,
                          CustomIndicator* data,QGraphicsView *view, QObject* manager, QGraphicsItem *parent = nullptr);
	~CustomVisualIndicator();
};
#endif
