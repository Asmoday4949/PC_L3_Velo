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
    qsrand(id*20 + siteId + QDateTime::currentMSecsSinceEpoch());

    AlgoThread* algoThread = AlgoThread::getAlgoThread();

    int maxSite = algoThread->getNbSite();
    int tripTime;
    int waitTime;
    int destSiteId;

    while(true)
    {
        this->takeVelo(algoThread);

        tripTime = algoThread->getRandomTripTime();
        waitTime = algoThread->getRandomTripTime();

        do
        {
            // Different value of seed is used here to get different site !
            destSiteId = algoThread->getRandomValue(maxSite);
        }
        while(siteId == destSiteId);

        algoThread->startDeplacement(id, siteId, destSiteId, tripTime);
        this->sleep(tripTime);
        this->siteId = destSiteId;

        this->dropVelo(algoThread);

        this->sleep(waitTime);
    }
}

void Habitant::dropVelo(AlgoThread *algoThread)
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

void Habitant::takeVelo(AlgoThread *algoThread)
{
    Site* currentSite = algoThread->getSites()[this->siteId];

    currentSite->mutex.lock();
    //possible case :
    //borne empty
    //borne not empty && queue not empty && !not first

    qDebug() << currentSite->velosAtSite << currentSite->takeVeloQueue;
    while(currentSite->velosAtSite <= 0
          || (currentSite->velosAtSite < algoThread->getNbBorne()
              && !currentSite->takeVeloQueue.isEmpty()
              && currentSite->takeVeloQueue.head() != this->id))
    {
        emit algoThread->setHabitantState(this->id, ParamList::WAIT);
        if(currentSite->takeVeloQueue.indexOf(this->id) == -1)
        {
            currentSite->takeVeloQueue.enqueue(this->id);
        }
        currentSite->conditionLeave.wait(&currentSite->mutex);
    }

    if(!currentSite->takeVeloQueue.isEmpty() && currentSite->takeVeloQueue.head() == this->id)
    {
        currentSite->takeVeloQueue.dequeue();
    }
    algoThread->addVelosAtSite(-1, currentSite);

    currentSite->conditionArrive.notify_all();

    currentSite->mutex.unlock();

    emit algoThread->setHabitantState(id, ParamList::BIKE);
}
