#include "citywidget.h"

CityWidget::CityWidget(int _nbSite,int _nbHabitants,int _nbBorne,int _nbVelo,QWidget *parent) :
    QMainWindow(parent)
{
    nbSite = _nbSite;
    nbHabitants = _nbHabitants;
    nbBorne = _nbBorne;
    nbVelo = _nbVelo;

    placeList = new QList<Place*>();
    Place* place;
    int radius = 200;
    for(int i=1;i<=nbSite;i++)
    {
        QPointF position = QPointF(120+radius+radius*cos(2.0*3.14/((float)nbSite) *((float)i+1)),
                10+radius+radius*sin(2.0*3.14/((float)nbSite) *((float)i+1)));
        place = new Place(ParamList::siteList[i-1],position,this);
        placeList->append(place);
        place->show();
    }

    peopleList = new QList<People*>();
    People* people;
    for(int i=1;i<=nbHabitants;i++)
    {
        people = new People(ParamList::nameList[i-1],this);
        peopleList->append(people);
        people->show();
    }

    depot = new Place("DEPOT",QPointF(650,20),this);
    depot->show();

    camion = new Camion(this);
    initCamion();
    camion->show();
}

CityWidget::~CityWidget()
{

}

void CityWidget::initSite(int siteId,int nbVelo)
{
    placeList->at(siteId)->setNbVelo(nbVelo);
}

void CityWidget::initHabitant(int habId,int initSiteId)
{
    peopleList->at(habId)->setPosition(placeList->at(initSiteId)->getDest());
}

void CityWidget::initCamion()
{
    camion->setPosition(depot->getDest());
}

void CityWidget::setHabitantState(int habId,int state)
{
    peopleList->at(habId)->changeState(state);
}

void CityWidget::setSiteVelo(int idSite,int nbVelo)
{
    placeList->at(idSite)->setNbVelo(nbVelo);
}

void CityWidget::startDeplacement(int habId,int initSite,int destSite,int parcourTime)
{
    QPropertyAnimation *animation = new QPropertyAnimation(peopleList->at(habId),"geometry");
    animation->setDuration(parcourTime*1000);
    QPointF A = placeList->at(initSite)->getDest();
    animation->setStartValue(QRect(A.x(),A.y(),100,100));
    QPointF B = placeList->at(destSite)->getDest();
    animation->setEndValue(QRect(B.x(),B.y(),100,100));
    animation->start();
}

void CityWidget::setDepotVelo(int nbVeloDep)
{
    depot->setNbVelo(nbVeloDep);
}

void CityWidget::setCamVelo(int nbVeloCam)
{
    camion->setNbVelo(nbVeloCam);
}

void CityWidget::startCamionDeplacement(int initSite,int destSite,int parcourTime)
{
    QPropertyAnimation *animation = new QPropertyAnimation(camion,"geometry");
    animation->setDuration(parcourTime*1000);

    QPointF A;
    if(initSite==-1)
        A = depot->getDest();
    else
        A = placeList->at(initSite)->getDest();

    QPointF B;
    if(destSite==placeList->size())
        B = depot->getDest();
    else
        B = placeList->at(destSite)->getDest();

    animation->setStartValue(QRect(A.x(),A.y(),100,100));
    animation->setEndValue(QRect(B.x(),B.y(),100,100));
    animation->start();
}
