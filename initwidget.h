#ifndef INITWIDGET_H
#define INITWIDGET_H

#include <QWidget>
#include "ui_initwidget.h"

class InitWidget : public QWidget, private Ui_InitWidget
{
    Q_OBJECT

public:
    explicit InitWidget(QWidget *parent = 0);
    int getVelos();
    int getBornesSite();
    int getSites();
    int getHabitants();
    ~InitWidget();
signals:
    void FormSubmitted();

};

#endif // INITWIDGET_H
