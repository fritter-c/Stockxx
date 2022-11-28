#ifndef INDICATORMANAGER_H
#define INDICATORMANAGER_H

#include "StockxxDataTypes.h"
#include "customindicatorvisual.h"
#include "customindicatorcalc.h"
#include "indicatorparam.h"
#include <QObject>

typedef struct{
    IndicatorIdentifier id;
    QList<QVector<double>> serie;
} IndicatorSerie;

typedef struct{
    CustomIndicatorCalc* calcIndicator;
    CustomIndicatorCalc* visualIndicator;
    IndicatorIdentifier id;
} IndicatorPair;

class IndicatorManager : public QObject
{
    Q_OBJECT
private:
    QVector<IndicatorSerie*> m_calcSeries;
    QVector<IndicatorPair> m_vectIndicators;
    QHash<IndicatorIdentifier, CustomIndicatorVisual*> m_hashIndicators;
    static IndicatorManager* instance;

public:
    explicit IndicatorManager(QObject *parent = nullptr);
    void addIndicatorSerie(size_t index, QObject *sender);
    static IndicatorManager& Instance(){
        return *instance;
    }
    void newIndicator(IndicatorType type, QVector<IndicatorParam> params, CustomPrice* base, TimeScaleVisual* ts, PriceScaleVisual* ps);

signals:
    void indicatorSerie(size_t index);

private slots:
    void onIndicatorSerie(size_t index);

};

#endif // INDICATORMANAGER_H
