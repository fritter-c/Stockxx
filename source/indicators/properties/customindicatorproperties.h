#ifndef CUSTOMINDICATORPROPERTIES_H
#define CUSTOMINDICATORPROPERTIES_H

#include "IndicatorDataTypes.h"
#include <QDialog>

namespace Ui {
class CustomIndicatorProperties;
}
enum PropertiesType {ptPrice = 0, ptMovingAverage = 1, ptVwap = 2, ptVolume = 3};
class CustomIndicatorProperties : public QDialog
{
    Q_OBJECT
private:
    Ui::CustomIndicatorProperties *ui;
    PropertiesType m_type;
    QWidget* style{nullptr};
    QWidget* properties{nullptr};

public:
    explicit CustomIndicatorProperties(QWidget *parent = nullptr);
    ~CustomIndicatorProperties();
    void setupForMovingAverage();
    const BasicIndicatorStyle& getBasicStyle();
    QWidget *getProperties();

};

#endif // CUSTOMINDICATORPROPERTIES_H
