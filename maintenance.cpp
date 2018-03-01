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
    //depot = nbSite
    AlgoThread* algo = AlgoThread::getAlgoThread();

    emit algo->initCamion();

    while(true)
    {
        int nbVelosAtDepot = algo->getNbVelosAtDepot();
        int nbVelosTaken = this->maxFromDepot > nbVelosAtDepot ? nbVelosAtDepot : this->maxFromDepot;
        this->nbVelosInCam += nbVelosTaken;

        algo->setNbVelosAtDepot(nbVelosAtDepot-nbVelosTaken);

        emit algo->setCamVelo(this->nbVelosInCam);
        emit algo->setDepotVelo(algo->getNbVelosAtDepot());

        for(int i = 0; i < algo->getNbSite(); i++)
        {

        }

        while(true) { }
    }
}

/**
 * @brief Maintenance::getNextSite
 * set the next site where the camion will go
 */
void Maintenance::setNextSite()
{
    this->direction = qrand() % AlgoThread::getAlgoThread()->getNbSite();
}
