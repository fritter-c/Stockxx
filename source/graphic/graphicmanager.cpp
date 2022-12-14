#include "graphicmanager.h"
#include "fibonaccistudie.h"
#include "freehandstudie.h"
#include "linestudie.h"
#include "mainwindow.h"
#include <QResizeEvent>
#include "resistancestudie.h"
#include "vertlinestudie.h"
#include "channelstudie.h"
#include "dataseriemanager.h"
#include "indicatormanager.h"
#include <QGraphicsProxyWidget>
#include "source/indicators/visuals/movingaveragevisual.h"

GraphicManager::GraphicManager(AssetId assetId, SerieInterval si, GoTView* m_view, QWidget* parent_main, QWidget* chart)
	: QObject{ chart }
{
	m_chart = chart;
	this->m_view = m_view;
	m_assetId = assetId;
	m_sInterval = si;
	m_scene = new QGraphicsScene(0, 0, m_view->width(), m_view->height(), m_view);
	m_view->setScene(m_scene);
	
	if (m_sInterval == siDaily)
		m_mainDataSerie = DataSerieManager::Instance().getDailyDataSerie(m_assetId, true);
	else
		m_mainDataSerie = DataSerieManager::Instance().getMinuteDataSerie(m_assetId, si, true);
	
	m_main = parent_main;

    CustomIndicator *indicator = IndicatorManager::Instance().requestIndicator(assetId, si, itPrice, IndicatorCalcParams());

    m_psVisual = new PriceScaleVisual(indicator, this, m_view);
    m_tsVisual = new TimeScaleVisual(indicator, this, m_view);

    m_priceVisual = new PriceVisualIndicator(m_tsVisual, m_psVisual, qobject_cast<PriceIndicator*>(indicator), m_view, this);

	m_scene->addItem(m_tsVisual);
	m_scene->addItem(m_psVisual);
    //m_scene->addItem(m_priceVisual);
	m_baseIndicator = m_priceVisual;

    GraphicTitlebar* title = new GraphicTitlebar(m_priceVisual);
    title->setTitle(assetId.name);
    title->setTimeframe(si);
    IndicatorVisualGroup* group = new IndicatorVisualGroup(m_priceVisual, m_scene, title,m_tsVisual
                                                           ,m_psVisual);
    m_visualGroups.append(group);

    m_studieProperties = new StudieProperties();
    m_studieProperties->setVisible(false);
    connect(m_studieProperties, &StudieProperties::styleChanged,this, &GraphicManager::onStudiePropertiesStyleChanged);

	connect(m_view, &GoTView::Resize, this, &GraphicManager::onViewResize);
	connect(qobject_cast<MainWindow*>(parent_main), &MainWindow::studieSelected, this, &GraphicManager::onMainStudieSelected);
	connect(qobject_cast<MainWindow*>(parent_main), &MainWindow::crossToggles, this, &GraphicManager::onMainCrossToggled);
	connect(m_view, &GoTView::MouseClick, this, &GraphicManager::onViewMouseClick);
	connect(m_view, &GoTView::MouseRelease, this, &GraphicManager::onViewMouseRelease);
	connect(m_view, &GoTView::MouseMove, this, &GraphicManager::onViewMouseMove);
	connect(m_view, &GoTView::KeyPress, this, &GraphicManager::onViewKeyPress);
	connect(qobject_cast<MainWindow*>(parent_main), &MainWindow::handToggles, this, &GraphicManager::onMainHandToggle);
	connect(qobject_cast<MainWindow*>(parent_main), &MainWindow::deleteAllStudies, this, &GraphicManager::onMainDeleteAllStudies);
	connect(qobject_cast<MainWindow*>(parent_main), &MainWindow::randomClose, this, &GraphicManager::onMainRandomClose);

    connectMainIndicators();
}

GraphicManager::~GraphicManager()
{
	delete m_priceVisual;
    delete m_studieProperties;
	m_scene->clear();
}

QWidget* GraphicManager::GetCustomChart()
{
	return m_chart;
}

bool GraphicManager::IsOverVisualItem(IVisualItem** item)
{
    for (auto studie : m_visualItems) {
		if (studie->isOverMouse()) {
            *item = studie;
			return true;
		}
	}
	return false;
}

