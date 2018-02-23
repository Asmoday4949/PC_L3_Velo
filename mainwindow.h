#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include "initwidget.h"
#include "citywidget.h"
#include "algothread.h"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

signals:

public slots:
    loadCity();
private:
    InitWidget* initWidget;
    QStackedLayout* mainLayout;
};

#endif // MAINWINDOW_H
