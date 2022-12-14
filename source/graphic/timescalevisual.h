#ifndef TIMESCALEVISUAL_H
#define TIMESCALEVISUAL_H

#include "candle.h"
#include <QGraphicsItem>
#include <QGraphicsView>
#include "StockxxDataTypes.h"
#include "indicators/customindicator.h"
#include "icustomserienotifiable.h"

class PriceVisual;

struct TimeTag
{
public:
    QuoteIdentifier iq;
    QColor color;
};

enum DragState {sNone, sDragging};
class TimeScaleVisual : public QGraphicsItem, public ICustomSerieNotifiable
{
private:
    QObject* m_parent;
    QGraphicsView* m_view;
    CustomIndicator* m_price;
    int m_nFirstIndex{0};
    int m_nLastIndex;
    int m_nMouseX;
    int m_nFirstVisible;
    QMap<QString, int> m_hashDates;
    QVector<int> m_drawnPositions;
    QVector<QuoteIdentifier> m_dtDateTimes;
    void popuplateDateTimes();
    bool m_bHighLight{false};
    void zoom(int);
    qreal m_rSpacing{0};
    qreal m_rFirst{0};
    qreal m_rLast{0};
    uint64_t m_nFirstID{0};
    uint64_t m_nLastID{0};
    QHash<QGraphicsItem*, TimeTag> m_timeTags;
    DragState m_state{sNone};
    void paintTimeTags(QPainter*, TimeTag);

protected:
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void wheelEvent(QGraphicsSceneWheelEvent *event) override;

public:
    TimeScaleVisual(CustomIndicator* price, QObject* parent = nullptr, QGraphicsView* view = nullptr);
    ~TimeScaleVisual();
    const qreal c_rTimeScaleHeight = 30;
    const qreal c_rPriceScaleWidth = 70;
    const qreal c_rTimeScaleBottomMargin = 10;
    const qreal c_rTimeScaleBoldMargin = 5;
    const qreal c_rTimeScaleTagMargin = 10;
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    qreal getFirstPos();
    qreal getSpacing();
    int getEntrys();
    int nZoom{0};
    int nOffset{0};
    void changeGeometry();
    void moveTime(int);
    QuoteIdentifier findNearestDate(qreal x, qreal *pos);
    QuoteIdentifier findNearestDate(qreal x);
    QuoteIdentifier getFirstQuote();
    void addPriceTag(qreal x, QColor color, QGraphicsItem* sender);
    void removePriceTag(QGraphicsItem* sender);
    void updatePriceTag(QGraphicsItem* sender, qreal x, QColor color = QColor());
    qreal XAtQuote(QuoteIdentifier);
    void recalculatePositions();
    virtual void OnNewData(size_t) override;
};
#endif // TIMESCALEVISUAL_H
