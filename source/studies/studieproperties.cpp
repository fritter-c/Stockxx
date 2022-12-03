#include "studieproperties.h"
#include "ui_studieproperties.h"

StudieProperties::StudieProperties(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudieProperties)
{
    ui->setupUi(this);
}

StudieProperties::~StudieProperties()
{
    delete ui;
}
