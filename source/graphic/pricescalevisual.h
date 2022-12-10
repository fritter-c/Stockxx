#ifndef PRICESCALEVISUAL_H
#define PRICESCALEVISUAL_H

#include "qpainter.h"
#include <QGraphicsItem>
#include <QGraphicsView>

class PriceVisual;

struct PriceTag{
public:
    double price;
    QColor color;
};

class PriceScaleVisual : public QGraphicsItem
{
private:
    QObject* m_parent;
    QGraphicsView* m_view;
    PriceVisual* m_price;
    double m_dTopPrice;
    double m_dBottomPrice;
    double m_dSpan;
    int m_nTags{ 15 };
    int m_nSpacing{ 24 };
    bool m_bHighLight{ false };
    void zoom(int);
    QHash<QGraphicsItem*, PriceTag> m_priceTags;
    void paintPriceTags(QPainter* painter, PriceTag);

    // QGraphicsItem interface
protected:
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
    virtual void wheelEvent(QGraphicsSceneWheelEvent* event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
public:
    PriceScaleVisual(PriceVisual* price, QObject* parent = nullptr, QGraphicsView* view = nullptr);
    ~PriceScaleVisual();
    const qreal c_PriceScaleFWidth = 70;
    const qreal c_dTimeScaleHeight = 30;
    const qreal c_rPriceScaleTagOffset = 5;
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    void UpdateExtremePrices();
    void UpdateSpan();
    void UpdateSpacing();
    qreal PriceAtY(qreal y);
    qreal YAtPrice(double price);
    QVector<qreal> priceTagPositions;
    void changeGeometry();
    void addPriceTag(double price, QColor color, QGraphicsItem* sender);
    void removePriceTag(QGraphicsItem* sender);
    void updatePriceTag(QGraphicsItem* sender, double price, QColor color = QColor());
    void movePrice(qreal y);
};
#endif // PRICESCALEVISUAL_H