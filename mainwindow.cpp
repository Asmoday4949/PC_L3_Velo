#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    this->mainLayout = new QStackedLayout(this);

    this->initWidget = new InitWidget();
    this->initWidget->resize(this->size());

    this->mainLayout->addWidget(initWidget);

    int nbSite=5;
    int nbHabitants=15;
    int nbBorne=5;
    int nbVelo=30;


}

MainWindow::loadCity()
{
    CityWidget* cityWidget = new CityWidget(nbSite,nbHabitants,nbBorne,nbVelo);
    cityWidget->resize(800,600);

    AlgoThread* algoThread = new AlgoThread(cityWidget,nbSite,nbHabitants,nbBorne,nbVelo);
    algoThread->start();
}
