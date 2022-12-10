#ifndef INDICATORDATATYPES_H
#define INDICATORDATATYPES_H


#include "candle.h"
#include "qcolor.h"

typedef QVector<QVector<double>> DoublyArray;
typedef QVector<QColor> ColorArray;
typedef QVector<Candle> CandleArray;

enum IndicatorType {itPrice = 0, itMovingAverage = 1};
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

struct IndicatorParam {
    int integer;
    double real;
    QString string;
};

typedef QVector<IndicatorParam> IndicatorParamList;


#endif // INDICATORDATATYPES_H
