#ifndef GRAPHICTITLEBAR_H
#define GRAPHICTITLEBAR_H

#include "StockxxDataTypes.h"
#include "candle.h"
#include <QGraphicsItem>



class GraphicTitlebar : public QGraphicsItem
{
private:
    const int c_nTitlebarHeight = 20;
    QGraphicsItem* m_parent;
    QString m_mainTitle{};
    QString m_mainTimeframe{};
    bool m_bHighlight{false};
    Candle m_candle;

protected:
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;


public:
    GraphicTitlebar(QGraphicsItem* parent);
    void setTitle(const QString&);
    void setTimeframe(SerieInterval);
    void setCandle(const Candle&);
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;


};




#endif // GRAPHICTITLEBAR_H
