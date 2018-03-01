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

    //members
    int direction;
    int nbVelosInCam;

    //static members
    const int maxFromDepot = 2;
};
