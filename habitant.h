#pragma once

#include <QtWidgets>

class Habitant : public QThread
{
public:
    Habitant();
    ~Habitante();

protected:
    void run() override;
};
