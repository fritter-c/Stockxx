#include "stockxxlinecombobox.h"
#include "ui_stockxxlinecombobox.h"

StockxxLineComboBox::StockxxLineComboBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StockxxLineComboBox)
{
    ui->setupUi(this);
    penStyleComboBox = new QComboBox(this);
    penStyleComboBox->addItem(tr("Solid"), static_cast<int>(Qt::SolidLine));
    penStyleComboBox->addItem(tr("Dash"), static_cast<int>(Qt::DashLine));
    penStyleComboBox->addItem(tr("Dot"), static_cast<int>(Qt::DotLine));
    penStyleComboBox->addItem(tr("Dash Dot"), static_cast<int>(Qt::DashDotLine));
    penStyleComboBox->addItem(tr("Dash Dot Dot"), static_cast<int>(Qt::DashDotDotLine));
    connect(penStyleComboBox, &QComboBox::activated,
            this, &StockxxLineComboBox::onPenChanged);
    ui->horizontalLayout->addWidget(penStyleComboBox);
    m_penStyle = Qt::SolidLine;
}

StockxxLineComboBox::~StockxxLineComboBox()
{
    delete ui;
}

Qt::PenStyle StockxxLineComboBox::penStyle() const
{
    return m_penStyle;
}

void StockxxLineComboBox::setPenStyle(Qt::PenStyle style)
{
    penStyleComboBox->setCurrentIndex(static_cast<int>(style) - 1);
    m_penStyle = style;
}

void StockxxLineComboBox::onPenChanged()
{
    m_penStyle = static_cast<Qt::PenStyle>(penStyleComboBox->currentIndex() + 1);
    emit penChanged();
}
