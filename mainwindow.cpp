#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMdiSubWindow>
#include "QActionGroup"
#include "customchart.h"
#include "dataseriemanager.h"
#include "symbolsearcher.h"

void MainWindow::syncButtons()
{

}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    AssetId id {"IBM"};
    m_forms.append(new CustomChart(id,this, ui->mdiArea));
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

}

MainWindow::~MainWindow()
{
    delete ui;
    foreach(QWidget *form, m_forms){
        delete form;
    }
    m_forms.clear();
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

void MainWindow::on_actionSearch_Ticker_triggered()
{
    SymbolSearcher symbolSearcher;
    symbolSearcher.exec();
    if (symbolSearcher.result() == QDialog::Accepted){
        DataSerieManager::Instance().requestDailySerie(symbolSearcher.getTicker());
    }
}


void MainWindow::on_actionClose_triggered()
{
    close();
}


void MainWindow::on_actionNew_Chart_triggered()
{
    SymbolSearcher symbolSearcher{this, true};
    symbolSearcher.exec();
    if (symbolSearcher.result() == QDialog::Accepted){
        AssetId id;
        id.name = symbolSearcher.getTicker();
        CustomChart *chart;
        if(!symbolSearcher.getFreeWindow()){
            chart = new CustomChart(id,this, ui->mdiArea);
            ui->mdiArea->addSubWindow(chart);
        }
        else{
            chart = new CustomChart(id,this, parentWidget());
        }
        m_forms.append(chart);
        chart->show();
        syncButtons();
    }
}

