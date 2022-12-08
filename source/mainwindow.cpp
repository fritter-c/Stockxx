#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMdiSubWindow>
#include "QActionGroup"
#include "customchart.h"
#include "dataseriemanager.h"
#include "symbolsearcher.h"
#include <QColorDialog>

void MainWindow::syncButtons()
{

}

const QColor &MainWindow::studieColor() const
{
    return m_studieColor;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setWindowIcon(QIcon(":/imgs/imgs/Main.png"));
    ui->setupUi(this);
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
    m_btnStudieColor = new QPushButton();
    m_btnStudieColor->setMinimumSize(20, 20);
    m_btnStudieColor->setMaximumSize(30, 30);
    m_studieColor = Qt::yellow;
    m_btnStudieColor->setAutoFillBackground(true);
    m_btnStudieColor->setStyleSheet("background-color: yellow;");
    m_btnStudieColor->update();
    m_btnStudieColor->setGeometry(0,0, 30,30);
    connect(m_btnStudieColor, &QPushButton::clicked, this,  &MainWindow::on_btnStudieColor_clicked);
    ui->toolBar->addWidget(m_btnStudieColor);

#ifdef QT_DEBUG
    ui->menuTests->menuAction()->setVisible(true);
#else
    ui->menuTests->menuAction()->setVisible(false);
#endif
}

MainWindow::~MainWindow()
{
    delete ui;
    foreach(QWidget *form, m_forms){
        delete form;
    }
    m_forms.clear();
    delete m_btnStudieColor;
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
           connect(&DataSerieManager::Instance(), &DataSerieManager::graphReady,
                   this, &MainWindow::onDataManagerGraphReady);
           connect(&DataSerieManager::Instance(), &DataSerieManager::notifyMain,
                   this, &MainWindow::onSerieLoadStep);
           m_progressBar.setVisible(true);
           m_progressBar.setValue(0);
        }
    }
    m_bCreateFreeWindow = symbolSearcher.getFreeWindow();
}


void MainWindow::on_actionClose_triggered()
{
    close();
}


void MainWindow::on_actionNew_Chart_triggered()
{
    emit ui->actionSearch_Ticker->triggered();
}


void MainWindow::on_actionOpen_100_Charts_triggered()
{
    for (int i{0}; i < 100; ++i){
        AssetId id;
        id.name = "IBM";
        CustomChart *chart;
        chart = new CustomChart(id,siDaily,this, ui->mdiArea);
        m_forms.append(chart);
        ui->mdiArea->addSubWindow(chart);
        chart->show();
    }
    ui->mdiArea->cascadeSubWindows();
}


void MainWindow::on_actionClose_All_Charts_triggered()
{
    for(long long i{m_forms.size() - 1}; 0 <= i; --i){
        m_forms.pop_back();
    }
    ui->mdiArea->closeAllSubWindows();
}

void MainWindow::onCustomChartDestroy(QObject * sender)
{
    for(long long i{m_forms.size() - 1}; 0 <= i; --i){
        if (m_forms[i] == (QWidget*)sender) {
            m_forms.removeAt(i);
        }
    }
}

void MainWindow::onDataManagerGraphReady(DataSerieIdentifier id)
{
    m_progressBar.setValue(100);
    CustomChart *chart;
    QMdiSubWindow *mdiWindow;
    if (!m_bCreateFreeWindow){
       chart = new CustomChart(id.id,id.si,this, this);
       chart->setAttribute(Qt::WA_DeleteOnClose);
       chart->setWindowTitle(id.id.name);
       mdiWindow = ui->mdiArea->addSubWindow(chart);
       mdiWindow->setWindowIcon(QIcon(":/imgs/imgs/NewChart.png"));
       mdiWindow->setGeometry(0,0,400,400);
    }
    else{
        chart = new CustomChart(id.id,id.si,this, parentWidget());
        chart->setWindowIcon(QIcon(":/imgs/imgs/NewChart.png"));
        chart->setAttribute(Qt::WA_DeleteOnClose);
        chart->setWindowTitle(id.id.name);


    }
    m_forms.append(chart);
    m_bCreateFreeWindow = false;
    connect(chart, SIGNAL(destroyed(QObject*)), this, SLOT(onCustomChartDestroy(QObject*)));
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


void MainWindow::on_actionsideAdjust_triggered()
{
    ui->mdiArea->tileSubWindows();
}


void MainWindow::on_actionRelease_MDI_Windows_triggered()
{

}

void MainWindow::on_actionRandom_Close_triggered(bool checked)
{
    emit randomClose(checked);
}

void MainWindow::on_btnStudieColor_clicked(bool)
{
    QColorDialog colordial;

    colordial.exec();
    if (colordial.result() == QDialog::Accepted){
        QColor col{ colordial.selectedColor() };
        m_studieColor = col;
        QString qss = QString("background-color: %1").arg(col.name());
        m_btnStudieColor->setStyleSheet(qss);
        m_btnStudieColor->update();
    }
}

