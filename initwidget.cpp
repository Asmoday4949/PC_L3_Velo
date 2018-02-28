#include "initwidget.h"

InitWidget::InitWidget(QWidget *parent) : QWidget(parent)
{
    setupUi(this);
    connect(this->btValider, &QPushButton::clicked, this, &InitWidget::FormSubmitted);
    connect(this->sbSites, &QSpinBox::editingFinished, this, &InitWidget::setVelosMin);
    connect(this->sbBornesSite, &QSpinBox::editingFinished, this, &InitWidget::setVelosMin);
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

void InitWidget::setVelosMin()
{
    this->sbVelos->setMinimum(this->sbSites->value()*(this->sbBornesSite->value()-2)+3);
}
