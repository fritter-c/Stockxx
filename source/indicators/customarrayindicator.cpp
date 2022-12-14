#include "customarrayindicator.h"
#include <customprice.h>

CustomArrayIndicator::CustomArrayIndicator(CustomSerie* base) : CustomIndicator{ base }
{
    // para evitar acesso inválido
	m_arData.resize(1);
    m_arData[0].resize(1);
}

void CustomArrayIndicator::setInnerSize(size_t N)
{
	if (N > 0)
		m_arData.resize(N);
}

bool CustomArrayIndicator::Next()
{
	if ((m_nIndex + 1) <= Size() - 1) {
		m_nIndex++;
		return true;
	}
	return false;
}

bool CustomArrayIndicator::Prior()
{
	if ((m_nIndex - 1) >= 0) {
		m_nIndex--;
		return true;
	}
	return false;
}

bool CustomArrayIndicator::PriorAll()
{
	m_nIndex = 0;
	return true;
}

bool CustomArrayIndicator::NextAll()
{
	m_nIndex = Size() - 1;
	return true;
}

bool CustomArrayIndicator::PriorN(size_t N)
{
	if ((m_nIndex - N) >= 0) {
		m_nIndex = m_nIndex - N;
		return true;
	}
	return false;
}

bool CustomArrayIndicator::NextN(size_t N)
{
	if ((m_nIndex + N) <= (Size() - 1)) {
		m_nIndex = m_nIndex + N;
		return true;
	}
	return false;
}

size_t CustomArrayIndicator::Size()
{
	return m_arData[0].size();
}

double CustomArrayIndicator::Open()
{
	return INVALID_DOUBLE;
}

double CustomArrayIndicator::Close()
{
	return INVALID_DOUBLE;
}

QDateTime CustomArrayIndicator::Date()
{
	return ZERO_DATE;
}

double CustomArrayIndicator::High()
{
	return INVALID_DOUBLE;
}

double CustomArrayIndicator::Low()
{
	return INVALID_DOUBLE;
}

double CustomArrayIndicator::Volume()
{
	return INVALID_DOUBLE;
}

bool CustomArrayIndicator::GoToQuote(QuoteIdentifier qi)
{
	if (!qobject_cast<CustomPrice*>(m_baseIndicator)) return false;
	m_baseIndicator->GoToQuote(qi);
	return GoToIndex(m_baseIndicator->ActualIndex());
}

QuoteIdentifier CustomArrayIndicator::Quote()
{
	if (!qobject_cast<CustomPrice*>(m_baseIndicator)) return INVALID_QUOTE;
	m_baseIndicator->GoToQuote(m_nIndex);
	return m_baseIndicator->Quote();
}

void CustomArrayIndicator::addNewValue(size_t start, size_t count, DoublyArray* values)
{

}

bool CustomArrayIndicator::GoToQuote(size_t n)
{
	if (!qobject_cast<CustomPrice*>(m_baseIndicator)) return false;
	m_baseIndicator->GoToQuote(n);
	return GoToIndex(m_baseIndicator->ActualIndex());
}

CandleArray CustomArrayIndicator::GetCandles()
{
    if (!qobject_cast<CustomPrice*>(m_baseIndicator))
        return CandleArray();
    return qobject_cast<CustomPrice*>(m_baseIndicator)->GetCandles();

}

SerieInterval CustomArrayIndicator::Interval()
{
	return SerieInterval();
}

double CustomArrayIndicator::Max()
{
	return 0.0;
}

double CustomArrayIndicator::Min()
{
	return 0.0;
}

bool CustomArrayIndicator::GoToIndex(size_t n)
{
	if ((n > 0) and (n < Size())) {
		m_nIndex = n;
		return true;
	}
	return false;
}
