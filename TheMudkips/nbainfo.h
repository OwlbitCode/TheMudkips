#ifndef NBAINFO_H
#define NBAINFO_H

#include <QWidget>

#include "nbateams.h"
#include "nbaarenas.h"
#include "nbaconfdiv.h"
#include "nbacoaches.h"
#include "nbasouvenirs.h"

namespace Ui {
class NBAInfo;
}

class NBAInfo : public QWidget
{
    Q_OBJECT

public:
    explicit NBAInfo(QWidget *parent = nullptr);
    ~NBAInfo();

private slots:
    void on_homeButton_clicked();

    void on_teamsButton_clicked();

    void on_arenasButton_clicked();

    void on_confDivButton_clicked();

    void on_coachesButton_clicked();

    void on_souvenirsButton_clicked();

    void on_exitButton_clicked();

private:
    Ui::NBAInfo *ui;

    nbaTeams teamWindow;
    nbaArenas arenaWindow;
    nbaConfDiv confDivWindow;
    nbaCoaches coachWindow;
    nbaSouvenirs souvenirsWindow;
};

#endif // NBAINFO_H
