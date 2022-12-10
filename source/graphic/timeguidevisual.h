#ifndef TIMEGUIDEVISUAL_H
#define TIMEGUIDEVISUAL_H

#include <QGraphicsItem>

class TimeGuideVisual : public QGraphicsItem
{
private:
    qreal m_rGuideHeight;
    qreal m_rX;
public:
    TimeGuideVisual(QGraphicsItem* parent = nullptr);
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void geometryChanged();
    void setRX(qreal newRY);

};
#endif // TIMEGUIDEVISUAL_H