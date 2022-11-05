#include "dataseriemanager.h"
#include "mainwindow.h"
#include <QApplication>


void createDataSerieManager(){
    new DataSerieManager();
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QThread::currentThread()->setObjectName("Main");
    QThread::currentThread()->setPriority(QThread::HighestPriority);
    createDataSerieManager();
    MainWindow w;
    w.show();
    return a.exec();
}
