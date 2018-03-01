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

private:
    int id;
    int siteId;
};
