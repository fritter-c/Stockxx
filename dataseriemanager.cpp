#include "dataseriemanager.h"
#include "dailydataseriecalc.h"
#include "minutedataserie.h"
#include "minutedataseriecalc.h"

DataSerieManager* DataSerieManager::instance = nullptr;

void DataSerieManager::loadStdDataSerie()
{

}

void DataSerieManager::populateLocalDataseries()
{
    QDir dir(m_path);
    QStringList aux = dir.entryList(QStringList() << "*.dat", QDir::Files);

    foreach(const QString& word, aux){
        avaiableDataSeries.append(word.left(word.count() - 6));
    }
}

void DataSerieManager::connectCalcSerie(CustomDataSerieCalc *calcSerie)
{
    connect(this, &DataSerieManager::loadCalcSerieFromJsonAV,
            calcSerie, &CustomDataSerieCalc::onLoadloadSerieFromJsonAV);

    connect(calcSerie, &CustomDataSerieCalc::serieReady,
            this, &DataSerieManager::onCalcSerieReady);
}

DataSerieManager::DataSerieManager(QObject *parent)
    : QObject{parent}
{
    assert(instance == nullptr);
    instance = this;
    populateLocalDataseries();
    m_alphaVantageApi = new StockDataApi(this);
}

void DataSerieManager::requestDailySerie(QString ticker)
{
    connect(m_alphaVantageApi, &StockDataApi::dataReady, this, &DataSerieManager::onAlphaVantageJsonLoadedDaily);
    m_alphaVantageApi->requestDailySerie(ticker);
    m_bWaitingCalc = true;
}

void DataSerieManager::requestMinuteSerie(QString ticker, int offset)
{
    connect(m_alphaVantageApi, &StockDataApi::dataReady, this, &DataSerieManager::onAlphaVantageJsonLoadedMinute);
    m_requestedOffset = offset;
    m_alphaVantageApi->requestMinuteSerie(ticker, offset);
}

DailyDataSerie* DataSerieManager::getDailyDataSerie(AssetId id, bool bCreate)
{

    if (m_hshDataSeries.contains(id)){
        return dynamic_cast<DailyDataSerie*>(m_hshDataSeries[id]);
    }
    else if (bCreate){
        DailyDataSerie* aux = new DailyDataSerie(id);
        m_hshDataSeries.insert(id, aux);
        m_dataSeries.append(aux);
        return aux;
    }
    else{
        return nullptr;
    }
}

DailyDataSerieCalc *DataSerieManager::getDailyDataSerieCalc(AssetId id, bool bCreate)
{
    if (m_hshDataSeries.contains(id)){
        return dynamic_cast<DailyDataSerieCalc*>(m_hshDataSeriesCalc[id]);
    }
    else if (bCreate){
        DailyDataSerieCalc* aux = new DailyDataSerieCalc(id);
        m_dataSeriesCalc.append(aux);
        connectCalcSerie(aux);
        return aux;
    }
    else{
        return nullptr;
    }
}

void DataSerieManager::onAlphaVantageJsonLoadedDaily(QString ticker)
{
    disconnect(m_alphaVantageApi, &StockDataApi::dataReady, this, &DataSerieManager::onAlphaVantageJsonLoadedDaily);
    AssetId id;
    id.name = ticker;
    DailyDataSerieCalc* aux = new DailyDataSerieCalc(id, false);
    connectCalcSerie(aux);
    if (m_alphaVantageApi != nullptr){
        emit loadCalcSerieFromJsonAV(m_alphaVantageApi->getJsonString());
    }
    emit notifyMain();
    m_bWaitingCalc = true;
    m_dataSeriesCalc.append(aux);
    m_hshDataSeriesCalc.insert(id, aux);
}

void DataSerieManager::onAlphaVantageJsonLoadedMinute(QString ticker)
{
    disconnect(m_alphaVantageApi, &StockDataApi::dataReady, this, &DataSerieManager::onAlphaVantageJsonLoadedMinute);
    AssetId id;
    id.name = ticker;
    MinuteDataSerieCalc* aux = new MinuteDataSerieCalc(id, m_requestedOffset);
    connectCalcSerie(aux);
     if (m_alphaVantageApi != nullptr){
         emit loadCalcSerieFromJsonAV(m_alphaVantageApi->getJsonString());
     }
     emit notifyMain();
     m_bWaitingCalc = true;
     m_dataSeriesCalc.append(aux);
     m_hshDataSeriesCalc.insert(id, aux);
}

void DataSerieManager::onCalcSerieReady(AssetId id)
{
    populateLocalDataseries();
    emit notifyMain();
    if (m_bWaitingCalc){
        if (qobject_cast<DailyDataSerieCalc*>(sender())){
            DailyDataSerie* aux = new DailyDataSerie(id);
            m_hshDataSeries.insert(id, aux);
            m_dataSeries.append(aux);
            m_bWaitingCalc = false;
        }
        else if (qobject_cast<MinuteDataSerieCalc*>(sender())){
            MinuteDataSerieCalc* calc = qobject_cast<MinuteDataSerieCalc*>(sender());
            MinuteDataSerie* aux = new MinuteDataSerie(id, calc->nOffset());
            m_hshDataSeries.insert(id, aux);
            m_dataSeries.append(aux);
            m_bWaitingCalc = false;

        }
    }
    emit notifyMain();
    emit graphReady(id);
}
