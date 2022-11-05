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
    void loadStdDataSerie();
    static DataSerieManager* instance;
public:
    explicit DataSerieManager(QObject *parent = nullptr);

    static DataSerieManager& Instance(){
        return *instance;
    }
    void addNewJsonDataSerie(AssetId id);
    DailyDataSerie *getDailyDataSerie(AssetId id, bool bCreate = false);

public slots:
    void onAlphaVantageJsonLoaded();

signals:

};


#endif // DATASERIEMANAGER_H