void GraphicManager::addStudie(QMouseEvent* event)
{
	if (m_mainStudie == stResistance) {
		CustomStudie* studie{ new ResistanceStudie(this, m_psVisual->PriceAtY(event->pos().y()),
												   m_tsVisual, m_psVisual, m_priceVisual)};
        m_visualItems.append(studie);
		studie->setMainColor(qobject_cast<MainWindow*>(m_main)->studieColor());
	}
	else if (m_mainStudie == stLine) {
		CustomStudie* studie{ new LineStudie(this, event->pos().x(), m_psVisual->PriceAtY(event->pos().y()), 
							                 m_tsVisual, m_psVisual, m_priceVisual)};
        m_visualItems.append(studie);
		m_selectedStudie = studie;
		studie->setMainColor(qobject_cast<MainWindow*>(m_main)->studieColor());
		m_bAddingStudie = true;
		m_studieState = ssSettingSecondPoint;
	}
	else if (m_mainStudie == stFibonacci) {
		CustomStudie* studie{ new FibonacciStudie(this, event->pos().x(), 
												  m_psVisual->PriceAtY(event->pos().y()), m_tsVisual, m_psVisual, m_priceVisual) };
        m_visualItems.append(studie);
		m_selectedStudie = studie;
		studie->setMainColor(qobject_cast<MainWindow*>(m_main)->studieColor());
		m_studieState = ssSettingSecondPoint;
		m_bAddingStudie = true;
	}
	else if (m_mainStudie == stVertLine) {
		CustomStudie* studie{ new VertLineStudie(this, event->pos().x(), m_tsVisual, m_psVisual, m_priceVisual) };
        m_visualItems.append(studie);
		studie->setMainColor(qobject_cast<MainWindow*>(m_main)->studieColor());
	}
	else if (m_mainStudie == stChannel) {
		CustomStudie* studie{ new ChannelStudie(this, event->pos().x(), m_psVisual->PriceAtY(event->pos().y()), 
			                                    m_tsVisual, m_psVisual, m_priceVisual) };
        m_visualItems.append(studie);
		m_selectedStudie = studie;
		studie->setMainColor(qobject_cast<MainWindow*>(m_main)->studieColor());
		m_bAddingStudie = true;
		m_studieState = ssSettingSecondPoint;
	}
	else if (m_mainStudie == stFreeHand) {
		CustomStudie* studie{ new FreeHandStudie(this, event->pos(), m_tsVisual, m_psVisual, m_priceVisual) };
        m_visualItems.append(studie);
		m_bAddingStudie = true;
		m_selectedStudie = studie;
		studie->setMainColor(qobject_cast<MainWindow*>(m_main)->studieColor());
		m_studieState = ssAddingPoint;
	}
}

void GraphicManager::fullUpdate()
{
    for (int i{ 0 }; i < m_visualItems.size(); ++i) {
        m_visualItems[i]->changeGeometry();
	}
}

void GraphicManager::handleMouseReleaseStudie()
{
	switch (m_mainStudie) {
	case stChannel: {
		if (m_studieState == ssSettingSecondPoint) {
			m_studieState = ssSettingThirdPoint;
		}
		else if (m_studieState == ssSettingThirdPoint) {
			m_bAddingStudie = false;
			m_selectedStudie = nullptr;

		}
		break;
	}
	default: {
		m_bAddingStudie = false;
		m_selectedStudie = nullptr;
		m_studieState = ssNone;
		break;
	}
	}
}

void GraphicManager::handleMousePressStudie()
{
	if (m_studieState == ssSettingThirdPoint) {
		m_bAddingStudie = false;
		m_selectedStudie = nullptr;
		m_studieState = ssNone;
		return;
	}
}

void GraphicManager::handleMouseMoveStudie(QMouseEvent* event)
{
	if (m_selectedStudie != nullptr) {
		if (m_studieState == ssSettingSecondPoint) {
			m_selectedStudie->setSecondPrice(event->pos());
			return;
		}
		else if (m_studieState == ssSettingThirdPoint) {
			m_selectedStudie->setThirdPrice(event->pos());
			return;
		}
		else if (m_studieState == ssAddingPoint) {
			m_selectedStudie->addPoint(event->pos());
			return;
		}
    }
}

void GraphicManager::connectMainIndicators()
{
    connect(qobject_cast<MainWindow*>(m_main), &MainWindow::addMovingAverage, this, &GraphicManager::onMainAddMovingAverage);
}

void GraphicManager::deleteStudie(IVisualItem* studie)
{
    m_visualItems.removeOne(studie);
	delete studie;
}

void GraphicManager::onViewResize(QResizeEvent* event)
{
	m_psVisual->changeGeometry();
	m_scene->setSceneRect(0, 0, m_view->width(), m_view->height());

    if (m_psVisual)
		m_psVisual->UpdateSpacing();

    if (m_tsVisual)
		m_tsVisual->recalculatePositions();

    for(auto group : m_visualGroups)
        group->changeGeometry();

    for (int i{ 0 }; i < m_visualItems.size(); ++i) {
        m_visualItems[i]->changeGeometry();
	}
}

void GraphicManager::onMainStudieSelected(StudieType studie, bool enabled)
{
	if (enabled) {
		m_mainStudie = studie;
	}
	else
		m_mainStudie = stNoStudie;
}

