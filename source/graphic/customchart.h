#ifndef CUSTOMCHART_H
#define CUSTOMCHART_H

#include <QWidget>
#include <QGraphicsView>
#include "gotview.h"
#include "graphicmanager.h"
#include "StockxxDataTypes.h"

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
    Ui::CustomChart *ui;
public:
    CustomChart(AssetId assetid,SerieInterval si, QWidget *parent_main, QWidget *parent = nullptr);
    ~CustomChart();
    GoTView* GetGraphicsView();
    GraphicManager *gManager() const;
};
#endif // CUSTOMCHART_H
