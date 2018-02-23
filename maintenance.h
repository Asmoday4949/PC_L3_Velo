#pragma once

#include <QtWidgets>

class Maintenance : public QThread
{
public:
    Maintenance();
    ~Maintenance();

protected:
    void run() override;
};
