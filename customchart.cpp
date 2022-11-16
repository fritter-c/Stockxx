#include "customchart.h"
#include "qopenglwidget.h"
#include "ui_customchart.h"

CustomChart::CustomChart(AssetId assetid, QWidget *parent_main, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomChart)
{
    setAttribute(Qt::WA_DeleteOnClose);
    m_assetId = assetid;
    ui->setupUi(this);
    m_view = new GoTView(this);
    QOpenGLWidget *gl = new QOpenGLWidget();
    QSurfaceFormat format;
    format.setSamples(1);
    gl->setFormat(format);
    m_view->setViewport(gl);
    m_gManager = new GraphicManager(assetid, m_view, parent_main, this);
    ui->horizontalLayout->addWidget(m_view);
    setMouseTracking(true);
}

CustomChart::~CustomChart()
{
    delete m_gManager;
    delete m_view;
    delete ui;
}

GoTView* CustomChart::GetGraphicsView()
{
    return m_view;
}
