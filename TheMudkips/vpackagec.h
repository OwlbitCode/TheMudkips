#ifndef VPACKAGEC_H
#define VPACKAGEC_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>
#include <QListWidget>
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
    void defaultListView();
    void defaultComboBoxView();
    void sortTeamList();

private slots:
    void on_cancelButton_clicked();

    void on_startButton_clicked();

    void on_startTeam_currentIndexChanged(const QString &arg1);

    void on_confirmButton_clicked();

private:
    Ui::vPackageC *ui;
    QSqlDatabase myDB;
    vSimulation *simulationWindow;

    QList<QListWidgetItem *> customList;
    QString* sortedTeams = nullptr;
    int* sortedDistance = nullptr;
    int teamNum;            // number of teams selected
    QString teamName;       // team name
    QString startTeam;      // starting team name
    QString closestTeam;    // team closest to starting team
};

#endif // VPACKAGEC_H
