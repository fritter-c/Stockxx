#include "indicatormanager.h"

IndicatorManager* IndicatorManager::instance = nullptr;
IndicatorManager::IndicatorManager(QObject *parent)
    : QObject{parent}
{
    assert(instance == nullptr);
    instance = this;
    connect(this, &IndicatorManager::indicatorSerie, this, &IndicatorManager::onIndicatorSerie);
}

void IndicatorManager::addIndicatorSerie(size_t index, QObject* sender)
{
    CustomIndicatorCalc* calcSender = qobject_cast<CustomIndicatorCalc*>(sender);
    IndicatorIdentifier id {calcSender->id()};
    IndicatorSerie* newSerie;
    newSerie = new IndicatorSerie();
    newSerie->id = id;
    QMutex mutex;

    mutex.lock();
    newSerie->serie.reserve(calcSender->Width());
    for(size_t i{index}; i < calcSender->Size(); ++i){
        for(size_t j{0}; j < newSerie->serie.size(); ++j){
            newSerie->serie[j].append(calcSender[j][index]);
        }
    }
    m_calcSeries.append(newSerie);
    emit indicatorSerie(index);
    mutex.unlock();


}

void IndicatorManager::onIndicatorSerie(size_t index)
{
    IndicatorSerie* newSerie = m_calcSeries.last();
    m_calcSeries.pop_back();
    if (m_hashIndicators.contains(newSerie->id)){
        IndicatorData* data{m_hashIndicators[newSerie->id]->data()};
        if((index + newSerie->serie[0].size()) > data->Size())
            data->grow(data->Size() - (index + newSerie->serie[0].size()));

        size_t nIndex{0};
        for(size_t i{index}; i < data->Size(); ++i){
            for(size_t j{0}; j < newSerie->serie.size(); ++j){
                (*data)[j][index] = newSerie->serie[j][nIndex];
            }
            nIndex++;
        }
    }
    delete newSerie;
}

