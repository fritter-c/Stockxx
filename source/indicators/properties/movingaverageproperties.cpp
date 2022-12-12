#include "movingaverageproperties.h"
#include "IndicatorDataTypes.h"
#include "ui_movingaverageproperties.h"

MovingAverageProperties::MovingAverageProperties(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MovingAverageProperties)
{
    ui->setupUi(this);
    ui->comboBox->addItem(tr("Arithmetic"), static_cast<int>(mtArithmetic));
    ui->comboBox->addItem(tr("Exponential"), static_cast<int>(mtExponential));
    ui->comboBox_2->addItem(tr("Close"));
    ui->comboBox_2->addItem(tr("Open"));
    ui->comboBox_2->addItem(tr("High"));
    ui->comboBox_2->addItem(tr("Low"));
}

MovingAverageProperties::~MovingAverageProperties()
{
    delete ui;
}

MovingAverageType MovingAverageProperties::getType()
{
    return static_cast<MovingAverageType>(ui->comboBox->currentIndex());
}

int MovingAverageProperties::getInterval()
{
    return ui->spinBox->value();
}

int MovingAverageProperties::getShift()
{
    return ui->spinBox_2->value();
}

IndicatorCalcOver MovingAverageProperties::getCalcOver()
{
    return static_cast<IndicatorCalcOver>(ui->comboBox_2->currentIndex());
}
