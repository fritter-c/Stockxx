#include "customindicatorstyleform.h"
#include "qcolordialog.h"
#include "qdialog.h"
#include "ui_customindicatorstyleform.h"

void CustomIndicatorStyleForm::styleChanged()
{
    ui->LineSample->setlineStyle(m_style);
}

CustomIndicatorStyleForm::CustomIndicatorStyleForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomIndicatorStyleForm)
{
    ui->setupUi(this);
    m_lineColor = Qt::green;
    m_style.color = m_lineColor;
    m_style.width = 1;
    m_style.penStyle = Qt::SolidLine;
    ui->pushButton->setStyleSheet("background-color: green;");
    connect(ui->LineCombobox, &StockxxLineComboBox::penChanged, this, &CustomIndicatorStyleForm::onPenChanged);
    connect(ui->spinBox, &QSpinBox::valueChanged, this, &CustomIndicatorStyleForm::onWidthChanged);
    styleChanged();
}

CustomIndicatorStyleForm::~CustomIndicatorStyleForm()
{
    delete ui;
}

const BasicIndicatorStyle &CustomIndicatorStyleForm::getStyle()
{
    return m_style;
}

void CustomIndicatorStyleForm::on_pushButton_clicked()
{
    QColorDialog colordial;
    colordial.exec();
    if (colordial.result() == QDialog::Accepted){
        QColor col{ colordial.selectedColor() };
        m_lineColor = col;
        QString qss = QString("background-color: %1").arg(col.name());
        ui->pushButton->setStyleSheet(qss);
        ui->pushButton->update();
        m_style.color = col;
        styleChanged();
    }
}

void CustomIndicatorStyleForm::onPenChanged()
{
    m_style.penStyle = ui->LineCombobox->penStyle();
    styleChanged();
}

void CustomIndicatorStyleForm::onWidthChanged()
{
    m_style.width = ui->spinBox->value();
    styleChanged();
}

