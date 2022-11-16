#ifndef DATASERIEMANAGER_H
#define DATASERIEMANAGER_H

#include "customdataserie.h"
#include "customdataseriecalc.h"
#include "dailydataserie.h"
#include "dailydataseriecalc.h"
#include "stockdataapi.h"
#include <QObject>

class DataSerieManager : public QObject
{
    Q_OBJECT
private:
    QList<CustomDataSerie*> m_dataSeries;
    QList<CustomDataSerieCalc*> m_dataSeriesCalc;
    QHash<AssetId, CustomDataSerie*> m_hshDataSeries;
    QHash<AssetId, CustomDataSerieCalc*> m_hshDataSeriesCalc;
    StockDataApi* m_alphaVantageApi{nullptr};
    QString m_path{"D:\\Projects\\ChartOnGraphicsView\\database\\assets\\daily"};
    void loadStdDataSerie();
    static DataSerieManager* instance;
    void populateLocalDataseries();
    void connectCalcSerie(CustomDataSerieCalc*);
    bool m_bWaitingCalc{false};
public:
    explicit DataSerieManager(QObject *parent = nullptr);
    void requestDailySerie(QString ticker);
    static DataSerieManager& Instance(){
        return *instance;
    }
    void addNewJsonDataSerie(AssetId id);
    DailyDataSerie *getDailyDataSerie(AssetId id, bool bCreate = false);
    DailyDataSerieCalc *getDailyDataSerieCalc(AssetId id, bool bCreate = false);
    QStringList avaiableDataSeries;

public slots:
    void onAlphaVantageJsonLoaded(QString ticker);
    void onCalcSerieReady(AssetId);

signals:
    void loadCalcSerieFromJsonAV(QString ticker);
    void graphReady(AssetId);
    void notifyMain();

};


#endif // DATASERIEMANAGER_H
