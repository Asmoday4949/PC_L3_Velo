#pragma once

#include <QtWidgets>

class Maintenance : public QThread
{
public:
    Maintenance();
    ~Maintenance();

protected:
    //functions
    void run() override;

    void setNextSite();
    int getTripTime();

    //members
    int direction;
    int nbVelosInCam;

    //static members
    const int waitingTime = 3; //time of the pause in second
    const int maxFromDepot = 2;
};
