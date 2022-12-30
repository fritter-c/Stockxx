#ifndef INDICATORDATATYPES_H
#define INDICATORDATATYPES_H


#include "candle.h"
#include "qcolor.h"
typedef struct{
    QuoteIdentifier id;
    bool valid;
    double value;
} IndicatorValue;

typedef QVector<QVector<IndicatorValue>> DoublyArray;
typedef QVector<QColor> ColorArray;
typedef QVector<Candle> CandleArray;

enum IndicatorType {itUnknown = -1,
                    itPrice = 0,
                    itMovingAverage = 1,
                    itVolume = 2,
                    itVwap = 3,
                    itBollingerBands = 4};

struct IndicatorIdentifier{
    IndicatorType type;
    int id;
public:
    IndicatorIdentifier(){
        type = itUnknown;
        id = -1;
    }
    inline bool operator==(const  IndicatorIdentifier &a) const{
        if((a.type == this->type) &&
           (a.id == this->id)){
            return true;
        }
        return false;
    }
};
inline uint qHash(const IndicatorIdentifier &key, uint seed)
{
    return (uint)qHash(key.type, seed) ^ (key.id + 1);
}
inline const IndicatorIdentifier AnonymousIndicator = IndicatorIdentifier();

enum MovingAverageType {mtArithmetic = 0,
                        mtExponential = 1};

enum PriceType {ptCandle = 0,
                ptLine = 1,
                ptMountain = 2,
                ptHeikinAshi = 3};

enum IndicatorCalcOver {icClose = 0,
                        icOpen = 1,
                        icHigh = 2,
                        icLow = 3};

struct IndicatorParam {
    int integer;
    double real;
    QString string;
    IndicatorParam(int i = 0, double d = 0.0, QString s = {}){
        integer = i;
        real = d;
        string = s;
    }
    IndicatorParam(double d = 0.0, int i = 0, QString s = {}){
        integer = i;
        real = d;
        string = s;
    }
    IndicatorParam(QString s = {}, double d = 0.0, int i = 0){
        integer = i;
        real = d;
        string = s;
    }
};

class CustomIndicatorStyle{
public:
    ~CustomIndicatorStyle() = default;

};

class BasicIndicatorStyle : public CustomIndicatorStyle{
public:
    BasicIndicatorStyle(){};
    Qt::PenStyle penStyle;
    int width;
    QColor color;
};

typedef QVector<IndicatorParam> IndicatorCalcParams;
typedef QVector<CustomIndicatorStyle*> IndicatorVisualParams;


#endif // INDICATORDATATYPES_H
