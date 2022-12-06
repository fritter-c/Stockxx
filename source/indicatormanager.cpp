#include "indicatormanager.h"
#include "custompricecalc.h"
#include "customprice.h"
#include "dailydataseriecalc.h"
#include "dailydataserie.h"
#include "dataseriemanager.h"
#include "indicators/movingaverage.h"
#include "indicators/priceindicator.h"
#include "minutedataseriecalc.h"
#include "movingaveragecalc.h"
#include "priceindicatorcalc.h"

IndicatorManager* IndicatorManager::instance = nullptr;

void IndicatorManager::addNewIndicatorData(IndicatorIdentifier id, size_t start, size_t size)
{
    QMutex mutex;
    mutex.lock();
    IndicatorSeries* series{nullptr};
    CustomIndicatorCalc* calcIndicator{m_hshIndicatorsCalc[id]};
    bool bPriceIndicator{id.type == itPrice};
    if (m_hshIndicatorSeries.contains(id)){
        series = m_hshIndicatorSeries[id];
    }
    else{
        series = new IndicatorSeries();
        m_hshIndicatorSeries.insert(id, series);
    }

    if ((calcIndicator != nullptr) && (!bPriceIndicator)){
        series->start = start;
        series->size = size;
        DoublyArray array = ((CustomArrayIndicatorCalc*)calcIndicator)->getData();
        series->arr = new DoublyArray();
        series->arr->resize(array.count());
        for(size_t i{start}; i < size; i++){
            for(size_t j{0}; j < series->arr->count(); ++j){
                (*series->arr)[j].append(array[j][i]);
            }
        }
    }
    else if(calcIndicator != nullptr){
        series->start = start;
        series->size = size;
        CandleArray array = ((PriceIndicatorCalc*)calcIndicator)->getData();
        series->candleArr = new CandleArray();
        series->candleArr->resize(array.count());
        for(size_t i{start}; i < size; i++){
             (*series->candleArr).append(array[i]);
        }

    }

    mutex.unlock();
    emit newIndicatorData(id);

}

void IndicatorManager::onNewIndicatorData(IndicatorIdentifier id)
{
    IndicatorSeries* series{m_hshIndicatorSeries[id]};
    if (id.type != itPrice){
        CustomArrayIndicator* indicator{qobject_cast<CustomArrayIndicator*>(m_hshIndicators[id])};
        indicator->addNewValue(series->start, series->size, series->arr);
    }
    else{
        PriceIndicator* indicator{qobject_cast<PriceIndicator*>(m_hshIndicators[id])};
        indicator->addNewPrice(series->start, series->size, series->candleArr);
    }
    m_hshIndicatorSeries.remove(id);
    delete series;
}

IndicatorIdentifier IndicatorManager::getNewID(IndicatorType type)
{
    IndicatorIdentifier id;
    if (m_hshIDs.contains(type)){
        id.type = type;
        id.id = m_hshIDs[type]++;
        m_hshIDs[type] = id.id;
    }
    else{
        m_hshIDs.insert(type, 0);
        id.type = type;
        id.id = 0;
    }
    return id;
}

IndicatorManager::IndicatorManager(QObject *parent)
    : QObject{parent}
{
    assert(instance == nullptr);
    instance = this;
    connect(this, &IndicatorManager::newIndicatorData, this, &IndicatorManager::onNewIndicatorData);
}

void IndicatorManager::requestIndicator(AssetId id, SerieInterval si, IndicatorType type, IndicatorParamList params)
{
    CustomPriceCalc* calcPrice{nullptr};
    CustomPrice* price{nullptr};

    if (si == siDaily){
        DailyDataSerieCalc* serieCalc = DataSerieManager::Instance().getDailyDataSerieCalc(id, false);
        DailyDataSerie* serie  = DataSerieManager::Instance().getDailyDataSerie(id, false);
        calcPrice = new CustomPriceCalc(serieCalc);
        price = new CustomPrice(serie);

    }
    else{
        MinuteDataSerieCalc* serieCalc = DataSerieManager::Instance().getMinuteDataSerieCalc(id, si, false);
        MinuteDataSerie* serie = DataSerieManager::Instance().getMinuteDataSerie(id, si, false);
        calcPrice = new CustomPriceCalc(serieCalc);
        price = new CustomPrice(serie);

    }
    IndicatorIdentifier indicator{getNewID(type)};
    switch (type) {
        case itMovingAverage:{
            MovingAverage* maMain{new MovingAverage(price)};
            maMain->setID(indicator);
            m_hshIndicators.insert(indicator, maMain);

            MovingAverageCalc* maCalc{new MovingAverageCalc(calcPrice, params)};
            maCalc->setID(indicator);
            m_hshIndicatorsCalc.insert(indicator, maCalc);

            connect(this, &IndicatorManager::requestFull, maCalc, &CustomIndicatorCalc::onCalcSerieFull);
            emit requestFull(indicator);
            break;
        }
        case itPrice:{
            PriceIndicator* piMain{new PriceIndicator(price)};
            piMain->setID(indicator);
            m_hshIndicators.insert(indicator, piMain);
            PriceIndicatorCalc* piCalc{new PriceIndicatorCalc(calcPrice)};
            piCalc->setID(indicator);
            m_hshIndicatorsCalc.insert(indicator, piCalc);
            connect(this, &IndicatorManager::requestFull, piCalc, &CustomIndicatorCalc::onCalcSerieFull);
            emit requestFull(indicator);
            break;
        }
        default:
            delete calcPrice;
            delete price;
            break;
    }

}
