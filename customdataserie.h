#ifndef CUSTOMDATASERIE_H
#define CUSTOMDATASERIE_H

#include <QDateTime>
#include <QList>
#include <QObject>
#include "StockxxDataTypes.h"

class CustomDataSerie : public QObject
{
    Q_OBJECT
protected:
    virtual void loadSerieFromCSV(QString path, QChar delimiter);
    virtual void loadSerieFromStream();
    virtual void serieToStream();
    virtual void createId();
    QString m_strPath = "D:\\Projects\\ChartOnGraphicsView\\database\\assets\\";
    QString m_strDat;
    AssetId m_assetId;
    DataSerieIdentifier m_ID;
    void ClearDataSerie();
    int m_nOffset{siDaily};
public:
    CustomDataSerie(AssetId assetID);
    QVector<DataSerieValue*> ar_values;
    virtual void loadSerieFromJsonAV(QString json); // Alpha Vantage API
    virtual size_t Size();

    const DataSerieIdentifier &ID() const;
};

#endif // CUSTOMDATASERIE_H
