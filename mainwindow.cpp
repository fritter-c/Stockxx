#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "customchart.h"
#include <QMdiSubWindow>
#include "QActionGroup"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    AssetId id {"IBM"};
    m_forms.append(new CustomChart(id,this));
    ui->mdiArea->addSubWindow(m_forms[0]);
    ui->mdiArea->currentSubWindow()->resize(QSize(500,500));
    QActionGroup* studieActionGroup = new QActionGroup(this);
    studieActionGroup->addAction(ui->actionCursor);
    studieActionGroup->addAction(ui->actionLine_Studie);
    studieActionGroup->addAction(ui->actionResistance_Studie);
    studieActionGroup->addAction(ui->actionFibonacci_Studie);
    studieActionGroup->addAction(ui->actionCross);
    studieActionGroup->addAction(ui->actionHand_Mouse);
    studieActionGroup->addAction(ui->actionVerticalLine_Studie);
    studieActionGroup->addAction(ui->actionChannel_Studie);
    studieActionGroup->addAction(ui->actionFreeHand_Studie);

#ifdef QT_DEBUG
    ui->menuTests->setVisible(false);
#endif
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionResistance_Studie_toggled(bool arg1)
{
    emit studieSelected(stResistance, arg1);
}


void MainWindow::on_actionLine_Studie_toggled(bool arg1)
{
    emit studieSelected(stLine, arg1);
}


void MainWindow::on_actionCursor_toggled(bool arg1)
{
    emit studieSelected(stNoStudie, arg1);
}


void MainWindow::on_actionCross_toggled(bool arg1)
{
    emit crossToggles(arg1);
}


void MainWindow::on_actionHand_Mouse_toggled(bool arg1)
{
    emit handToggles(arg1);
}


void MainWindow::on_actionDelete_All_triggered()
{
    emit deleteAllStudies();
}


void MainWindow::on_actionFibonacci_Studie_toggled(bool arg1)
{
    emit studieSelected(stFibonacci, arg1);
}


void MainWindow::on_actionVerticalLine_Studie_toggled(bool arg1)
{
    emit studieSelected(stVertLine, arg1);
}

void MainWindow::on_actionChannel_Studie_toggled(bool arg1)
{
    emit studieSelected(stChannel, arg1);
}


void MainWindow::on_actionFreeHand_Studie_toggled(bool arg1)
{
    emit studieSelected(stFreeHand, arg1);
}


void MainWindow::on_actionAlphaVantage_Get_Daily_triggered()
{

}

