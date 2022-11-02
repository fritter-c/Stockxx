#ifndef GRAPHICMANAGER_H
#define GRAPHICMANAGER_H

#include "customstudie.h"
#include "indicatorvisual.h"
#include "pricescalevisual.h"
#include <QObject>
#include "gotview.h"
#include "pricevisual.h"
#include "timescalevisual.h"
#include <dailydataserie.h>

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
    DailyDataSerie *m_dailyDataSerie;
    IndicatorVisual *m_baseIndicator;
    PriceVisual *m_priceVisual;
    QVector<QGraphicsItem*> m_visualItems;
    QVector<CustomStudie*> m_visualStudies;
    QGraphicsItem* m_candleMag;
    StudieType m_mainStudie;
    CustomStudie* m_draggingStudie{nullptr};
    CustomStudie* m_selectedStudie{nullptr};
    QPointF m_lastChartPos{0,0};
    bool m_bHandMode{false};
    bool m_draggingChart{false};
    bool m_bAddingStudie{false};

    void addStudie(QMouseEvent* event);
    void fullUpdate();
public:
    explicit GraphicManager(GoTView *m_view, QObject *parent = nullptr, QWidget *chart = nullptr);
    QWidget* GetCustomChart();
    void candleHoveredChanged();

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

};

#endif // GRAPHICMANAGER_H
