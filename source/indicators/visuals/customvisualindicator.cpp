#include "customvisualindicator.h"


CustomVisualIndicator::CustomVisualIndicator(TimeScaleVisual* timescale, PriceScaleVisual* pricescale,
    CustomIndicator* data, QGraphicsView *view, QObject* manager, QGraphicsItem* parent) : QGraphicsItem(parent)
{	
	m_data = data;
	m_data->setVisualParent(this);
	m_tsVisual = timescale;
	m_psVisual = pricescale;
    m_view = view;
	m_manager = manager;
}

CustomVisualIndicator::~CustomVisualIndicator()
{

}

void CustomVisualIndicator::setBHighlight(bool newBHighlight)
{
    if (m_bHighlight != newBHighlight){
        m_bHighlight = newBHighlight;
        update();
    }
}

void CustomVisualIndicator::OnNewData(size_t start)
{
    update();
}
