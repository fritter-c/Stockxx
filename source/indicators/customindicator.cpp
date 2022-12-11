#include "customindicator.h"

QGraphicsItem *CustomIndicator::visualParent() const
{
    return m_visualParent;
}

void CustomIndicator::addSubscriber(ICustomSerieNotifiable * subs)
{
    if(!m_subscribers.contains(subs)){
        m_subscribers.append(subs);
    }
}

void CustomIndicator::removeSubscriber(ICustomSerieNotifiable * subs)
{
    m_subscribers.removeOne(subs);
}

void CustomIndicator::NotifyNewData(size_t start)
{
    long long i{m_subscribers.size() - 1};
    while(i >= 0){
        try {
            m_subscribers[i]->OnNewData(start);
        } catch (...) {
            m_subscribers.remove(i);
        }
        i--;
    }
}

CustomIndicator::CustomIndicator(CustomSerie* base)
{
    m_baseIndicator = base;
    connect(this, &CustomIndicator::NewData, this, &CustomIndicator::NotifyNewData);
}

CustomIndicator::~CustomIndicator()
{
    delete m_baseIndicator;
}

IndicatorIdentifier CustomIndicator::ID() const
{
    return m_ID;
}

void CustomIndicator::setID(IndicatorIdentifier newNID)
{
    m_ID = newNID;
}

void CustomIndicator::setVisualParent(QGraphicsItem* parent)
{
    m_visualParent = parent;
}
