#ifndef CUSTOMDATASERIE_H
#define CUSTOMDATASERIE_H
#include "StockxxDataTypes.h"
#include <QDateTime>
#include <QList>
#include <QObject>

const quint32 c_StreamStart = 0xA0B0C0D0;
class CustomDataSerie : public QObject
{
    Q_OBJECT
protected:
    virtual void LoadSerieFromCSV(QString path, QChar delimiter);
    virtual void LoadSerieFromStream();
    virtual void SerieToStream();
    QString m_strPath = "D:\\Projects\\ChartOnGraphicsView\\DJI_D.dat";
    void ClearDataSerie();
    int m_nOffset = 1;
public:
    CustomDataSerie(AssetId assetID);
    QVector<DataSerieValue*> ar_values;
    AssetId assetID;
    virtual size_t Size();
};

#endif // CUSTOMDATASERIE_H
