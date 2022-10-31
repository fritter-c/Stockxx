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
    m_managers.append(new GraphicManager(this, new CustomChart(this)));
    m_forms.append(m_managers[0]->GetCustomChart());  
    ui->mdiArea->addSubWindow(m_forms[0]);
    ui->mdiArea->currentSubWindow()->resize(QSize(500,500));
    QActionGroup* studieActionGroup = new QActionGroup(this);
    QActionGroup* mouseMode = new QActionGroup(this);
    studieActionGroup->addAction(ui->actionCursor);
    studieActionGroup->addAction(ui->actionLine_Studie);
    studieActionGroup->addAction(ui->actionResistance_Studie);
    mouseMode->addAction(ui->actionCross);
    mouseMode->addAction(ui->actionHand_Mouse);

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

