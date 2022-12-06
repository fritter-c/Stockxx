#ifndef DATASERIEMANAGER_H
#define DATASERIEMANAGER_H

#include "customdataserie.h"
#include "customdataseriecalc.h"
#include "dailydataserie.h"
#include "dailydataseriecalc.h"
#include "minutedataserie.h"
#include "stockdataapi.h"
#include "minutedataseriecalc.h"
#include <QObject>

class DataSerieManager : public QObject
{
    Q_OBJECT
private:
    QList<CustomDataSerie*> m_dataSeries;
    QList<CustomDataSerieCalc*> m_dataSeriesCalc;
    QHash<DataSerieIdentifier, CustomDataSerie*> m_hshDataSeries;
    QHash<DataSerieIdentifier, CustomDataSerieCalc*> m_hshDataSeriesCalc;
    StockDataApi* m_alphaVantageApi{nullptr};
    QString m_path{"D:\\Projects\\ChartOnGraphicsView\\database\\assets\\daily"};
    void loadStdDataSerie();
    static DataSerieManager* instance;
    void populateLocalDataseries();
    void connectCalcSerie(CustomDataSerieCalc*);
    void disconnectCalcSerie(CustomDataSerieCalc*);
    bool m_bWaitingCalc{false};
    int m_requestedOffset{1};
    DataSerieIdentifier getDataID(AssetId, int);
public:
    explicit DataSerieManager(QObject *parent = nullptr);
    void requestDailySerie(QString ticker);
    void requestMinuteSerie(QString ticker, int offset);
    static DataSerieManager& Instance(){
        return *instance;
    }
    void addNewJsonDataSerie(AssetId id);
    DailyDataSerie *getDailyDataSerie(AssetId id, bool bCreate = false);
    MinuteDataSerie* getMinuteDataSerie(AssetId id, int offset, bool bCreate = false);
    DailyDataSerieCalc *getDailyDataSerieCalc(AssetId id, bool bCreate = false);
    MinuteDataSerieCalc* getMinuteDataSerieCalc(AssetId id, int offset, bool bCreate = false);
    QStringList avaiableDataSeries;

public slots:
    void onAlphaVantageJsonLoadedDaily(QString ticker);
    void onAlphaVantageJsonLoadedMinute(QString ticker);
    void onCalcSerieReady(AssetId);

signals:
    void loadCalcSerieFromJsonAV(QString ticker);
    void graphReady(DataSerieIdentifier);
    void notifyMain();

};


#endif // DATASERIEMANAGER_H
