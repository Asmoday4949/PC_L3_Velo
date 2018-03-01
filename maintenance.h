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
    void takeFromDepot();
    void dropAtDepot();
    void updateDepot(int nbVelosInDepot);

    //members
    int position;
    int nbVelosInCam;

    //const members
    const int maxFromDepot = 2;
    const int idDepot = -1;
    const int breakTime = 5;
};
