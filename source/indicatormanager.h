#ifndef INDICATORMANAGER_H
#define INDICATORMANAGER_H

#include "IndicatorDataTypes.h"
#include "indicators/customindicator.h"
#include "customindicatorcalc.h"
#include <QObject>

struct IndicatorSeries{
    size_t start;
    size_t size;
    DoublyArray* arr;
    CandleArray* candleArr;
    ~IndicatorSeries(){
        delete arr;
        delete candleArr;
    }
};
class IndicatorManager : public QObject
{
    Q_OBJECT
private:
    static IndicatorManager* instance;
    QHash<IndicatorIdentifier, CustomIndicator*> m_hshIndicators;
    QHash<IndicatorIdentifier, CustomIndicatorCalc*> m_hshIndicatorsCalc;
    QHash<IndicatorIdentifier, IndicatorSeries*> m_hshIndicatorSeries;
    QHash<IndicatorType, int> m_hshIDs;


    IndicatorIdentifier getNewID(IndicatorType);
public:
    explicit IndicatorManager(QObject *parent = nullptr);
    static IndicatorManager& Instance(){
        return *instance;
    }
    CustomIndicator* requestIndicator(AssetId, SerieInterval, IndicatorType, IndicatorParamList);
    void addNewIndicatorData(IndicatorIdentifier, size_t, size_t);
    void addNewPriceIndicatorData(IndicatorIdentifier, size_t, size_t);

private slots:
    void onNewIndicatorData(IndicatorIdentifier);
signals:
    void requestFull(IndicatorIdentifier);
    void newIndicatorData(IndicatorIdentifier);
    void newPriceIndicatorData(IndicatorIdentifier);

};

#endif // INDICATORMANAGER_H
