#ifndef MINUTEDATASERIECALC_H
#define MINUTEDATASERIECALC_H

#include "customdataseriecalc.h"
#include <QObject>

class MinuteDataSerieCalc : public CustomDataSerieCalc
{
    Q_OBJECT
private:
    const QString strPathSufix = "_M.dat";
    const QString strFolder = "\\minute\\";
    int m_nOffset{5};
    QString strOffset = "_" + QString::number(m_nOffset);

    // CustomDataSerie interface
protected:
    virtual void loadSerieFromCSV(QString path, QChar delimiter) override;
    virtual void loadSerieFromStream() override;
    virtual void serieToStream() override;

public:
    MinuteDataSerieCalc(AssetId assetId,int offset, bool bLoad = true);
    virtual void loadSerieFromJsonAV(QString json) override;
    int nOffset() const;
};

#endif // MINUTEDATASERIECALC_H
