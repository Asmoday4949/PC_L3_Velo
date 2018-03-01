#include "habitant.h"

Habitant::Habitant(int id, int siteId)
{
    this->id = id;
    this->siteId = siteId;
}

Habitant::~Habitant()
{

}

void Habitant::run()
{
    AlgoThread* algoThread = AlgoThread::getAlgoThread();

    int maxSite = algoThread->getNbSite();
    int tripTime = -1;
    int destSiteId = -1;


    tripTime = algoThread->getRandomTripTime();
    destSiteId = algoThread->getRandomValue(maxSite);

    algoThread->setHabitantState(id, ParamList::BIKE);
    algoThread->startDeplacement(id, siteId, destSiteId, tripTime);
}
