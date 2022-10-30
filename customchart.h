#ifndef CUSTOMCHART_H
#define CUSTOMCHART_H

#include <QWidget>
#include <QGraphicsView>
#include "gotview.h"

namespace Ui {
class CustomChart;
}

class CustomChart : public QWidget
{
    Q_OBJECT
private:
    GoTView* m_view;
public:
    CustomChart(QWidget *parent = nullptr);
    ~CustomChart();
    GoTView* GetGraphicsView();

private:
    Ui::CustomChart *ui;
};

#endif // CUSTOMCHART_H
