#ifndef BOLLINGERBANDSPROPERTIES_H
#define BOLLINGERBANDSPROPERTIES_H

#include "IndicatorDataTypes.h"
#include <QWidget>

namespace Ui {
class BollingerBandsProperties;
}

class BollingerBandsProperties : public QWidget
{
    Q_OBJECT
private:
    Ui::BollingerBandsProperties *ui;
public:
    explicit BollingerBandsProperties(QWidget *parent = nullptr);
    ~BollingerBandsProperties();
   MovingAverageType getType();
   int getInterval();
   int getShift();
   IndicatorCalcOver getCalcOver() const;
   double getStdDev() const;


};

#endif // BOLLINGERBANDSPROPERTIES_H
