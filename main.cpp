#include "mainwindow.h"
#include <QApplication>

#include "algothread.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    int nbSite=5;
    int nbHabitants=15;
    int nbBorne=5;
    int nbVelo=30;

    MainWindow* mainWindow = new MainWindow(nbSite,nbHabitants,nbBorne,nbVelo);
    mainWindow->show();

    AlgoThread* algoThread = new AlgoThread(mainWindow,nbSite,nbHabitants,nbBorne,nbVelo);
    algoThread->start();

    return a.exec();

}
