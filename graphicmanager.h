#ifndef GRAPHICMANAGER_H
#define GRAPHICMANAGER_H

#include "customstudie.h"
#include "indicatorvisual.h"
#include "pricescalevisual.h"
#include <QObject>
#include <customchart.h>
#include "gotview.h"
#include "pricevisual.h"
#include "timescalevisual.h"
#include <dailydataserie.h>

enum StudieType {stNoStudie, stLine, stResistance, stDragging};

class GraphicManager : public QObject
{
    Q_OBJECT
private:
    CustomChart *m_chart;
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

    void addStudie(QMouseEvent* event);
public:
    explicit GraphicManager(QObject *parent = nullptr, CustomChart *chart = nullptr);
    CustomChart* GetCustomChart();
    void candleHoveredChanged();

public slots:
    void onViewResize(QResizeEvent *event);
    void onMainStudieSelected(StudieType, bool);
    void onViewMouseClick(QMouseEvent* event);
    void onViewMouseRelease(QMouseEvent* event);
    void onViewMouseMove(QMouseEvent* event);
    void onViewKeyPress(QKeyEvent* event);
    void onMainCrossToggled(bool);

};

#endif // GRAPHICMANAGER_H
