#pragma once

#include <QDebug>

#include <QMainWindow>
#include <QPropertyAnimation>

#include "GUI/people.h"
#include "GUI/place.h"
#include "GUI/camion.h"

#include "paramlist.h"

class CityWidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit CityWidget(int nbSite,int nbHabitants,int nbBorne,int nbVelo,QWidget *parent = 0);
    ~CityWidget();

public slots:
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

    QList<Place*>* placeList;
    Place* depot;
    Camion* camion;
    QList<People*>* peopleList;

};

