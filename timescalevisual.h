#ifndef TIMESCALEVISUAL_H
#define TIMESCALEVISUAL_H

#include "candle.h"
#include <QGraphicsItem>
#include <QGraphicsView>
#include "StockxxDataTypes.h"

class PriceVisual;
class TimeScaleVisual : public QGraphicsItem
{
private:
    QObject* m_parent;
    QGraphicsView* m_view;
    PriceVisual* m_price;
    int m_nFirstIndex;
    int m_nLastIndex;
    int m_nMouseX;
    int m_nFirstVisible;
    QHash<QuoteIdentifier, qreal> m_datePositions;
    QMap<QString, int> m_hashDates;
    QVector<int> m_drawnPositions;
    QVector<QuoteIdentifier> m_dtDateTimes;
    QHash<QuoteIdentifier, Candle*> m_mapCandles;
    void popuplateDateTimes();
    bool m_bHighLight{false};
    void zoom(int);

public:
    TimeScaleVisual(PriceVisual* price, QObject* parent = nullptr, QGraphicsView* view = nullptr);
    const qreal c_rTimeScaleHeight = 30;
    const qreal c_rPriceScaleWidth = 70;
    const qreal c_rTimeScaleBottomMargin = 10;
    const qreal c_rTimeScaleBoldMargin = 5;
    const qreal c_rTimeScaleTagMargin = 10;
    int getEntrys();
    int nZoom{0};
    int nOffset{0};
    void changeGeometry();

    // QGraphicsItem interface
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    qreal XAtQuote(QuoteIdentifier);
    void recalculatePositions();
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void wheelEvent(QGraphicsSceneWheelEvent *event) override;
};

#endif // TIMESCALEVISUAL_H
