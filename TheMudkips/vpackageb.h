#ifndef VPACKAGEB_H
#define VPACKAGEB_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>
#include "vsimulation.h"

namespace Ui {
class vPackageB;
}

class vPackageB : public QWidget
{
    Q_OBJECT

public:
    explicit vPackageB(QWidget *parent = nullptr);
    ~vPackageB();

private slots:
    void on_cancelButton_clicked();

    void on_startButton_clicked();

private:
    Ui::vPackageB *ui;
    QSqlDatabase myDB;
    vSimulation *simulationWindow;
};

#endif // VPACKAGEB_H
