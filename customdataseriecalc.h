#ifndef CUSTOMDATASERIECALC_H
#define CUSTOMDATASERIECALC_H

#include <QObject>
#include "StockxxDataTypes.h"

class CustomDataSerieCalc : public QObject
{
    Q_OBJECT
protected:
    virtual void loadSerieFromCSV(QString path, QChar delimiter);
    virtual void loadSerieFromStream();
    virtual void serieToStream();
    QString m_strPath = "D:\\Projects\\ChartOnGraphicsView\\database\\assets\\daily\\";
    QString m_strDat;
    AssetId m_assetId;
    void ClearDataSerie();
    int m_nOffset = 1;
public:
    CustomDataSerieCalc(AssetId assetID);
    QVector<DataSerieValue*> ar_values;
    virtual void loadSerieFromJsonAV(QString json); // Alpha Vantage API
    virtual size_t Size();

};

#endif // CUSTOMDATASERIECALC_H
