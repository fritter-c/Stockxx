#ifndef CUSTOMCHART_H
#define CUSTOMCHART_H

#include <QWidget>
#include <QGraphicsView>
#include "gotview.h"
#include "graphicmanager.h"

namespace Ui {
class CustomChart;
}

class CustomChart : public QWidget
{
    Q_OBJECT
private:
    GoTView* m_view;
    GraphicManager* m_gManager;
    AssetId m_assetId;
public:
    CustomChart(AssetId assetid, QWidget *parent_main, QWidget *parent = nullptr);
    ~CustomChart();
    GoTView* GetGraphicsView();

private:
    Ui::CustomChart *ui;
};

#endif // CUSTOMCHART_H
