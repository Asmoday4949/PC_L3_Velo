#pragma once

#include <QMutex>
#include <QWaitCondition>
#include <QThread>
#include <QDebug>
#include <QQueue>

#include "citywidget.h"
#include "paramlist.h"

using namespace std;

struct Site
{
    Site(int id) : velosAtSite(0), conditionArrive(), conditionLeave(), mutex(), dropVeloQueue(), takeVeloQueue()
    {
        this->id = id;
    }

    int id;
    int velosAtSite;
    QWaitCondition conditionArrive;
    QWaitCondition conditionLeave;
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

    //debug
    void threadSafeQDebug(QString text);

    //getters
    int getNbSite() { return this->nbSite; }
    int getNbHabitants() { return this->nbHabitants; }
    int getNbBorne() { return this->nbBorne; }
    int getNbVelo() { return this->nbVelo; }
    Site** getSites() { return this->arrSites; }
    int getNbVelosAtDepot() { return this->nbVelosAtDepot; }
    void addVelosAtSite(int nbVelos, Site* site);

    //setters
    void setNbVelosAtDepot(int velos) { this->nbVelosAtDepot = velos; }

    //static getters
    static AlgoThread *getAlgoThread();
    static int getRandomTripTime();
    static int getRandomValue(int max);
    static const int waitingTime = 3; //time of the pause in second

protected:
    //logic function
    void setVelosPerSite(int velos);
    void setVelosAtDepot(int velos);

    //threads related funcitons
    void run();
    void createThreads();
    void startThreads();
    void waitThreads();
    void initSites();

    //members
    int nbSite;
    int nbHabitants;
    int nbBorne;
    int nbVelo;
    Site** arrSites;
    int nbVelosAtDepot;

    //array to store all threads to start/wait/destroy them with a loop,
    //they are independant after starting so not useful to know which one is what
    QThread** arrThreads;

    //qdebug tools
    bool displayQDebug;
    QMutex mutexQDebug;

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
