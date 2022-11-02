#include "fibonaccistudie.h"

FibonacciStudie::FibonacciStudie(qreal x, double price, TimeScaleVisual *ts_Visual, PriceScaleVisual *ps_Visual, QGraphicsItem *parent) : CustomStudie{ts_Visual, ps_Visual, parent}
{
    qreal rX;
    m_dStartPrice = price;
    m_dEndPrice = price;
    m_qiStartQuote = m_tsVisual->findNearestDate(x, &rX);
    m_qiEndQuote = m_qiStartQuote;
    setAcceptHoverEvents(true);
}

QRectF FibonacciStudie::boundingRect() const
{
    QPointF point1{m_tsVisual->XAtQuote(m_qiStartQuote), m_psVisual->YAtPrice(m_dStartPrice)};
    QPointF point2{m_tsVisual->XAtQuote(m_qiEndQuote), m_psVisual->YAtPrice(m_dEndPrice)};
    return QRectF(point1, point2).normalized();
}

void FibonacciStudie::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    const qreal c_rMargin{5};
    if ((m_dStartPrice != m_dEndPrice) or (m_qiStartQuote != m_qiEndQuote)){
        CustomStudie::paint(painter, option, widget); // clips
        bool bLeftAlign{((m_qiEndQuote > m_qiStartQuote) and (m_dEndPrice > m_dStartPrice))};
        double dSpread{abs(m_dEndPrice - m_dStartPrice)};
        // main line
        QPointF point1{m_tsVisual->XAtQuote(m_qiStartQuote), m_psVisual->YAtPrice(m_dStartPrice)};
        QPointF point2{m_tsVisual->XAtQuote(m_qiEndQuote), m_psVisual->YAtPrice(m_dEndPrice)};
        QPen blackPen{Qt::black, m_nPenWidth};
        blackPen.setStyle(Qt::DashLine);
        painter->setPen(blackPen);
        painter->drawLine(point1, point2);

        blackPen.setStyle(Qt::SolidLine);
        painter->setPen(blackPen);

        QFont font{painter->font()};
        QFontMetricsF fm{font};
        qreal rAdvance{fm.horizontalAdvance("100% " +QString::number(std::max(m_dStartPrice,m_dStartPrice), 'f', 2)) + 20};
        bool bCanFit {(abs(m_tsVisual->XAtQuote(m_qiStartQuote) - m_tsVisual->XAtQuote(m_qiEndQuote)) > rAdvance) and
                    ((5 * fm.height()) < abs(m_psVisual->YAtPrice(m_dStartPrice) - m_psVisual->YAtPrice(m_dEndPrice)))};
        // 0% line
        QPointF point3{m_tsVisual->XAtQuote(m_qiStartQuote), m_psVisual->YAtPrice(m_dStartPrice)};
        QPointF point4{m_tsVisual->XAtQuote(m_qiEndQuote), m_psVisual->YAtPrice(m_dStartPrice)};
        painter->drawLine(point3, point4);
        if ((bLeftAlign) and (bCanFit)){
            point4.rx() = point4.rx() - fm.horizontalAdvance("0% " + QString::number(m_dStartPrice, 'f', 2));
            point4.ry() = point4.ry() - c_rMargin;
            painter->drawText(point4, "0% " + QString::number(m_dStartPrice, 'f', 2));
        }

        // 100% line
        QPointF point5{m_tsVisual->XAtQuote(m_qiStartQuote), m_psVisual->YAtPrice(m_dEndPrice)};
        QPointF point6{m_tsVisual->XAtQuote(m_qiEndQuote), m_psVisual->YAtPrice(m_dEndPrice)};
        painter->drawLine(point5, point6);
        if ((bLeftAlign) and (bCanFit)){
            point6.rx() = point6.rx() - fm.horizontalAdvance("100% " + QString::number(m_dEndPrice, 'f', 2));
            point6.ry() = point6.ry() + fm.height();
            painter->drawText(point6, "100% " + QString::number(m_dEndPrice, 'f', 2));
        }

        // Other lines
        if (m_dStartPrice < m_dEndPrice){
            QPointF point7{m_tsVisual->XAtQuote(m_qiStartQuote), m_psVisual->YAtPrice(m_dStartPrice + dSpread / 2)};
            QPointF point8{m_tsVisual->XAtQuote(m_qiEndQuote), m_psVisual->YAtPrice(m_dStartPrice + dSpread / 2)};
            painter->drawLine(point7, point8);
            if ((bLeftAlign) and (bCanFit)){
                point8.rx() = point8.rx() - fm.horizontalAdvance("50% " + QString::number(m_dStartPrice + dSpread / 2, 'f', 2));
                point8.ry() = point8.ry() - c_rMargin;
                painter->drawText(point8, "50% " + QString::number(m_dStartPrice + dSpread / 2, 'f', 2));
            }
            QPointF point9{m_tsVisual->XAtQuote(m_qiStartQuote), m_psVisual->YAtPrice(m_dStartPrice + dSpread * 0.382)};
            QPointF point10{m_tsVisual->XAtQuote(m_qiEndQuote), m_psVisual->YAtPrice(m_dStartPrice + dSpread * 0.382)};
            painter->drawLine(point9, point10);
            if ((bLeftAlign) and (bCanFit)){
                point10.rx() = point10.rx() - fm.horizontalAdvance("38.2% " + QString::number(m_dStartPrice + dSpread * 0.382, 'f', 2));
                point10.ry() = point10.ry() - c_rMargin;
                painter->drawText(point10, "38.2% " + QString::number(m_dStartPrice + dSpread * 0.382, 'f', 2));
            }
            QPointF point11{m_tsVisual->XAtQuote(m_qiStartQuote), m_psVisual->YAtPrice(m_dStartPrice + dSpread * 0.618)};
            QPointF point12{m_tsVisual->XAtQuote(m_qiEndQuote), m_psVisual->YAtPrice(m_dStartPrice + dSpread * 0.618)};
            painter->drawLine(point11, point12);
            if ((bLeftAlign) and (bCanFit)){
                point12.rx() = point12.rx() - fm.horizontalAdvance("61.8% " + QString::number(m_dStartPrice + dSpread * 0.618, 'f', 2));
                point12.ry() = point12.ry() - c_rMargin;
                painter->drawText(point12, "61.8% " + QString::number(m_dStartPrice + dSpread * 0.618, 'f', 2));
            }
        }
        else{
            QPointF point7{m_tsVisual->XAtQuote(m_qiStartQuote), m_psVisual->YAtPrice(m_dStartPrice - dSpread / 2)};
            QPointF point8{m_tsVisual->XAtQuote(m_qiEndQuote), m_psVisual->YAtPrice(m_dStartPrice - dSpread / 2)};
            painter->drawLine(point7, point8);
            if ((bLeftAlign) and (bCanFit)){
                point8.rx() = point8.rx() - fm.horizontalAdvance("50% " + QString::number(m_dStartPrice - dSpread / 2, 'f', 2));
                point8.ry() = point8.ry() - c_rMargin;
                painter->drawText(point8, "50% " + QString::number(m_dStartPrice - dSpread / 2, 'f', 2));
            }
            QPointF point9{m_tsVisual->XAtQuote(m_qiStartQuote), m_psVisual->YAtPrice(m_dStartPrice - dSpread * 0.382)};
            QPointF point10{m_tsVisual->XAtQuote(m_qiEndQuote), m_psVisual->YAtPrice(m_dStartPrice - dSpread * 0.382)};
            painter->drawLine(point9, point10);
            if ((bLeftAlign) and (bCanFit)){
                point10.rx() = point10.rx() - fm.horizontalAdvance("38.2% " + QString::number(m_dStartPrice + dSpread - 0.382, 'f', 2));
                point10.ry() = point10.ry() - c_rMargin;
                painter->drawText(point10, "38.2% " + QString::number(m_dStartPrice + dSpread - 0.382, 'f', 2));
            }
            QPointF point11{m_tsVisual->XAtQuote(m_qiStartQuote), m_psVisual->YAtPrice(m_dStartPrice - dSpread * 0.618)};
            QPointF point12{m_tsVisual->XAtQuote(m_qiEndQuote), m_psVisual->YAtPrice(m_dStartPrice - dSpread * 0.618)};
            painter->drawLine(point11, point12);
            if ((bLeftAlign) and (bCanFit)){
                point12.rx() = point12.rx() - fm.horizontalAdvance("61.8% " + QString::number(m_dStartPrice - dSpread * 0.618, 'f', 2));
                point12.ry() = point12.ry() - c_rMargin;
                painter->drawText(point12, "61.8% " + QString::number(m_dStartPrice - dSpread * 0.618, 'f', 2));
            }
        }
    }
}

void FibonacciStudie::updateLastPos(QPointF pf)
{
    prepareGeometryChange();
    qreal rX;
    m_qiEndQuote = m_tsVisual->findNearestDate(pf.x(), &rX);
    m_dEndPrice  = m_psVisual->PriceAtY(pf.y());
    update();
}

QPainterPath FibonacciStudie::shape() const
{
    QPainterPath path;
    QPointF point1{m_tsVisual->XAtQuote(m_qiStartQuote), m_psVisual->YAtPrice(m_dStartPrice)};
    QPointF point2{m_tsVisual->XAtQuote(m_qiEndQuote), m_psVisual->YAtPrice(m_dEndPrice)};

    path.addRect(QRectF(point1, point2).normalized());
    return path;
}
