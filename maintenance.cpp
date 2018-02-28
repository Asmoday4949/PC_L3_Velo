#include "maintenance.h"

#include "algothread.h"

Maintenance::Maintenance()
{

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

    emit AlgoThread::getAlgoThread()->startCamionDeplacement(1,2,5);

    while(true)
    {

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

/**
 * @brief Maintenance::getTripTime
 * @return time to wait between one and waitingTime
 */
int Maintenance::getTripTime()
{
    return qrand() % this->waitingTime + 1;
}
