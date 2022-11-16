#include "dataseriemanager.h"
#include "dailydataseriecalc.h"

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

DataSerieManager::DataSerieManager(QObject *parent)
    : QObject{parent}
{
    assert(instance == nullptr);
    instance = this;
    populateLocalDataseries();
}

void DataSerieManager::requestDailySerie(QString ticker)
{
    m_alphaVantageApi = new StockDataApi(ticker, this);
    connect(m_alphaVantageApi, &StockDataApi::dataReady, this, &DataSerieManager::onAlphaVantageJsonLoaded);
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
        DailyDataSerieCalc* aux2 = new DailyDataSerieCalc(id);
        m_dataSeriesCalc.append(aux2);
        return aux;
    }
    else{
        return nullptr;
    }
}

void DataSerieManager::onAlphaVantageJsonLoaded(QString ticker)
{
    AssetId id;
    id.name = ticker;
    DailyDataSerie* aux = new DailyDataSerie(id, false);
    if (m_alphaVantageApi != nullptr)
        aux->loadSerieFromJsonAV(m_alphaVantageApi->getJsonString());
    m_hshDataSeries.insert(id, aux);
    m_dataSeries.append(aux);
    populateLocalDataseries();

}
