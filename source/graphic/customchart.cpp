#include "customchart.h"
#include "ui_customchart.h"

CustomChart::CustomChart(AssetId assetid, SerieInterval si, QWidget *parent_main, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomChart)
{
    m_assetId = assetid;
    ui->setupUi(this);
    m_view = new GoTView(this);
    //QOpenGLWidget *gl = new QOpenGLWidget();
    //QSurfaceFormat format;
    //format.setSamples(1);
    //gl->setFormat(format);
    //m_view->setViewport(gl);
    m_gManager = new GraphicManager(assetid,si, m_view, parent_main, this);
    ui->horizontalLayout->addWidget(m_view);
    setMouseTracking(true);
}

CustomChart::~CustomChart()
{
    // é necessário deletar o manager antes;
    delete m_gManager;
    delete ui;
}

GoTView* CustomChart::GetGraphicsView()
{
    return m_view;
}

GraphicManager *CustomChart::gManager() const
{
    return m_gManager;
}
