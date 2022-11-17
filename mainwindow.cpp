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
    connect(m_forms[0], SIGNAL(destroyed(QObject*)), this, SLOT(onCustomChartDestroy(QObject*)));
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
    m_progressBar.setMaximum(100);
    m_progressBar.setMinimum(0);
    ui->statusbar->addPermanentWidget(&m_progressBar);
    m_progressBar.setVisible(false);
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
        if(symbolSearcher.getInterval() == siDaily){
            DataSerieManager::Instance().requestDailySerie(symbolSearcher.getTicker());
            connect(&DataSerieManager::Instance(), &DataSerieManager::graphReady,
                    this, &MainWindow::onDataManagerGraphReady);
            connect(&DataSerieManager::Instance(), &DataSerieManager::notifyMain,
                    this, &MainWindow::onSerieLoadStep);
            m_progressBar.setVisible(true);
            m_progressBar.setValue(0);
        }
        else{
           DataSerieManager::Instance().requestMinuteSerie(symbolSearcher.getTicker(), symbolSearcher.getInterval());
        }
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
            connect(chart, SIGNAL(destroyed(QObject*)), this, SLOT(onCustomChartDestroy(QObject*)));
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


void MainWindow::on_actionOpen_100_Charts_triggered()
{
    for (int i{0}; i < 100; ++i){
        AssetId id;
        id.name = "IBM";
        CustomChart *chart;
        chart = new CustomChart(id,this, ui->mdiArea);
        m_forms.append(chart);
        ui->mdiArea->addSubWindow(chart);
        chart->show();
    }
    ui->mdiArea->cascadeSubWindows();
}


void MainWindow::on_actionClose_All_Charts_triggered()
{
    for(qsizetype i{m_forms.size() - 1}; 0 <= i; --i){
        m_forms.pop_back();
    }
    ui->mdiArea->closeAllSubWindows();
}

void MainWindow::onCustomChartDestroy(QObject * sender)
{
    ui->mdiArea->removeSubWindow((QWidget*)sender);
    for(qsizetype i{m_forms.size() - 1}; 0 <= i; --i){
        if (m_forms[i] == (QWidget*)sender) {
            m_forms.removeAt(i);
        }
    }
}

void MainWindow::onDataManagerGraphReady(AssetId id)
{
    m_progressBar.setValue(100);
    CustomChart *chart = new CustomChart(id,this, ui->mdiArea);
    connect(chart, SIGNAL(destroyed(QObject*)), this, SLOT(onCustomChartDestroy(QObject*)));
    ui->mdiArea->addSubWindow(chart);
    m_forms.append(chart);
    chart->show();
    disconnect(&DataSerieManager::Instance(), &DataSerieManager::graphReady,
               this, &MainWindow::onDataManagerGraphReady);
    disconnect(&DataSerieManager::Instance(), &DataSerieManager::notifyMain,
            this, &MainWindow::onSerieLoadStep);
    if (!m_progressBarHide){
        m_progressBarHide = new QTimer(this);
        m_progressBarHide->setInterval(2000);
        connect(m_progressBarHide, &QTimer::timeout,this, &MainWindow::onHideProgressBar);
        m_progressBarHide->start();
    }
}

void MainWindow::onSerieLoadStep()
{
    m_progressBar.setValue(m_progressBar.value() + 33);
}

void MainWindow::onHideProgressBar()
{
    m_progressBarHide->stop();
    m_progressBar.setVisible(false);
    delete m_progressBarHide;
    m_progressBarHide = nullptr;
}

