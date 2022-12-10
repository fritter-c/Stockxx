#ifndef PRICEGUIDE_H
#define PRICEGUIDE_H

#include <QGraphicsItem>

class PriceGuide : public QGraphicsItem
{
private:
    qreal m_rGuideLenght;
    qreal m_rY;
    QGraphicsItem* m_parent;
public:
    PriceGuide(QGraphicsItem* parent = nullptr);
    ~PriceGuide();

    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void geometryChanged();
    void setRY(qreal newRY);
};
#endif // PRICEGUIDE_H