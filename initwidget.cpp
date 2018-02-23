#include "initwidget.h"

InitWidget::InitWidget(QWidget *parent) : QWidget(parent)
{
    setupUi(this);
    connect(btValider, &QPushButton::clicked, this, &InitWidget::FormSubmitted);
}

int InitWidget::getVelos()
{
    return this->sbVelos->value();
}

int InitWidget::getBornesSite()
{
    return this->sbBornesSite->value();
}

int InitWidget::getSites()
{
    return this->sbSites->value();
}

int InitWidget::getHabitants()
{
    return this->sbHabitants->value();
}

InitWidget::~InitWidget()
{

}
