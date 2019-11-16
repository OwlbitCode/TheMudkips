#ifndef VPACKAGEA_H
#define VPACKAGEA_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>
#include "vsimulation.h"

namespace Ui {
class vPackageA;
}

class vPackageA : public QWidget
{
    Q_OBJECT

public:
    explicit vPackageA(QWidget *parent = nullptr);
    ~vPackageA();

private slots:
    void on_cancelButton_clicked();

    void on_startButton_clicked();

private:
    Ui::vPackageA *ui;
    QSqlDatabase myDB;
    vSimulation *simulationWindow;
};

#endif // VPACKAGEA_H
