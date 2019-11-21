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
    //!< Constructor

    ~vPackageC();
    //!< Destructor

    void defaultListView();
    //!< Sets default view for list on left side listing teams from db

    void defaultComboBoxView();
    //!< Sets default combobox view using values from the database.

    void sortTeamOptimize();
    //!< Creates the sorted dynamic team and destination arrays
    //!< OPTIMIZED: shortest distance, not fan choice

    void sortTeamNormal();
    //!< Creates the sorted dynamic team and destination arrays
    //!< NOT OPTIMIZED: fan choice of order

private slots:
    void on_cancelButton_clicked();
    //!< Closes window and returns fan to package window

    void on_startButton_clicked();
    //!< Opens vacation simulation window and closes this window

    void on_startTeam_currentIndexChanged(const QString &arg1);
    //!< Updates list view and sets starting team

    void on_confirmButton_clicked();
    //!< Creates list, calls sortTeamList(), and displays arrays in list

private:
    Ui::vPackageC *ui;      /*!< class object */
    QSqlDatabase myDB;      /*!< database connection */
    vSimulation *simulationWindow;
                            /*!< class object for simulation window */
    QList<QListWidgetItem *> customList;
                            /*!< list of teams selected from list */
    QString* sortedTeams = nullptr;
                            /*!< list of sorted teams */
    int* sortedDistance = nullptr;
                            /*!< list of sorted destinations */
    int teamNum;            /*!< number of teams selected */
    QString teamName;       /*!< team name */
    QString startTeam;      /*!< starting team name */
    QString closestTeam;    /*!< team closest to starting team */
};

#endif // VPACKAGEC_H
