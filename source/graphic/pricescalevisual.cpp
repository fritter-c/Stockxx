#include "pricescalevisual.h"
#include "colorutils.h"
#include "qgraphicsscene.h"
#include "qgraphicssceneevent.h"
#include "qgraphicsview.h"
#include <QPainter>
#include "pricescalevisual.h"

void PriceScaleVisual::zoom(int delta)
{
    double dTop{m_dTopPrice + delta *(0.01 * m_dTopPrice) / 100}, dBottom {m_dBottomPrice + (-delta) *(0.01 * m_dTopPrice) / 100};
    if (dTop > dBottom)
    {
        m_dTopPrice = dTop;
        m_dBottomPrice = dBottom;
        UpdateSpan();
    }
}

void PriceScaleVisual::paintPriceTags(QPainter *painter, PriceTag tag)
{
    QBrush brush{tag.color};
    painter->setBrush(brush);
    QPointF pointVertice1{boundingRect().left(), YAtPrice(tag.price)};
    QPointF pointAboveVertice1 {pointVertice1.x() + 10, pointVertice1.y() + 10};
    QPointF pointEnd1 {boundingRect().right(), pointVertice1.y() + 10};
    QPointF pointEnd2 {boundingRect().right(), pointVertice1.y() - 10};
    QPointF pointAboveVertice2 {pointVertice1.x() + 10, pointVertice1.y() - 10};
    QPointF pointVertice2{boundingRect().left(), YAtPrice(tag.price)};
    QPointF pointText(pointVertice1.x() + 10, pointVertice1.y() + 5);

    QList points{pointVertice1, pointAboveVertice1, pointEnd1, pointEnd2, pointAboveVertice2, pointVertice2};
    QPolygonF polygon{points};
    if (isDarkColor(tag.color)){
        QPen penText{Qt::white};
        painter->setPen(penText);
    }
    else{
        QPen penText{Qt::black};
        painter->setPen(penText);
    }
    painter->drawPolygon(polygon);
    painter->drawText(pointText,QString::number(PriceAtY(pointVertice1.y()), 'f', 2));
}

PriceScaleVisual::PriceScaleVisual(CustomIndicator *price, QObject* parent, QGraphicsView* view)
{
    m_price = price;
    m_parent = parent;
    m_view = view;
    setAcceptHoverEvents(true);
    m_price->addSubscriber(this);
    UpdateExtremePrices();

}

PriceScaleVisual::~PriceScaleVisual()
{
    m_priceTags.clear();
    priceTagPositions.clear();
    m_price->removeSubscriber(this);
}

QRectF PriceScaleVisual::boundingRect() const
{
    return QRectF(m_view->width() - c_PriceScaleFWidth, 0 ,c_PriceScaleFWidth, m_view->height()- c_dTimeScaleHeight);
}

void PriceScaleVisual::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen penBorder{Qt::black, 2};
    painter->setPen(penBorder);
    painter->drawLine(m_view->width() - c_PriceScaleFWidth,0,m_view->width() - c_PriceScaleFWidth, m_view->height() - c_dTimeScaleHeight);

    QFont font{painter->font()};
    font.setPixelSize(12);
    QPointF point {boundingRect().left() + c_rPriceScaleTagOffset,c_dTimeScaleHeight + font.pixelSize() / 2};
    QPointF drawPoint {boundingRect().left() + c_rPriceScaleTagOffset, c_dTimeScaleHeight + font.pixelSize() / 2};

    QPen penTags {Qt::black};

    if (m_bHighLight)
        font.setBold(true);

    painter->setFont(font);
    priceTagPositions.clear();
    painter->setPen(penTags);
    for (int i{0}; i < m_nTags; ++i)
    {
      drawPoint.ry() = point.y() + font.pixelSize() / 2;
      priceTagPositions.push_back(point.y());
      painter->drawText(drawPoint,QString::number(PriceAtY(point.y()), 'f', 2));
      point.ry() += 2 * m_nSpacing;
      if ((point.ry() + font.pixelSize() / 2) > boundingRect().bottom()) break;

    }
   QHashIterator<QGraphicsItem*, PriceTag> i(m_priceTags);
   while(i.hasNext()){
       i.next();
       if (i.key()->isVisible())
           paintPriceTags(painter, i.value());
   }
}

void PriceScaleVisual::UpdateExtremePrices()
{
    m_dTopPrice = m_price->Max();
    m_dBottomPrice = m_price->Min();
    UpdateSpan();
}

void PriceScaleVisual::UpdateSpan()
{
    m_dSpan = m_dTopPrice - m_dBottomPrice;
    if (m_price->visualParent())
        m_price->visualParent()->update();
    update();
}

void PriceScaleVisual::UpdateSpacing()
{
    int nTotalSpace {static_cast<int>(boundingRect().height() - 2 * c_dTimeScaleHeight)};
    int nSpaceNeeded {m_nTags * m_nSpacing + (m_nTags + 1) * m_nSpacing};
    int nSpaceLeft {nTotalSpace - nSpaceNeeded};

    if (nSpaceLeft > 0)
     {
         while (nSpaceLeft >= 0)
         {
             m_nTags++;
             nSpaceNeeded = m_nTags * m_nSpacing + (m_nTags - 1) * m_nSpacing;
             nSpaceLeft = nTotalSpace - nSpaceNeeded;
         }
     }
     else
     {
         while ((nSpaceLeft < 0) && (m_nTags > 1))
         {
             m_nTags--;
             nSpaceNeeded = m_nTags * m_nSpacing + (m_nTags - 1) * m_nSpacing;
             nSpaceLeft = nTotalSpace - nSpaceNeeded;
         }
    }
}

qreal PriceScaleVisual::PriceAtY(qreal y)
{
    return (((boundingRect().height() - y) *m_dSpan)/ boundingRect().height()) + m_dBottomPrice;
}

qreal PriceScaleVisual::YAtPrice(double price)
{
    return -(price - m_dBottomPrice) * boundingRect().height() / m_dSpan + boundingRect().height();
}

void PriceScaleVisual::changeGeometry()
{
    prepareGeometryChange();
}

void PriceScaleVisual::addPriceTag(double price, QColor color, QGraphicsItem* sender)
{
    m_priceTags.insert(sender, {price, color});
    update();
}

void PriceScaleVisual::removePriceTag(QGraphicsItem *sender)
{
    if (m_priceTags.contains(sender)){
        m_priceTags.remove(sender);
        update();
    }
}

void PriceScaleVisual::updatePriceTag(QGraphicsItem *sender, double price, QColor color)
{
    if(m_priceTags.contains(sender)){
        m_priceTags[sender].price = price;
        if (color != QColor()){
            m_priceTags[sender].color = color;

        }
        update();
    }

}

void PriceScaleVisual::movePrice(qreal y)
{
    double aux{m_dTopPrice};
    m_dTopPrice += y * 0.1 * aux;
    m_dBottomPrice += y * 0.1 * aux;
    UpdateSpan();
}

void PriceScaleVisual::OnNewData(size_t start)
{
    if (start == 0)
        UpdateExtremePrices();
}

void PriceScaleVisual::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    m_bHighLight = true;
    update();
    event->accept();
}

void PriceScaleVisual::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{

}

void PriceScaleVisual::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    m_bHighLight = false;
    update();
    event->accept();
}

void PriceScaleVisual::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    zoom(event->delta());
    update();
    event->accept();

}

void PriceScaleVisual::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

}
