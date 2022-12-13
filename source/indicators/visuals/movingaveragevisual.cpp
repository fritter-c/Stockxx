#include "movingaveragevisual.h"
#include "indicatormanager.h"

MovingAverageVisual::MovingAverageVisual(IndicatorVisualParams params, TimeScaleVisual* timescale, PriceScaleVisual* pricescale,
	MovingAverage* data, QGraphicsView* view, QObject* manager, QGraphicsItem* parent) :
	CustomVisualIndicator{ timescale, pricescale, data, view, manager, parent }
{
	MovingAverageVisual::loadParams(params);
    m_data = data;
}

MovingAverageVisual::~MovingAverageVisual()
{
    IndicatorManager::Instance().scheduleDeletion(m_data->ID());
}

QRectF MovingAverageVisual::boundingRect() const
{
	return QRectF(0, 0,
		m_view->width() - m_psVisual->c_PriceScaleFWidth,
		m_view->height() - m_tsVisual->c_rTimeScaleHeight);
}

void MovingAverageVisual::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{

	QPen pen;
	pen.setStyle(m_style.penStyle);
	pen.setColor(m_style.color);
    pen.setWidth(m_style.width);
	painter->setPen(pen);
	painter->setClipRect(boundingRect());

	int nEntrys{ m_tsVisual->getEntrys() };
    if (!(nEntrys and m_data->Size())) return;

	m_data->PriorAll();
	bool bNext{ true };

	qreal rFirstPos{ m_tsVisual->getFirstPos() };
	QuoteIdentifier qiFirstQuote{ m_tsVisual->getFirstQuote() };
	qreal rSpacing{ m_tsVisual->getSpacing() };
	int nCandlesPainted{ 0 };
	if (m_bHighlight)
		painter->setOpacity(0.5);
	m_data->GoToQuote(qiFirstQuote);
	do {
		QPointF start;
		QPointF end;

		start.ry() = m_psVisual->YAtPrice(m_data->Value());
		start.rx() = rFirstPos;

		bNext = m_data->Next();

		end.ry() = m_psVisual->YAtPrice(m_data->Value());
		end.rx() = rFirstPos + rSpacing;

		painter->drawLine(start, end);

		rFirstPos += rSpacing;
		nCandlesPainted++;

	} while (bNext and (nCandlesPainted < nEntrys));
}

void MovingAverageVisual::changeGeometry()
{
	prepareGeometryChange();
}

bool MovingAverageVisual::contains(const QPointF& point) const
{
	qreal pos;
	QPointF localpoint{ point };
	QuoteIdentifier qi = m_tsVisual->findNearestDate(localpoint.x(), &pos);
	m_data->GoToQuote(qi);
	QPointF start;
	QPointF end;
	qreal rFirstPos{ m_tsVisual->XAtQuote(m_data->Quote()) };
	qreal rSpacing{ m_tsVisual->getSpacing() };
	QPainterPath path;
	int nIndex{ 0 };

    // desenha dois segmentos
	while (nIndex < 2) {
		start.ry() = m_psVisual->YAtPrice(m_data->Value());
		start.rx() = rFirstPos;

        m_data->Next();

		end.ry() = m_psVisual->YAtPrice(m_data->Value());
		end.rx() = rFirstPos + rSpacing;
		path.moveTo(start);
		path.lineTo(end);
		nIndex++;
		rFirstPos += rSpacing;
	}
	QPen pen;
    pen.setWidth(m_style.width);
	QPainterPathStroker stroker{ pen };
	return stroker.createStroke(path).contains(point);
}

void MovingAverageVisual::loadParams(IndicatorVisualParams params)
{
	m_style = *static_cast<BasicIndicatorStyle*>(params[0]);
	delete params[0];
}
