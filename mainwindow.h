#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graphicmanager.h"
#include "customchart.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    void syncButtons();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void studieSelected(StudieType, bool);
    void crossToggles(bool);
    void handToggles(bool);
    void deleteAllStudies();
private slots:
    void on_actionResistance_Studie_toggled(bool arg1);
    void on_actionLine_Studie_toggled(bool arg1);
    void on_actionCursor_toggled(bool arg1);
    void on_actionCross_toggled(bool arg1);
    void on_actionHand_Mouse_toggled(bool arg1);
    void on_actionDelete_All_triggered();
    void on_actionFibonacci_Studie_toggled(bool arg1);
    void on_actionVerticalLine_Studie_toggled(bool arg1);
    void on_actionChannel_Studie_toggled(bool arg1);
    void on_actionFreeHand_Studie_toggled(bool arg1);
    void on_actionSearch_Ticker_triggered();

    void on_actionClose_triggered();

    void on_actionNew_Chart_triggered();

private:
    Ui::MainWindow *ui;
    QList<QWidget*> m_forms;
    QList<GraphicManager*> m_managers;
};
#endif // MAINWINDOW_H
