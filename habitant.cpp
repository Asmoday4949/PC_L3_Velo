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

    while(true)
    {
        this->takeVelo(algoThread);

        int destSiteId;
        int tripTime = algoThread->getRandomTripTime();

        do
        {
            // Different value of seed is used here to get different site !
            destSiteId = algoThread->getRandomValue(maxSite);
        }
        while(siteId == destSiteId);

        //move to next site
        algoThread->threadSafeQDebug(QString("Habitant #%1 moving from site #%2 to site #%3").arg(this->id).arg(siteId).arg(destSiteId));
        algoThread->startDeplacement(id, siteId, destSiteId, tripTime);
        this->sleep(tripTime);
        this->siteId = destSiteId;

        this->dropVelo(algoThread);

        //do actions
        this->sleep(algoThread->getRandomTripTime());
    }
}
/**
 * @brief Habitant::dropVelo
 * drop a velo at a site, if no place available will wait, also notify people who need to take a velo
 * @param algoThread
 */
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
        //if not already in the queue get in the queue
        if(currentSite->dropVeloQueue.indexOf(this->id) == -1)
        {
            currentSite->dropVeloQueue.enqueue(this->id);
        }

        algoThread->threadSafeQDebug(QString("Habitant #%1 waiting for dropping velo at site #%2 velo remaining : %3").arg(this->id).arg(currentSite->id).arg(currentSite->velosAtSite));

        currentSite->conditionArrive.wait(&currentSite->mutex);
    }

    //if in the queue, dequeue
    if(!currentSite->dropVeloQueue.isEmpty() && currentSite->dropVeloQueue.head() == this->id)
    {
        currentSite->dropVeloQueue.dequeue();
    }
    algoThread->addVelosAtSite(1, currentSite);

    algoThread->threadSafeQDebug(QString("Habitant #%1 dropped velo at site #%2 velo remaining : %3").arg(this->id).arg(currentSite->id).arg(currentSite->velosAtSite));

    currentSite->mutex.unlock();

    //notify people that are waiting to take a bike that a bike is available
    currentSite->conditionLeave.notify_all();

    emit algoThread->setHabitantState(id, ParamList::ACTION);
}
/**
 * @brief Habitant::takeVelo
 * take a velo at a site, if no velo available will wait, also notify people who need to drop a velo
 * @param algoThread
 */
void Habitant::takeVelo(AlgoThread *algoThread)
{
    Site* currentSite = algoThread->getSites()[this->siteId];

    currentSite->mutex.lock();
    //possible case :
    //borne empty
    //borne not empty && queue not empty && !not first
    while(currentSite->velosAtSite <= 0
          || (currentSite->velosAtSite < algoThread->getNbBorne()
              && !currentSite->takeVeloQueue.isEmpty()
              && currentSite->takeVeloQueue.head() != this->id))
    {
        emit algoThread->setHabitantState(this->id, ParamList::WAIT);
        //if not already in the queue get in the queue
        if(currentSite->takeVeloQueue.indexOf(this->id) == -1)
        {
            currentSite->takeVeloQueue.enqueue(this->id);
        }

        algoThread->threadSafeQDebug(QString("Habitant #%1 waiting for taking velo at site #%2 velo remaining : %3").arg(this->id).arg(currentSite->id).arg(currentSite->velosAtSite));
        currentSite->conditionLeave.wait(&currentSite->mutex);
    }

    //if in the queue, dequeue
    if(!currentSite->takeVeloQueue.isEmpty() && currentSite->takeVeloQueue.head() == this->id)
    {
        currentSite->takeVeloQueue.dequeue();
    }
    //take a bike
    algoThread->addVelosAtSite(-1, currentSite);

    algoThread->threadSafeQDebug(QString("Habitant #%1 took velo at site #%2 velo remaining : %3").arg(this->id).arg(currentSite->id).arg(currentSite->velosAtSite));

    currentSite->mutex.unlock();

    //notify people that are waiting to drop a velo that a free space is available
    currentSite->conditionArrive.notify_all();


    emit algoThread->setHabitantState(id, ParamList::BIKE);
}
