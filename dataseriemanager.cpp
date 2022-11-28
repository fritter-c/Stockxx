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
    connect(this, SIGNAL(loadCalcSerieFromJsonAV(QString)),
            calcSerie, SLOT(onLoadSerieFromJsonAV(QString)));

    connect(calcSerie, SIGNAL(serieReady(AssetId)),
            this, SLOT(onCalcSerieReady(AssetId)));
}

void DataSerieManager::disconnectCalcSerie(CustomDataSerieCalc * calcSerie)
{
    disconnect(this, SIGNAL(loadCalcSerieFromJsonAV(QString)),
              calcSerie, SLOT(onLoadSerieFromJsonAV(QString)));

    disconnect(calcSerie, SIGNAL(serieReady(AssetId)),
               this, SLOT(onCalcSerieReady(AssetId)));
}

DataSerieIdentifier DataSerieManager::getDataID(AssetId id, int offset)
{
    DataSerieIdentifier dsid;

    dsid.id = id;
    switch (offset) {
        case 1:
            dsid.si = siOneMin;
        break;
        case 5:
            dsid.si = siFiveMin;
        case 15:
            dsid.si = siFifteenMin;
        case 30:
            dsid.si = siThirtyMin;
        case 60:
            dsid.si = siSixtyMin;
        default:
            dsid.si = siDaily;
    }
    return dsid;
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
    if (m_hshDataSeries.contains(getDataID(id, 1))){
        return dynamic_cast<DailyDataSerie*>(m_hshDataSeries[getDataID(id, 1)]);
    }
    else if (bCreate){
        DailyDataSerie* aux = new DailyDataSerie(id);
        m_hshDataSeries.insert(aux->ID(), aux);
        m_dataSeries.append(aux);
        return aux;
    }
    else{
        return nullptr;
    }
}

MinuteDataSerie *DataSerieManager::getMinuteDataSerie(AssetId id, int offset, bool bCreate)
{
    if (m_hshDataSeries.contains(getDataID(id, offset))){
        return dynamic_cast<MinuteDataSerie*>(m_hshDataSeries[getDataID(id, offset)]);
    }
    else if (bCreate){
        MinuteDataSerie* aux = new MinuteDataSerie(id, offset);
        m_hshDataSeries.insert(aux->ID(), aux);
        m_dataSeries.append(aux);
        return aux;
    }
    else{
        return nullptr;
    }
}

DailyDataSerieCalc *DataSerieManager::getDailyDataSerieCalc(AssetId id, bool bCreate)
{
    if (m_hshDataSeries.contains(getDataID(id, 0))){
        return dynamic_cast<DailyDataSerieCalc*>(m_hshDataSeriesCalc[getDataID(id, 0)]);
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
    m_hshDataSeriesCalc.insert(aux->ID(), aux);
}

void DataSerieManager::onAlphaVantageJsonLoadedMinute(QString ticker)
{
    disconnect(m_alphaVantageApi, &StockDataApi::dataReady, this, &DataSerieManager::onAlphaVantageJsonLoadedMinute);
    AssetId id;
    id.name = ticker;
    MinuteDataSerieCalc* aux = new MinuteDataSerieCalc(id, m_requestedOffset, false);
    connectCalcSerie(aux);
     if (m_alphaVantageApi != nullptr){
         emit loadCalcSerieFromJsonAV(m_alphaVantageApi->getJsonString());
     }
     emit notifyMain();
     m_bWaitingCalc = true;
     m_dataSeriesCalc.append(aux);
     m_hshDataSeriesCalc.insert(aux->ID(), aux);
}

void DataSerieManager::onCalcSerieReady(AssetId id)
{
    populateLocalDataseries();
    emit notifyMain();
    CustomDataSerie* aux{nullptr};
    if (m_bWaitingCalc){
        if (qobject_cast<DailyDataSerieCalc*>(sender())){
            aux = new DailyDataSerie(id);
            aux->setCalcSerie(qobject_cast<DailyDataSerieCalc*>(sender()));
            m_hshDataSeries.insert(aux->ID(), aux);
            m_dataSeries.append(aux);
            m_bWaitingCalc = false;
        }
        else {
            MinuteDataSerieCalc* calc = qobject_cast<MinuteDataSerieCalc*>(sender());
            aux = new MinuteDataSerie(id, calc->nOffset());
            aux->setCalcSerie(calc);
            m_hshDataSeries.insert(aux->ID(), aux);
            m_dataSeries.append(aux);
            m_bWaitingCalc = false;

        }
    }
    disconnectCalcSerie(qobject_cast<CustomDataSerieCalc*>(sender()));
    emit notifyMain();
    if (aux)
        emit graphReady(aux->ID());
}
