#pragma once

#include <QMutex>
#include <QWaitCondition>
#include <QThread>
#include <QDebug>
#include <QQueue>

#include "citywidget.h"
#include "paramlist.h"

using namespace std;

struct Borne
{
    QWaitCondition condition;
    QMutex mutex;
    QQueue<int> dropVeloQueue;
    QQueue<int> takeVeloQueue;
};

class AlgoThread : public QThread
{
    Q_OBJECT
public:
    AlgoThread(CityWidget* mainWindow,int nbSite,int nbHabitants,int nbBorne,int nbVelo);
    virtual ~AlgoThread();


    //getters
    int getNbSite() { return this->nbSite; }
    int getNbHabitants() { return this->nbHabitants; }
    int getNbBorne() { return this->nbBorne; }
    int getNbVelo() { return this->nbVelo; }
    int* getNbVelosAtBorne() { return this->nbVelosAtBorne; }
    int getNbVelosAtDepot() { return this->nbVelosAtDepot; }

    //setters
    void setNbVelosAtDepot(int velos) { this->nbVelosAtDepot = velos; }

    //static getters
    static AlgoThread *getAlgoThread();
    static int getRandomTripTime();
    static int getRandomValue(int max);
    static const int waitingTime = 3; //time of the pause in second

protected:
    //logic function
    void setVeloPerBorne(int velos);
    void setVelosAtDepot(int velos);
    //threads related funcitons
    void run();
    void createThreads();
    void startThreads();
    void waitThreads();

    //members
    int nbSite;
    int nbHabitants;
    int nbBorne;
    int nbVelo;
    int* nbVelosAtBorne;
    int nbVelosAtDepot;

    //array to store all threads to start/wait/destroy them with a loop,
    //they are independant after starting so not useful to know which one is what
    QThread** arrThreads;

    //static members
    static AlgoThread* algoThread;
signals:
     void initSite(int siteId,int nbVelo);
     void initHabitant(int habId,int initSiteId);
     void initCamion();

     void setHabitantState(int habId,int param);
     void setSiteVelo(int idSite,int nbVelo);
     void startDeplacement(int habId,int initSite,int destSite,int parcourTime);

     void setDepotVelo(int nbVeloDep);
     void setCamVelo(int nbVeloCam);
     void startCamionDeplacement(int initSite,int destSite,int parcourTime);
};
