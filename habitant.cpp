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
    int waitTime = -1;
    int destSiteId = -1;

    while(true)
    {
        tripTime = algoThread->getRandomTripTime();
        waitTime = algoThread->getRandomTripTime();
        // Different value of seed is used here to get different site !
        destSiteId = algoThread->getRandomValue(maxSite, QDateTime::currentMSecsSinceEpoch() + id + siteId);

        algoThread->setHabitantState(id, ParamList::BIKE);
        algoThread->startDeplacement(id, siteId, destSiteId, tripTime);

        this->sleep(tripTime);
        this->siteId = destSiteId;

        algoThread->setHabitantState(id, ParamList::ACTION);
        //this->sleep(waitTime);
    }
}
