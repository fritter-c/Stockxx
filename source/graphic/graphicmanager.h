#ifndef GRAPHICMANAGER_H
#define GRAPHICMANAGER_H

#include "customstudie.h"
#include "customdataserie.h"
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
    QVector<QGraphicsItem*> m_visualGraphicItems;
    QVector<IVisualItem*> m_visualItems;
    QGraphicsItem* m_candleMag;
    StudieType m_mainStudie;
    StudieProperties* m_studieProperties{nullptr};
    CustomStudie* m_selectedStudie{nullptr};
    StudieState m_studieState{ssNone};
    IVisualItem* m_viSelected{nullptr};
    QPointF m_lastChartPos{0,0};
    SerieInterval m_sInterval;
    QWidget* m_main;
    bool m_bHandMode{false};
    bool m_draggingChart{false};
    bool m_bAddingStudie{false};
    bool IsOverVisualItem(IVisualItem **);
    void addStudie(QMouseEvent* event);
    void fullUpdate();
    void handleMouseReleaseStudie();
    void handleMousePressStudie();
    void handleMouseMoveStudie(QMouseEvent *event);
public:
    explicit GraphicManager(AssetId assetId, SerieInterval si, GoTView *m_view, QWidget *parent_main = nullptr, QWidget *chart = nullptr);
    ~GraphicManager();
    QWidget* GetCustomChart();
    void candleHoveredChanged();
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
};
#endif // GRAPHICMANAGER_H
