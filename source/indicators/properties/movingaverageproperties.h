#ifndef MOVINGAVERAGEPROPERTIES_H
#define MOVINGAVERAGEPROPERTIES_H

#include "IndicatorDataTypes.h"
#include <QWidget>

namespace Ui {
class MovingAverageProperties;
}

class MovingAverageProperties : public QWidget
{
    Q_OBJECT
public:
    explicit MovingAverageProperties(QWidget *parent = nullptr);
    ~MovingAverageProperties();
    MovingAverageType getType();
    int getInterval();
    int getShift();
    IndicatorCalcOver getCalcOver();


private:
    Ui::MovingAverageProperties *ui;
};

#endif // MOVINGAVERAGEPROPERTIES_H
