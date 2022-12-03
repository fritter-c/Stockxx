#include "calcdaemon.h"
#include "dataseriemanager.h"
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

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QThread::currentThread()->setObjectName("Main");
    QThread::currentThread()->setPriority(QThread::HighestPriority);
    createDataSerieManager();
    createCalcDaemon();
    CalcDaemon::Instance().start();
    MainWindow w;
    w.show();
    return a.exec();
}
