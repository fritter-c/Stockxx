#include "customindicatorproperties.h"
#include "indicators/properties/bollingerbandsproperties.h"
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
    this->m_style = new CustomIndicatorStyleForm(style);
    layout->addWidget(this->m_style);
    QWidget* properties;
    properties = ui->Properties_tab;
    QGridLayout* layout2 = new QGridLayout(properties);
    this->m_properties = new MovingAverageProperties(properties);
    layout2->addWidget(this->m_properties);
    setWindowTitle("Moving Average Properties");
    m_type = ptMovingAverage;
}

void CustomIndicatorProperties::setupForBollingerBands()
{
    QWidget* style;
    style = ui->Style_tab;
    QGridLayout* layout = new QGridLayout(style);
    this->m_style = new CustomIndicatorStyleForm(style);
    layout->addWidget(this->m_style);
    QWidget* properties;
    properties = ui->Properties_tab;
    QGridLayout* layout2 = new QGridLayout(properties);
    this->m_properties = new BollingerBandsProperties(properties);
    layout2->addWidget(this->m_properties);
    setWindowTitle("Bollinger Bands Properties");
    m_type = ptMovingAverage;
}

const BasicIndicatorStyle CustomIndicatorProperties::getBasicStyle()
{
    if (qobject_cast<CustomIndicatorStyleForm*>(m_style))
        return qobject_cast<CustomIndicatorStyleForm*>(m_style)->getStyle();


    return BasicIndicatorStyle();
}

QWidget *CustomIndicatorProperties::getProperties()
{
    return m_properties;
}





