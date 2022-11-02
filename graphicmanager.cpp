#include "graphicmanager.h"
#include "candlemagnifier.h"
#include "dailyprice.h"
#include "fibonaccistudie.h"
#include "linestudie.h"
#include "mainwindow.h"
#include <QResizeEvent>
#include "resistancestudie.h"
#include "vertlinestudie.h"

GraphicManager::GraphicManager(GoTView *m_view, QObject *parent, QWidget *chart)
    : QObject{parent}
{
    m_chart = chart;
    this->m_view = m_view;
    m_scene = new QGraphicsScene(0,0, m_view->width(), m_view->height(), m_view);
    m_assetId.name = "PETR4";

    m_view->setScene(m_scene);
    m_dailyDataSerie = new DailyDataSerie(m_assetId);
    m_priceVisual = new PriceVisual(new DailyPrice(m_dailyDataSerie, this), this, m_view);
    m_psVisual = m_priceVisual->GetPriceScale();
    m_tsVisual = m_priceVisual->GetTimeScale();
    m_candleMag = new CandleMagnifier();
    m_scene->addItem(m_tsVisual);
    m_scene->addItem(m_psVisual);
    m_scene->addItem(m_priceVisual);
    m_scene->addItem(m_candleMag);
    m_baseIndicator = m_priceVisual;

    connect(m_view, &GoTView::Resize, this,&GraphicManager::onViewResize);
    connect(qobject_cast<MainWindow*>(parent), &MainWindow::studieSelected, this, &GraphicManager::onMainStudieSelected);
    connect(qobject_cast<MainWindow*>(parent), &MainWindow::crossToggles, this, &GraphicManager::onMainCrossToggled);
    connect(m_view, &GoTView::MouseClick, this, &GraphicManager::onViewMouseClick);
    connect(m_view, &GoTView::MouseRelease, this, &GraphicManager::onViewMouseRelease);
    connect(m_view, &GoTView::MouseMove, this, &GraphicManager::onViewMouseMove);
    connect(m_view, &GoTView::KeyPress, this, &GraphicManager::onViewKeyPress);
    connect(qobject_cast<MainWindow*>(parent), &MainWindow::handToggles, this, &GraphicManager::onMainHandToggle);
    connect(qobject_cast<MainWindow*>(parent), &MainWindow::deleteAllStudies, this, &GraphicManager::onMainDeleteAllStudies);

    m_visualItems.append(m_priceVisual);
    m_visualItems.append(m_psVisual);
    m_visualItems.append(m_tsVisual);
}

void GraphicManager::addStudie(QMouseEvent *event)
{
    if(m_mainStudie == stResistance){
        m_visualStudies.append(new ResistanceStudie(m_psVisual->PriceAtY(event->pos().y()), m_tsVisual, m_psVisual, m_priceVisual));
    }
    else if(m_mainStudie == stLine){
        m_visualStudies.append(new LineStudie(event->pos().x(),m_psVisual->PriceAtY(event->pos().y()), m_tsVisual, m_psVisual, m_priceVisual));
        m_selectedStudie = m_visualStudies.last();
        m_bAddingStudie = true;
    }
    else if(m_mainStudie == stFibonacci){
        m_visualStudies.append(new FibonacciStudie(event->pos().x(),m_psVisual->PriceAtY(event->pos().y()), m_tsVisual, m_psVisual, m_priceVisual));
        m_selectedStudie = m_visualStudies.last();
        m_bAddingStudie = true;
    }
    else if(m_mainStudie == stVertLine){
        m_visualStudies.append(new VertLineStudie(event->pos().x(), m_tsVisual, m_psVisual, m_priceVisual));
    }
}

void GraphicManager::fullUpdate()
{
    for (int i{0}; i < m_visualStudies.size(); ++i){
        m_visualStudies[i]->changeGeometry();
    }
    m_baseIndicator->update();
}
void GraphicManager::candleHoveredChanged()
{
    dynamic_cast <CandleMagnifier*>(m_candleMag)->setSelectedCandle(m_priceVisual->getHoveredCandle());
}

void GraphicManager::onViewResize(QResizeEvent *event)
{
    m_psVisual->changeGeometry();
    dynamic_cast <CandleMagnifier*>(m_candleMag)->changeSize(QSizeF{m_view->size()});
    m_scene->setSceneRect(0, 0, m_view->width(), m_view->height());
    if (m_psVisual)
       m_psVisual->UpdateSpacing();
    if (m_tsVisual)
        m_tsVisual->recalculatePositions();
    m_priceVisual->changeGeometry();
    for (int i{0}; i < m_visualStudies.size(); ++i){
        m_visualStudies[i]->changeGeometry();
    }
}

void GraphicManager::onMainStudieSelected(StudieType studie, bool enabled)
{
    if (enabled){
        m_mainStudie = studie;
        m_view->setCursor(Qt::BitmapCursor);
    }
    else
        m_mainStudie = stNoStudie;
}

void GraphicManager::onViewMouseClick(QMouseEvent *event)
{
    for (int i{0}; i < m_visualStudies.size(); ++i){
        if (m_visualStudies[i]->isUnderMouse()){
            m_draggingStudie = m_visualStudies[i];
            m_selectedStudie = m_draggingStudie;
            m_draggingChart  = false;
            return;
        }
    }
    if ((event->button() == Qt::LeftButton) and (not m_candleMag->isUnderMouse())){
        addStudie(event);
    }
    else{
        m_selectedStudie = nullptr; // não estava em cima de nenhum estudo, desceleciona
    }
    if (m_bHandMode){
        m_draggingChart = true;
        m_view->setCursor(Qt::ClosedHandCursor);
    }
    else{
        m_draggingChart = false;
    }
}

void GraphicManager::onViewMouseRelease(QMouseEvent *event)
{
    m_draggingStudie = nullptr;
    m_draggingChart = false;
    m_bAddingStudie = false;
    if (m_bHandMode){
        m_view->setCursor(Qt::OpenHandCursor);
    }
}

void GraphicManager::onViewMouseMove(QMouseEvent *event)
{
    const int c_yProportion{10};
    if ((m_bAddingStudie) and (m_selectedStudie != nullptr)){
        m_selectedStudie->updateLastPos(event->pos());
        return;
    }
    else if (m_draggingStudie != nullptr){
        m_draggingStudie->updatePrice(m_psVisual->PriceAtY(event->pos().y()));
        return;
    }
    else if((m_bHandMode) and (m_draggingChart) and (not m_candleMag->isUnderMouse())) {
        m_psVisual->movePrice((event->pos().y() - m_lastChartPos.y())/c_yProportion);
        m_tsVisual->moveTime((int)(-event->pos().x() + m_lastChartPos.x()));
        fullUpdate();

    }
    m_lastChartPos = event->pos();
}

void GraphicManager::onViewKeyPress(QKeyEvent *event)
{


}

void GraphicManager::onMainCrossToggled(bool enabled)
{
    m_priceVisual->toggleCross();
    if (enabled){
        m_view->setCursor(Qt::BlankCursor);
    }
    else{
        m_view->setCursor(Qt::ArrowCursor);
    }
}

void GraphicManager::onMainHandToggle(bool enabled)
{
    m_bHandMode = not m_bHandMode;
    if (enabled){
        m_view->setCursor(Qt::OpenHandCursor);
    }
    else{
        m_view->setCursor(Qt::ArrowCursor);
    }
}

void GraphicManager::onMainDeleteAllStudies()
{
    for(long long i{m_visualStudies.size() - 1}; i >= 0; --i){
        delete m_visualStudies[i];
        m_visualStudies.pop_back();
    }
}



