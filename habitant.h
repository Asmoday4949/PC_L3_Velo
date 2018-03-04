#pragma once

#include <QtWidgets>
#include "algothread.h"

class Habitant : public QThread
{
public:
    Habitant(int id, int siteId);
    ~Habitant();

protected:
    void run() override;
    void dropVelo(AlgoThread* algoThread);
    void takeVelo(AlgoThread* algoThread);
    void moveTo(int destSiteId);

private:
    int id;
    int siteId;
};
