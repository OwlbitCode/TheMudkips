#ifndef NBATEAMS_H
#define NBATEAMS_H

#include <QWidget>
#include "QtSql"
#include "databasemanager.h"
#include "QtDebug"

namespace Ui {
class nbaTeams;
}

class nbaTeams : public QWidget
{
    Q_OBJECT

public:
    explicit nbaTeams(QWidget *parent = nullptr);
    ~nbaTeams();

private slots:

    void on_sortNameButton_clicked();

    void on_sortYearButton_clicked();

    void on_teamComboBox_activated(const QString &arg1);

private:
    Ui::nbaTeams *ui;
    QSqlDatabase myDB;
};

#endif // NBATEAMS_H
