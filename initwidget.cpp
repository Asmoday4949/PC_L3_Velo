#include "initwidget.h"
#include "ui_initwidget.h"

InitWidget::InitWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InitWidget)
{
    ui->setupUi(this);
}

InitWidget::~InitWidget()
{
    delete ui;
}
