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
    QWidget* m_style{nullptr};
    QWidget* m_properties{nullptr};

public:
    explicit CustomIndicatorProperties(QWidget *parent = nullptr);
    ~CustomIndicatorProperties();
    void setupForMovingAverage();
    void setupForBollingerBands();
    const BasicIndicatorStyle getBasicStyle();
    QWidget *getProperties();

};

#endif // CUSTOMINDICATORPROPERTIES_H
