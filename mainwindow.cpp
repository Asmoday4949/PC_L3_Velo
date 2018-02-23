#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    this->mainLayout = new QStackedLayout(this);

    this->initWidget = new InitWidget();
    this->initWidget->resize(this->size());

    this->mainLayout->addWidget(initWidget);

    connect(this->initWidget, &InitWidget::FormSubmitted, this, &MainWindow::loadCity);
}

void MainWindow::loadCity()
{
    int nbSite = this->initWidget->getSites();
    int nbHabitants = this->initWidget->getHabitants();
    int nbBorne = this->initWidget->getBornesSite();
    int nbVelo = this->initWidget->getVelos();

    CityWidget* cityWidget = new CityWidget(nbSite,nbHabitants,nbBorne,nbVelo);
    this->mainLayout->addWidget(cityWidget);
    this->mainLayout->setCurrentIndex(1);

    AlgoThread* algoThread = new AlgoThread(cityWidget,nbSite,nbHabitants,nbBorne,nbVelo);
    algoThread->start();
}
