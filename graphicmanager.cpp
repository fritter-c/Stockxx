#include "graphicmanager.h"
#include "candlemagnifier.h"
#include "dailyprice.h"
#include "mainwindow.h"
#include <QResizeEvent>
#include "resistancestudie.h"


void GraphicManager::addStudie(QMouseEvent *event)
{
    if(m_mainStudie == stResistance){
        m_visualStudies.append(new ResistanceStudie(m_psVisual->PriceAtY(event->pos().y()), m_tsVisual, m_psVisual, m_priceVisual));
        m_scene->addItem(m_visualStudies[m_visualStudies.count() - 1]);
    }
}

GraphicManager::GraphicManager(QObject *parent, CustomChart *chart)
    : QObject{parent}
{
    m_chart = chart;
    m_view = chart->GetGraphicsView();
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


    m_visualItems.append(m_priceVisual);
    m_visualItems.append(m_psVisual);
    m_visualItems.append(m_tsVisual);
}

CustomChart *GraphicManager::GetCustomChart()
{
    return m_chart;
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
    if (enabled)
        m_mainStudie = studie;
}

void GraphicManager::onViewMouseClick(QMouseEvent *event)
{
    for (int i{0}; i < m_visualStudies.size(); ++i){
        if (m_visualStudies[i]->isUnderMouse()){
            m_draggingStudie = m_visualStudies[i];
            m_selectedStudie = m_draggingStudie;
            return;
        }
    }
    if ((event->button() == Qt::LeftButton) and (not m_candleMag->isUnderMouse())){
        addStudie(event);
    }
    m_selectedStudie = nullptr; // não estava em cima de nenhum estudo, desceleciona

}

void GraphicManager::onViewMouseRelease(QMouseEvent *event)
{
    m_draggingStudie = nullptr;
}

void GraphicManager::onViewMouseMove(QMouseEvent *event)
{
    if (m_draggingStudie != nullptr){
        m_draggingStudie->updatePrice(m_psVisual->PriceAtY(event->pos().y()));
        return;
    }
}

void GraphicManager::onViewKeyPress(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Delete){
        if (m_selectedStudie != nullptr){
            for(int i{0}; i < m_visualStudies.count(); ++i){
                if (m_visualStudies[i] == m_selectedStudie){
                    m_visualStudies.remove(i);
                    break;
                }
            }
            delete m_selectedStudie;
            m_selectedStudie = nullptr;
        }
    }
}

void GraphicManager::onMainCrossToggled(bool)
{
    m_priceVisual->toggleCross();
}



