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
    // initialise random
    qsrand(id + siteId + QDateTime::currentMSecsSinceEpoch());

    AlgoThread* algoThread = AlgoThread::getAlgoThread();

    int maxSite = algoThread->getNbSite();
    int tripTime;
    int waitTime;
    int destSiteId;

    while(true)
    {
        tripTime = algoThread->getRandomTripTime();
        waitTime = algoThread->getRandomValue(maxSite);

        do
        {
            // Different value of seed is used here to get different site !
            destSiteId = algoThread->getRandomValue(maxSite);
        }
        while(siteId == destSiteId);

        emit algoThread->setHabitantState(id, ParamList::BIKE);
        algoThread->startDeplacement(id, siteId, destSiteId, tripTime);
        this->sleep(tripTime);
        this->siteId = destSiteId;

        this->tryDropVelo(algoThread);

        this->sleep(waitTime);
    }
}

void Habitant::tryDropVelo(AlgoThread *algoThread)
{
    Site* currentSite = algoThread->getSites()[this->siteId];

    currentSite->mutex.lock();
    //possible case :
    //borne full
    //borne not full && queue not empty && !not first
    while(currentSite->velosAtSite >= algoThread->getNbBorne()
          || (currentSite->velosAtSite < algoThread->getNbBorne()
              && !currentSite->dropVeloQueue.isEmpty()
              && currentSite->dropVeloQueue.head() != this->id))
    {
        emit algoThread->setHabitantState(this->id, ParamList::WAIT);
        if(currentSite->dropVeloQueue.indexOf(this->id) == -1)
        {
            currentSite->dropVeloQueue.enqueue(this->id);
        }
        currentSite->conditionArrive.wait(&currentSite->mutex);
    }

    if(!currentSite->dropVeloQueue.isEmpty() && currentSite->dropVeloQueue.head() == this->id)
    {
        currentSite->dropVeloQueue.dequeue();
    }
    algoThread->addVelosAtSite(1, currentSite);

    currentSite->conditionLeave.notify_all();

    currentSite->mutex.unlock();

    emit algoThread->setHabitantState(id, ParamList::ACTION);
}

void Habitant::tryTakeVelo(AlgoThread *algoThread)
{

}
