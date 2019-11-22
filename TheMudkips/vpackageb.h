#ifndef VPACKAGEB_H
#define VPACKAGEB_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>
#include <QListWidget>
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
    void defaultPackage();
    void sortTeam();

private slots:
    void on_cancelButton_clicked();

    void on_startButton_clicked();

    void on_confirmButton_clicked();



private:
    Ui::vPackageB *ui;
    QSqlDatabase myDB;
    vSimulation *simulationWindow;
    QString tName;
    QString startTeam = "Detroit Pistons";
    QList<QListWidgetItem *> selectionList;
    int teamNum;
    QString* sortedTeams = nullptr;
                            /*!< pointer to point to list of sorted teams */
    int* sortedDistance = nullptr;
                            /*!< pointer to point to list of sorted destinations */
};

#endif // VPACKAGEB_H
