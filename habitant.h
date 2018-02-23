#pragma once

#include <QtWidgets>

class Habitant : public QThread
{
public:
    Habitant();
    ~Habitant();

protected:
    void run() override;
};
