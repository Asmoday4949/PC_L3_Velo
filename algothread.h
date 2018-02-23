#ifndef ALGOTHREAD_H
#define ALGOTHREAD_H

#include <QThread>
#include <QDebug>

#include "citywidget.h"
#include "paramlist.h"

using namespace std;

class AlgoThread : public QThread
{
    Q_OBJECT
public:
    AlgoThread(CityWidget* mainWindow,int nbSite,int nbHabitants,int nbBorne,int nbVelo);



protected:
     void run();

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

private:
     int nbSite;
     int nbHabitants;
     int nbBorne;
     int nbVelo;
};




#endif // ALGOTHREAD_H
