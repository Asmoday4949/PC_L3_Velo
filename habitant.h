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
    void tryDropVelo(AlgoThread* algoThread);
    void tryTakeVelo(AlgoThread* algoThread);

private:
    int id;
    int siteId;
};
