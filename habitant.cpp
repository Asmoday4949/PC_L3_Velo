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
    int tripTime;
    int waitTime;
    int destSiteId;

    while(true)
    {
        int seed =id + siteId;
        tripTime = algoThread->getRandomValue(maxSite, seed + QDateTime::currentMSecsSinceEpoch());
        waitTime = algoThread->getRandomValue(maxSite, seed + QDateTime::currentMSecsSinceEpoch());

        do
        {
            // Different value of seed is used here to get different site !
            destSiteId = algoThread->getRandomValue(maxSite, seed + QDateTime::currentMSecsSinceEpoch());
        }
        while(siteId == destSiteId);

        algoThread->setHabitantState(id, ParamList::BIKE);
        algoThread->startDeplacement(id, siteId, destSiteId, tripTime);

        this->sleep(tripTime);
        this->siteId = destSiteId;

        algoThread->setHabitantState(id, ParamList::ACTION);
        this->sleep(waitTime);
    }
}
