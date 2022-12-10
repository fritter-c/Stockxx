#ifndef CUSTOMSTUDIE_H
#define CUSTOMSTUDIE_H

#include <QGraphicsItem>
#include "pricescalevisual.h"
#include "timescalevisual.h"
#include "ivisualitem.h"
#include "iglower.h"

class CustomStudie : public QGraphicsItem, public IVisualItem, public IGlower
{
protected:
    PriceScaleVisual* m_psVisual;
    TimeScaleVisual* m_tsVisual;
    const qreal m_cPriceScaleMargin = 2;
    QuoteIdentifier m_qiStartQuote{INVALID_QUOTE};
    QuoteIdentifier m_qiEndQuote{INVALID_QUOTE};
    double m_dStartPrice{0};
    double m_dEndPrice{0};
    double m_nPenWidth{1};
    double m_nBasePenWidth{1};
    Qt::PenStyle m_penStyle{Qt::SolidLine};
    QColor m_mainColor{Qt::yellow};
    QObject* m_manager;
    bool m_bSelected{false};

    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
public:
    CustomStudie(QObject* manager, TimeScaleVisual* ts_Visual, PriceScaleVisual* ps_Visual, QGraphicsItem* parent);
    void setMainColor(const QColor &newMainColor);
    virtual void changeGeometry() override;
    virtual void setSecondPrice(QPointF);
    virtual void setThirdPrice(QPointF);
    virtual void addPoint(QPointF);
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    virtual QPainterPath shape() const override;
    virtual void colorChanged() override;
    virtual void select() override;
    virtual void deselect() override;
    virtual bool isOverMouse() override;
    virtual void onGlow(int intensity) override;
    void setStyle(BasicStudieStyle style);
    BasicStudieStyle getStyle() const;
};

#endif // CUSTOMSTUDIE_H
