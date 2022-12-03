#include "customindicatorcalc.h"

CustomIndicatorCalc::CustomIndicatorCalc(CustomSerieCalc* baseIndicator)
{

}

void CustomIndicatorCalc::onCalcSerieFull()
{
    createIndicatorValues();
}

void CustomIndicatorCalc::createIndicatorValues()
{
    emit newData(0);
}

void CustomIndicatorCalc::resize(size_t n)
{

}

void CustomIndicatorCalc::grow(size_t n)
{

}
