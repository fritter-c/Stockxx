#include "studieproperties.h"
#include "qcolordialog.h"
#include "ui_studieproperties.h"

StudieProperties::StudieProperties(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudieProperties)
{
    ui->setupUi(this);
    ui->pushButton_ColorPicker->setStyleSheet("background-color: yellow;");
    connect(ui->LineComboBox, &StockxxLineComboBox::penChanged, this, &StudieProperties::onPenChanged);
}

StudieProperties::~StudieProperties()
{
    delete ui;
}

BasicStudieStyle StudieProperties::getStyle() const
{
    BasicStudieStyle style{ui->LineComboBox->penStyle(), ui->spinBox_LineWidth->value(), m_studieColor};
    return style;
}

void StudieProperties::setStyle(BasicStudieStyle style)
{
    ui->LineComboBox->setPenStyle(style.penStyle);
    QString qss = QString("background-color: %1").arg(style.color.name());
    ui->pushButton_ColorPicker->setStyleSheet(qss);
    m_studieColor = style.color;
    ui->pushButton_ColorPicker->update();
    ui->spinBox_LineWidth->setValue(style.width);
}

void StudieProperties::onPenChanged()
{
    emit styleChanged();
}

void StudieProperties::on_pushButton_ColorPicker_clicked()
{
    QColorDialog colordial;
    colordial.exec();
    if (colordial.result() == QDialog::Accepted){
        QColor col{ colordial.selectedColor() };
        m_studieColor = col;
        QString qss = QString("background-color: %1").arg(col.name());
        ui->pushButton_ColorPicker->setStyleSheet(qss);
        ui->pushButton_ColorPicker->update();
        emit styleChanged();
    }
}


void StudieProperties::on_spinBox_LineWidth_valueChanged(int arg1)
{
    emit styleChanged();
}

