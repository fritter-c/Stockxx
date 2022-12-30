#ifndef GRAPHICMANAGER_H
#define GRAPHICMANAGER_H

#include "customstudie.h"
#include "customdataserie.h"
#include "graphictitlebar.h"
#include "pricescalevisual.h"
#include <QObject>
#include "gotview.h"
#include "studieproperties.h"
#include "timescalevisual.h"
#include "StockxxDataTypes.h"
#include "indicators/visuals/pricevisualindicator.h"

enum StudieState  {ssSettingSecondPoint,
                  ssSettingThirdPoint,
                  ssDragging,
                  ssAddingPoint,
                  ssNone};
class IndicatorVisualGroup{
private:
    QVector<CustomVisualIndicator*> m_children;
    CustomVisualIndicator* m_father;
    QGraphicsScene* m_scene;
    GraphicTitlebar* m_titlebar;
    TimeScaleVisual* m_timeScale;
    PriceScaleVisual* m_priceScale;
    QRectF m_groupArea;
public:
    IndicatorVisualGroup(CustomVisualIndicator* father, QGraphicsScene* scene,
                         GraphicTitlebar* titlebar,
                         TimeScaleVisual* timescale,
                         PriceScaleVisual* pricescale){
        m_father = father;
        m_scene = scene;
        m_titlebar = titlebar;
        m_timeScale = timescale;
        m_priceScale = pricescale;
        m_scene->addItem(father);
    }
    inline void addChild(CustomVisualIndicator* child){
        m_scene->addItem(child);
        m_children.append(child);
    }
    inline void removeChild(CustomVisualIndicator* child){
        m_scene->removeItem(child);
        m_children.removeOne(child);
    }
    inline void changeGeometry(){
        m_father->changeGeometry();
        for(auto child : m_children){
            child->changeGeometry();
        }
    }
    inline bool isUnderMouse(CustomVisualIndicator** visual){
        if (m_father->isUnderMouse()){
            *visual = m_father;
            return true;
        }
        for(auto child : m_children){
            if (child->isUnderMouse()){
                *visual = child;
                return true;
            }
        }
        *visual = nullptr;
        return false;
    }
    inline bool isChildUnderMouse(CustomVisualIndicator** visual){
        for(auto child : m_children){
            if (child->isUnderMouse()){
                *visual = child;
                return true;
            }
        }
        *visual = nullptr;
        return false;
    }
    inline void mouseMove(const QPointF& p){
        if (m_father->isUnderMouse()){
            m_father->setBHighlight(true);
        }
        else{
            m_father->setBHighlight(false);
        }
        for(auto child : m_children){
            if (child->isUnderMouse()){
                child->setBHighlight(true);
            }
            else{
                child->setBHighlight(false);
            }
        }
        if (dynamic_cast<PriceVisualIndicator*>(m_father)){
            m_titlebar->setCandle(dynamic_cast<PriceVisualIndicator*>(m_father)->getCandle(m_timeScale->findNearestDate(p.x())));
        }

    }
    inline bool isOver(const QPointF& p){
        return m_groupArea.contains(p);
    }

};

class GraphicManager : public QObject
{
    Q_OBJECT
private:
    QWidget *m_chart;
    GoTView *m_view;
    QGraphicsScene *m_scene;
    PriceScaleVisual *m_psVisual;
    TimeScaleVisual  *m_tsVisual;
    AssetId m_assetId;
    CustomDataSerie *m_mainDataSerie;
    CustomVisualIndicator *m_baseIndicator;
    PriceVisualIndicator *m_priceVisual;
    QVector<IVisualItem*> m_visualItems;
    QVector<IndicatorVisualGroup*> m_visualGroups;
    StudieType m_mainStudie;
    StudieProperties* m_studieProperties{nullptr};
    CustomStudie* m_selectedStudie{nullptr};
    StudieState m_studieState{ssNone};
    IVisualItem* m_viSelected{nullptr};
    QPointF m_lastChartPos{0,0};
    SerieInterval m_sInterval;
    QWidget* m_main;
    QVector<QRect> m_boundingAreas;
    QRect m_timescaleBoundingArea;
    QRect m_baseIndicatorBoundingArea;
    bool m_bHandMode{false};
    bool m_draggingChart{false};
    bool m_bAddingStudie{false};
    bool IsOverVisualItem(IVisualItem **);
    void addStudie(QMouseEvent* event);
    void fullUpdate();
    void handleMouseReleaseStudie();
    void handleMousePressStudie();
    void handleMouseMoveStudie(QMouseEvent *event);
    void connectMainIndicators();
public:
    explicit GraphicManager(AssetId assetId, SerieInterval si, GoTView *m_view, QWidget *parent_main = nullptr, QWidget *chart = nullptr);
    ~GraphicManager();
    QWidget* GetCustomChart();
    void deleteStudie(IVisualItem*);

public slots:
    void onViewResize(QResizeEvent *event);
    void onMainStudieSelected(StudieType, bool);
    void onViewMouseClick(QMouseEvent* event);
    void onViewMouseRelease(QMouseEvent* event);
    void onViewMouseMove(QMouseEvent* event);
    void onViewKeyPress(QKeyEvent* event);
    void onMainCrossToggled(bool);
    void onMainHandToggle(bool);
    void onMainDeleteAllStudies();
    void onMainRandomClose(bool);
    void onStudiePropertiesStyleChanged();

    // indicators
    void onMainAddMovingAverage(BasicIndicatorStyle, IndicatorCalcOver, int interval, int shift, MovingAverageType);
    void onMainAddBollingerBands(BasicIndicatorStyle, IndicatorCalcOver, int interval, int shift, MovingAverageType, double);
};
#endif // GRAPHICMANAGER_H
