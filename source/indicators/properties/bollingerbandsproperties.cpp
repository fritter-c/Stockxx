#include "bollingerbandsproperties.h"
#include "IndicatorDataTypes.h"
#include "ui_bollingerbandsproperties.h"

BollingerBandsProperties::BollingerBandsProperties(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BollingerBandsProperties)
{
    ui->setupUi(this);
    ui->comboBox->addItem(tr("Arithmetic"), static_cast<int>(mtArithmetic));
    ui->comboBox->addItem(tr("Exponential"), static_cast<int>(mtExponential));
    ui->comboBox_2->addItem(tr("Close"));
    ui->comboBox_2->addItem(tr("Open"));
    ui->comboBox_2->addItem(tr("High"));
    ui->comboBox_2->addItem(tr("Low"));
}

BollingerBandsProperties::~BollingerBandsProperties()
{
    delete ui;
}

MovingAverageType BollingerBandsProperties::getType()
{
    return static_cast<MovingAverageType>(ui->comboBox->currentIndex());
}

int BollingerBandsProperties::getInterval()
{
    return ui->spinBox->value();
}

int BollingerBandsProperties::getShift()
{
    return ui->spinBox_2->value();
}

IndicatorCalcOver BollingerBandsProperties::getCalcOver() const
{
    return static_cast<IndicatorCalcOver>(ui->comboBox_2->currentIndex());
}

double BollingerBandsProperties::getStdDev() const
{
    return ui->doubleSpinBox->value();
}
