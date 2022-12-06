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


struct IndicatorParam{
public:
    virtual int getIntegerParam() = 0;
    virtual double getDoubleParam() = 0;
    virtual ~IndicatorParam()=default;
};

class IntegerParam : public IndicatorParam{
    int param;
public:
    IntegerParam(int i){
        param = i;
    }
    virtual int getIntegerParam() override{
        return param;
    }
    virtual double getDoubleParam() override{
        return 0;
    }
    ~IntegerParam(){};
};


class DoubleParam : public IndicatorParam{
    double param;
public:
    DoubleParam(double d){
        param = d;
    }
    virtual int getIntegerParam() override{
        return 0;
    }
    virtual double getDoubleParam() override{
        return param;
    }
    ~DoubleParam(){};

};

typedef QVector<IndicatorParam*> IndicatorParamList;


#endif // INDICATORDATATYPES_H
