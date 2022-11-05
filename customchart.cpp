#include "customchart.h"
#include "ui_customchart.h"

CustomChart::CustomChart(AssetId assetid, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomChart)
{
    m_assetId = assetid;
    ui->setupUi(this);
    m_view = new GoTView(this);
    m_gManager = new GraphicManager(assetid, m_view, parent, this);
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
