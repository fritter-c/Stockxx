#ifndef INDICATORDATATYPES_H
#define INDICATORDATATYPES_H


#include "candle.h"
#include "qcolor.h"
typedef struct{
    double value;
    bool valid;
    QuoteIdentifier id;
} IndicatorValue;
typedef QVector<QVector<IndicatorValue>> DoublyArray;
typedef QVector<QColor> ColorArray;
typedef QVector<Candle> CandleArray;

enum IndicatorType {itPrice = 0, itMovingAverage = 1, itVolume = 2, itVwap = 3};
struct IndicatorIdentifier{
    IndicatorType type;
    int id;
public:
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
enum MovingAverageType {mtArithmetic = 0, mtExponential = 1};
enum IndicatorCalcOver {icClose = 0, icOpen = 1, icHigh = 2, icLow = 3};

struct IndicatorParam {
    int integer;
    double real;
    QString string;
    IndicatorParam(int i = 0, double d = 0.0, QString s = {}){
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
