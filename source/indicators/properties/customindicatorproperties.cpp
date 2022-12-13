#include "customindicatorproperties.h"
#include "indicators/properties/movingaverageproperties.h"
#include "ui_customindicatorproperties.h"
#include "customindicatorstyleform.h"



CustomIndicatorProperties::CustomIndicatorProperties(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustomIndicatorProperties)
{
    ui->setupUi(this);

}

CustomIndicatorProperties::~CustomIndicatorProperties()
{
    delete ui;
}

void CustomIndicatorProperties::setupForMovingAverage()
{
    QWidget* style;
    style = ui->Style_tab;
    QGridLayout* layout = new QGridLayout(style);
    this->style = new CustomIndicatorStyleForm(style);
    layout->addWidget(this->style);
    QWidget* properties;
    properties = ui->Properties_tab;
    QGridLayout* layout2 = new QGridLayout(properties);
    this->properties = new MovingAverageProperties(properties);
    layout2->addWidget(this->properties);
    setWindowTitle("Moving Average Properties");
    m_type = ptMovingAverage;
}

const BasicIndicatorStyle &CustomIndicatorProperties::getBasicStyle()
{
    return qobject_cast<CustomIndicatorStyleForm*>(style)->getStyle();
}

QWidget *CustomIndicatorProperties::getProperties()
{
    return properties;
}





