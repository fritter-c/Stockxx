#ifndef CANDLEMAGNIFIER_H
#define CANDLEMAGNIFIER_H

#include <QGraphicsItem>
#include "candle.h"

class CandleMagnifier : public QGraphicsItem
{
private:
    qreal m_zValue{1};
    qreal m_rHeight{200};
    qreal m_rWidth{200};
    Candle* m_selectedCandle{nullptr};
    inline qreal YAtPrice(double,double,double,double);
public:
    CandleMagnifier(QGraphicsItem* parent = nullptr);
    void bringBack();
    void changeSize(QSizeF);
    void setSelectedCandle(Candle*);


    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // CANDLEMAGNIFIER_H
