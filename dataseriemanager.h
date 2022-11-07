#ifndef DATASERIEMANAGER_H
#define DATASERIEMANAGER_H

#include "customdataserie.h"
#include "dailydataserie.h"
#include "stockdataapi.h"
#include <QObject>

class DataSerieManager : public QObject
{
    Q_OBJECT
private:
    QList<CustomDataSerie*> m_dataSeries;
    QHash<AssetId, CustomDataSerie*> m_hshDataSeries;
    StockDataApi* m_alphaVantageApi{nullptr};
    QString m_path{"D:\\Projects\\ChartOnGraphicsView\\database\\assets\\daily"};
    void loadStdDataSerie();
    static DataSerieManager* instance;
    void populateLocalDataseries();
public:
    explicit DataSerieManager(QObject *parent = nullptr);
    void requestDailySerie(QString ticker);
    static DataSerieManager& Instance(){
        return *instance;
    }
    void addNewJsonDataSerie(AssetId id);
    DailyDataSerie *getDailyDataSerie(AssetId id, bool bCreate = false);
    QStringList avaiableDataSeries;

public slots:
    void onAlphaVantageJsonLoaded(QString ticker);

signals:

};


#endif // DATASERIEMANAGER_H
