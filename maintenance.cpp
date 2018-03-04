#include "maintenance.h"

#include "algothread.h"

Maintenance::Maintenance()
{
    this->nbVelosInCam = 0;
}

Maintenance::~Maintenance()
{
}

void Maintenance::run()
{
 /*
1. Mettre a = min(2;D) vélos dans la camionnette
2. Pour i = 1 à S faire
    2a. Si Vi > B - 2 alors
        Prendre c = min(Vi - (B - 2); 4 - a) et les mettre dans la camionnette.
        a <- a + c
    2b. Si Vi < B - 2 alors
        Laisser c = min((B - 2) - Vi; a)
        a <- a - c
3. Vider la camionnette D <- D + a.
4. Faire une pause.
*/
    //depot = -1 if moving from depot, nbSite if moving to depot
    AlgoThread* algo = AlgoThread::getAlgoThread();

    this->position = this->idDepot;

    while(true)
    {
        //depot is not protected by a mutex because there is only one maintenance
        //and that's the only thread who take and put in the depot
        this->takeFromDepot();

        for(int i = 0; i < algo->getNbSite(); i++)
        {
            int tripTime = AlgoThread::getRandomTripTime();
            emit algo->startCamionDeplacement(this->position, i, tripTime);
            this->position = i;
            this->sleep(tripTime);
        }

        int tripTime = AlgoThread::getRandomTripTime();
        emit algo->startCamionDeplacement(this->position, algo->getNbSite(), tripTime);
        this->position = this->idDepot;
        this->sleep(tripTime);

        this->dropAtDepot();
        this->sleep(this->breakTime);
    }
}

/**
 * @brief Maintenance::getNextSite
 * set the next site where the camion will go
 */
void Maintenance::setNextSite()
{
    this->position = qrand() % AlgoThread::getAlgoThread()->getNbSite();
}

/**
 * @brief Maintenance::takeFromDepot
 * take the right amount of velos from the depo
 */
int Maintenance::takeFromDepot()
{
    AlgoThread* algo = AlgoThread::getAlgoThread();
    int nbVelosAtDepot = algo->getNbVelosAtDepot();
    int nbVelosTaken = this->maxFromDepot > nbVelosAtDepot ? nbVelosAtDepot : this->maxFromDepot;
    this->nbVelosInCam += nbVelosTaken;
    emit algo->setCamVelo(this->nbVelosInCam);

    this->updateDepot(nbVelosAtDepot-nbVelosTaken);

    return nbVelosTaken;
}

/**
 * @brief Maintenance::dropAtDepot
 * drop all of his velos at the depot
 */
void Maintenance::dropAtDepot()
{
    AlgoThread* algo = AlgoThread::getAlgoThread();

    this->updateDepot(algo->getNbVelosAtDepot()+this->nbVelosInCam);
    this->nbVelosInCam = 0;
    emit algo->setCamVelo(0);
}
/**
 * @brief Maintenance::updateDepot
 * update the number of velos on the UI and the main thread
 * @param nbVelosInDepot
 */
void Maintenance::updateDepot(int nbVelosInDepot)
{
    AlgoThread* algo = AlgoThread::getAlgoThread();
    algo->setNbVelosAtDepot(nbVelosInDepot);
    emit algo->setDepotVelo(nbVelosInDepot);
}

void Maintenance::work()
{
    AlgoThread* algoThread = AlgoThread::getAlgoThread();
    int nbSites = algoThread->getNbSite();
    int nbVelosDepot;
    int nbVelosCamion;

    while(true)
    {
        nbVelosDepot = algoThread->getNbVelosAtDepot();
        nbVelosCamion = takeFromDepot();

        for(int i = 0;i < nbSites; i++)
        {
            Site* currentSite = algoThread->getSites()[i];
            int nbBornes = algoThread->getNbBorne();

            // DANGER ZONE !
            currentSite->mutex.lock();
            int nbVelosSite = currentSite->velosAtSite;

            // take cycles from the site
            if(nbVelosSite > nbBornes - 2)
            {
                int c = min(nbVelosDepot - (nbBornes - 2), 4 - nbVelosCamion);

                currentSite->velosAtSite -= c;

                nbVelosCamion += nbBornes;
            }
            // drop cycles to the site
            else if(nbVelosSite < nbBornes - 2)
            {
                int c = min((nbBornes - 2) - nbVelosSite, nbVelosCamion);

                currentSite->velosAtSite += c;

                nbVelosCamion -= nbBornes;
            }

            // SAFE ZONE
            currentSite->mutex.unlock();

            // animation to next site
            int tripTime = AlgoThread::getRandomTripTime();
            emit algoThread->startCamionDeplacement(this->position, i, tripTime);
            this->position = i;
            this->sleep(tripTime);
        }

        // animation to depot
        int tripTime = AlgoThread::getRandomTripTime();
        emit algoThread->startCamionDeplacement(this->position, algoThread->getNbSite(), tripTime);
        this->position = this->idDepot;
        this->sleep(tripTime);

        // no protection is needed here, cause the maintenance is the only thread who threats this info
        nbVelosDepot += nbVelosCamion;
        updateDepot(nbVelosDepot);

        // wait
        this->sleep(5000);
    }
}
