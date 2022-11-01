#include "customstudie.h"

CustomStudie::CustomStudie(TimeScaleVisual *ts_Visual, PriceScaleVisual *ps_Visual, QGraphicsItem *parent)
    : QGraphicsItem{parent}
{
    m_tsVisual = ts_Visual;
    m_psVisual = ps_Visual;
    setParentItem(parent);

}

void CustomStudie::changeGeometry()
{
    prepareGeometryChange();
}

void CustomStudie::updatePrice(double)
{

}

void CustomStudie::updateLastPos(QPointF)
{

}
