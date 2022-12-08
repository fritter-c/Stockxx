#include "customstudie.h"
#include "qevent.h"
#include "graphicmanager.h"

CustomStudie::CustomStudie(QObject* manager, TimeScaleVisual *ts_Visual, PriceScaleVisual *ps_Visual, QGraphicsItem *parent)
    : QGraphicsItem{parent}
{
    m_tsVisual = ts_Visual;
    m_psVisual = ps_Visual;
    setParentItem(parent);
    setFlag(QGraphicsItem::ItemIsFocusable);
    m_manager = manager;

}

void CustomStudie::changeGeometry()
{
    prepareGeometryChange();
}

void CustomStudie::colorChanged() 
{

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
    m_nPenWidth = 3;
}

void CustomStudie::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    prepareGeometryChange();
    m_nPenWidth = 1;
}

void CustomStudie::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{

}

void CustomStudie::keyPressEvent(QKeyEvent *event)
{
   if (event->key() == Qt::Key_Delete) dynamic_cast<GraphicManager*>(m_manager)->deleteStudie(this);
}