void GraphicManager::onViewMouseClick(QMouseEvent* event)
{
    IVisualItem *item;
	if (m_bAddingStudie) {
		handleMousePressStudie();
	}
    else if (!IsOverVisualItem(&item)) {
        if ((event->button() == Qt::LeftButton) &&
                (!m_bHandMode) and (m_mainStudie))
        {
			addStudie(event);
		}
		else {
			if (m_bHandMode) {
				m_draggingChart = true;
				m_view->setCursor(Qt::ClosedHandCursor);
			}
			else {
				m_draggingChart = false;
                if (m_viSelected) {
                    m_viSelected->deselect();
                    m_viSelected = nullptr;
                }
			}
		}
	}
	else {
		item->select();

		if (m_viSelected) {
			m_viSelected->deselect();		
		}
		m_viSelected = item;
        if(dynamic_cast<CustomStudie*>(m_viSelected)){
            m_studieProperties->show();
            m_studieProperties->setStyle(dynamic_cast<CustomStudie*>(m_viSelected)->getStyle());
        }
	}
}

void GraphicManager::onViewMouseRelease(QMouseEvent* event)
{
	if (m_bAddingStudie) {
		handleMouseReleaseStudie();
	}
	m_draggingChart = false;
	if (m_bHandMode) {
		m_view->setCursor(Qt::OpenHandCursor);
	}
}

void GraphicManager::onViewMouseMove(QMouseEvent* event)
{
	const int c_yProportion{ 10 };
	if (m_bAddingStudie) {
		handleMouseMoveStudie(event);
	}
    else if ((m_bHandMode) and (m_draggingChart)) {
		m_psVisual->movePrice((event->pos().y() - m_lastChartPos.y()) / c_yProportion);
		m_tsVisual->moveTime((int)(-event->pos().x() + m_lastChartPos.x()));
		fullUpdate();

	}
	m_lastChartPos = event->pos();

    for(auto group : m_visualGroups)
       group->mouseMove(event->pos());

}

void GraphicManager::onViewKeyPress(QKeyEvent* event)
{
	if ((event->key() == Qt::Key_Delete) && (m_viSelected)) {
        m_visualItems.removeOne(m_viSelected);
		deleteStudie(m_viSelected);
		m_viSelected = nullptr;
	}
    else if(event->key() == Qt::Key_Delete){
        CustomVisualIndicator* indicator;
        for(auto group : m_visualGroups){
            if (group->isChildUnderMouse(&indicator)){
                group->removeChild(indicator);
                delete indicator;
                break;
            }
        }
    }

}

void GraphicManager::onMainCrossToggled(bool enabled)
{
	m_priceVisual->toggleCross();
	if (enabled) {
		m_view->setCursor(Qt::BlankCursor);
	}
	else {
		m_view->setCursor(Qt::ArrowCursor);
	}
}

void GraphicManager::onMainHandToggle(bool enabled)
{
	m_bHandMode = not m_bHandMode;
	if (enabled) {
		m_view->setCursor(Qt::OpenHandCursor);
	}
	else {
		m_view->setCursor(Qt::ArrowCursor);
	}
}

void GraphicManager::onMainDeleteAllStudies()
{
	if (dynamic_cast<CustomStudie*>(m_viSelected)) m_viSelected = nullptr;

    for (long long i{ m_visualItems.size() - 1 }; i >= 0; --i) {
        delete dynamic_cast<CustomStudie*>(m_visualItems[i]);
        m_visualItems.pop_back();
	}

}

void GraphicManager::onMainRandomClose(bool b)
{
    //m_priceVisual->toggleRandomClose(b);
}

void GraphicManager::onStudiePropertiesStyleChanged()
{
    if (m_viSelected){
        if (dynamic_cast<CustomStudie*>(m_viSelected)){
            dynamic_cast<CustomStudie*>(m_viSelected)->setStyle(m_studieProperties->getStyle());
        }
    }
}

void GraphicManager::onMainAddMovingAverage(BasicIndicatorStyle style, IndicatorCalcOver calcOver, int interval, int shift, MovingAverageType type)
{
    IndicatorCalcParams lst;
    IndicatorParam a{interval},b{type},c{calcOver},d{shift};
    lst << a << b << c << d;

    CustomIndicator* indicator = IndicatorManager::Instance().requestIndicator(m_assetId, m_sInterval, itMovingAverage, lst);

    IndicatorVisualParams params;
    BasicIndicatorStyle* pstyle = new BasicIndicatorStyle(style);
    params.append(pstyle);


    IndicatorVisualGroup* group = m_visualGroups[0];
    group->addChild(new MovingAverageVisual(params, m_tsVisual, m_psVisual, qobject_cast<MovingAverage*>(indicator), m_view, this));
}
