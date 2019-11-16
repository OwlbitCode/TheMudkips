#ifndef VPACKAGEC_H
#define VPACKAGEC_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>
#include "vsimulation.h"

namespace Ui {
class vPackageC;
}

class vPackageC : public QWidget
{
    Q_OBJECT

public:
    explicit vPackageC(QWidget *parent = nullptr);
    ~vPackageC();

private slots:
    void on_cancelButton_clicked();

    void on_startButton_clicked();

private:
    Ui::vPackageC *ui;
    QSqlDatabase myDB;
    vSimulation *simulationWindow;
};

#endif // VPACKAGEC_H
