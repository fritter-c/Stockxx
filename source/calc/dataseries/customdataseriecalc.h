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
    virtual void createId();
    QString m_strPath = "D:\\Projects\\ChartOnGraphicsView\\assets\\";
    const QString m_strBasePath = "D:\\Projects\\ChartOnGraphicsView\\assets\\";
    QString m_strDat;
    AssetId m_assetId;
    DataSerieIdentifier m_ID;
    void ClearDataSerie();
    int m_nOffset = 1;
public:
    CustomDataSerieCalc(AssetId assetID);
    QVector<DataSerieValue*> ar_values;
    virtual void loadSerieFromJsonAV(QString json); // Alpha Vantage API
    virtual size_t Size();
    const DataSerieIdentifier &ID() const;

public slots:
    void onLoadSerieFromJsonAV(QString json);
signals:
    void serieReady(AssetId);

};

#endif // CUSTOMDATASERIECALC_H
