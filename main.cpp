#include "calcdaemon.h"
#include "dataseriemanager.h"
#include "indicatormanager.h"
#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QStyleFactory>


void createDataSerieManager(){
    new DataSerieManager();
}
void createCalcDaemon(){
    new CalcDaemon();
}
void createIndicatorManager(){
    new IndicatorManager();
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QThread::currentThread()->setObjectName("Main");
    QThread::currentThread()->setPriority(QThread::HighestPriority);
    createDataSerieManager();
    createCalcDaemon();
    createIndicatorManager();
    CalcDaemon::Instance().start();
    MainWindow w;
    w.show();
    return a.exec();
}
