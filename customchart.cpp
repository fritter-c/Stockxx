#include "customchart.h"
#include "ui_customchart.h"

CustomChart::CustomChart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomChart)
{
    ui->setupUi(this);
    m_view = new GoTView(this);
    ui->horizontalLayout->addWidget(m_view);
    setMouseTracking(true);
}

CustomChart::~CustomChart()
{
    delete ui;
}

GoTView* CustomChart::GetGraphicsView()
{
    return m_view;
}
