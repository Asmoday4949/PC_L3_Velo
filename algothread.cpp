#include "algothread.h"
#include "maintenance.h"
#include "habitant.h"

AlgoThread* AlgoThread::algoThread = nullptr;

AlgoThread::AlgoThread(CityWidget* mainWindow,int _nbSite,int _nbHabitants,int _nbBorne,int _nbVelo)
{
    AlgoThread::algoThread = this;

    nbSite = _nbSite;
    nbHabitants = _nbHabitants;
    nbBorne = _nbBorne;
    nbVelo = _nbVelo;

    connect(this,SIGNAL(initSite(int,int)),mainWindow,SLOT(initSite(int,int)));
    connect(this,SIGNAL(initHabitant(int,int)),mainWindow,SLOT(initHabitant(int,int)));

    connect(this,SIGNAL(setHabitantState(int,int)),mainWindow,SLOT(setHabitantState(int,int)));
    connect(this,SIGNAL(setSiteVelo(int,int)),mainWindow,SLOT(setSiteVelo(int,int)));
    connect(this,SIGNAL(startDeplacement(int,int,int,int)),mainWindow,SLOT(startDeplacement(int,int,int,int)));

    connect(this,SIGNAL(setDepotVelo(int)),mainWindow,SLOT(setDepotVelo(int)));
    connect(this,SIGNAL(setCamVelo(int)),mainWindow,SLOT(setCamVelo(int)));
    connect(this,SIGNAL(startCamionDeplacement(int,int,int)),mainWindow,SLOT(startCamionDeplacement(int,int,int)));
}

AlgoThread::~AlgoThread()
{
    for(int i = 0; i < this->nbHabitants+1; i++)
    {
        delete this->arrThreads[i];
    }
    delete this->arrThreads;
}

AlgoThread *AlgoThread::getAlgoThread()
{
    return algoThread;
}

void AlgoThread::setVeloPerBorne(int velos)
{
    for(int i = 0; i < this->nbSite; i++)
    {
        emit setSiteVelo(i, velos);
    }
}

void AlgoThread::setVelosAtDepot(int velos)
{
    emit setDepotVelo(velos);
}

void AlgoThread::run()
{
    this->setVeloPerBorne(this->nbBorne-2);
    this->setVelosAtDepot(this->nbVelo - (this->nbBorne-2)*this->nbSite);

    this->arrThreads = new QThread*[this->nbHabitants+1];
    this->createThreads();
    this->startThreads();
    this->waitThreads();
}

void AlgoThread::createThreads()
{
    // create maintenance thread at the last position of the threads array
    this->arrThreads[this->nbHabitants] = new Maintenance();

    // create habitant threads
    for(int i = 0; i < nbHabitants; i++)
    {
        this->arrThreads[i] = new Habitant();
    }
}

void AlgoThread::startThreads()
{
    for(int i = 0; i < nbHabitants+1; i++)
    {
        this->arrThreads[i]->start();
    }
}

void AlgoThread::waitThreads()
{
    for(int i = 0; i < nbHabitants+1; i++)
    {
        this->arrThreads[i]->wait();
    }
}
