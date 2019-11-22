#ifndef VPACKAGEA_H
#define VPACKAGEA_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>
#include <QListWidget>
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
    void defaultPackage();

    void sortTeam();


private slots:
    void on_cancelButton_clicked();

    void on_startButton_clicked();

    void on_confirmButton_clicked();

private:
    Ui::vPackageA *ui;
    QSqlDatabase myDB;
    vSimulation *simulationWindow;
    QString tName;
    QString startTeam = "Denver Nuggets";
    QList<QListWidgetItem *> selectionList;
    int teamNum;
    QString* sortedTeams = nullptr;
                            /*!< pointer to point to list of sorted teams */
    int* sortedDistance = nullptr;
                            /*!< pointer to point to list of sorted destinations */
};

#endif // VPACKAGEA_H
