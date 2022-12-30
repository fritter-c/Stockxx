#include "customstudie.h"

CustomStudie::CustomStudie(QObject* manager, TimeScaleVisual *ts_Visual, PriceScaleVisual *ps_Visual, QGraphicsItem *parent)
    : QGraphicsItem{parent}
{
    m_tsVisual = ts_Visual;
    m_psVisual = ps_Visual;
    setParentItem(parent);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    m_manager = manager;
}

void CustomStudie::changeGeometry()
{
    prepareGeometryChange();
}

void CustomStudie::colorChanged() 
{
    
}

void CustomStudie::select()
{
    m_bSelected = true;

    start();
    update();
}

void CustomStudie::deselect()
{
    m_bSelected = false;
    m_nPenWidth = m_nBasePenWidth;

    stop();
    update();
}

bool CustomStudie::isOverMouse()
{
    return isUnderMouse();
}

void CustomStudie::onGlow(int intensity)
{
    prepareGeometryChange();
    m_nPenWidth = m_nBasePenWidth + (double)intensity/50;
    update();
}

void CustomStudie::setStyle(BasicStudieStyle style)
{
    m_nBasePenWidth = style.width;
    m_penStyle = style.penStyle;
    m_mainColor = style.color;
    m_nPenWidth = m_nBasePenWidth;
    colorChanged();
    update();
}

BasicStudieStyle CustomStudie::getStyle() const
{
    BasicStudieStyle style;
    style.width = m_nBasePenWidth;
    style.penStyle = m_penStyle;
    style.color = m_mainColor;
    return style;
}

void CustomStudie::setThirdPrice(QPointF)
{

}

void CustomStudie::addPoint(QPointF)
{

}

void CustomStudie::setSecondPrice(QPointF)
{

}

QRectF CustomStudie::boundingRect() const
{
    return QRectF(0,0,0,0);
}

void CustomStudie::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setClipRect(parentItem()->boundingRect());
}

QPainterPath CustomStudie::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void CustomStudie::setMainColor(const QColor &newMainColor)
{
    if (newMainColor != m_mainColor) {
        m_mainColor = newMainColor;
        colorChanged();
    }
}

void CustomStudie::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    prepareGeometryChange();
    if(m_bSelected)
        stop();
    m_nPenWidth = fmin(m_nBasePenWidth + 3, 6);
}

void CustomStudie::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    prepareGeometryChange();  
    if(m_bSelected)
        start();
    m_nPenWidth = m_nBasePenWidth;
}
